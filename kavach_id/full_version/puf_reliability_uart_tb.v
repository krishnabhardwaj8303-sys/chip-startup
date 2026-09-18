module puf_reliability_uart_tb;

    reg  clk, rst;
    wire uart_link;
    wire uart_from_chip;
    wire chip_healthy, verification_blocked;

    reg        host_tx_start;
    reg  [7:0] host_tx_data;
    wire       host_tx_busy;

    uart_tx #(.CLKS_PER_BIT(4)) HOST_TX (
        .clk(clk), .rst(rst),
        .tx_start(host_tx_start), .data_in(host_tx_data),
        .tx_out(uart_link), .tx_busy(host_tx_busy)
    );

    wire [7:0] host_rx_byte;
    wire       host_rx_valid;

    uart_rx #(.CLKS_PER_BIT(4)) HOST_RX (
        .clk(clk), .rst(rst),
        .rx_in(uart_from_chip),
        .data_out(host_rx_byte),
        .data_valid(host_rx_valid)
    );

    kavach_id_top DUT (
        .clk(clk), .clk_sel(1'b0), .rst(rst),
        .uart_rx_in(uart_link),
        .uart_tx_out(uart_from_chip),
        .chip_healthy(chip_healthy),
        .verification_blocked(verification_blocked)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    task send_byte(input [7:0] b);
        begin
            wait (host_tx_busy == 0);
            host_tx_data = b;
            host_tx_start = 1;
            @(posedge clk); #1;
            host_tx_start = 0;
            wait (host_tx_busy == 1);
            wait (host_tx_busy == 0);
        end
    endtask

    task reg_write_uart(input [7:0] addr, input [31:0] data);
        begin
            send_byte(8'h01);
            send_byte(addr);
            send_byte(data[31:24]);
            send_byte(data[23:16]);
            send_byte(data[15:8]);
            send_byte(data[7:0]);
        end
    endtask

    reg [31:0] read_result;
    integer    read_byte_count;

    task reg_read_uart(input [7:0] addr);
        begin
            read_result = 0;
            read_byte_count = 0;
            send_byte(8'h02);
            send_byte(addr);
            send_byte(8'h00);
            send_byte(8'h00);
            send_byte(8'h00);
            send_byte(8'h00);
            wait (read_byte_count == 4);
        end
    endtask

    always @(posedge clk) begin
        if (host_rx_valid) begin
            read_result     <= {read_result[23:0], host_rx_byte};
            read_byte_count <= read_byte_count + 1;
        end
    end

    initial begin
        rst = 1; host_tx_start = 0; host_tx_data = 0;
        #20; rst = 0; #150;

        $display("================================================");
        $display("  PUF RELIABILITY-MASK ENROLLMENT TESTS (via UART)");
        $display("================================================");

        $display("--- TEST A: Mask starts unlocked, all-zero ---");
        reg_read_uart(8'h44); // MASK_STATUS
        $display("MASK_STATUS=0x%0h (expect bit0=mask_locked=0)", read_result);
        if (read_result[0] == 0)
            $display("PASS: mask starts unlocked");
        else
            $display("FAIL");

        reg_read_uart(8'h40); // RELIABILITY_MASK
        $display("RELIABILITY_MASK=0x%08h (expect 0 before enrollment)", read_result);
        if (read_result == 32'h0)
            $display("PASS: mask starts all-zero");
        else
            $display("FAIL");

        $display("--- TEST B: Trigger enrollment (CONTROL bit5), wait for completion ---");
        reg_write_uart(8'h00, 32'h0000_0020); // CONTROL bit5 = enroll_start
        // 8 enrollment rounds x (3-sample resample + ~120-cycle SHA-free
        // stabilizer, which is near-instant since puf_stabilizer.v has
        // no multi-cycle hash) - generous margin for 8 full rounds.
        repeat (3000) @(posedge clk);

        reg_read_uart(8'h44);
        $display("MASK_STATUS=0x%0h (expect bit0=mask_locked=1)", read_result);
        if (read_result[0] == 1)
            $display("PASS: enrollment completed and mask locked!");
        else
            $display("FAIL: enrollment did not complete/lock in the expected window");

        reg_read_uart(8'h40);
        $display("RELIABILITY_MASK=0x%08h after enrollment", read_result);
        // Not asserting a specific value here (depends on this chip
        // instance's simulated near-tie bits) - just confirming the
        // read path works and enrollment produced SOME defined mask.

        $display("--- TEST C: Re-enrollment attempt after lock is ignored ---");
        reg_write_uart(8'h00, 32'h0000_0020); // try enroll_start again
        repeat (50) @(posedge clk);
        reg_read_uart(8'h44);
        if (read_result[1] == 0) // enroll_busy should never have asserted
            $display("PASS: locked mask correctly rejected re-enrollment attempt (enroll_busy never set)");
        else
            $display("FAIL: SECURITY-RELEVANT BUG - re-enrollment started on a locked mask");

        $display("--- TEST D: Authentication still works normally after enrollment ---");
        reg_write_uart(8'h08, 32'hBEEF0001); // CHALLENGE
        reg_write_uart(8'h00, 32'h0000_0001); // CONTROL bit0 = bist_start
        repeat (10) @(posedge clk);
        reg_write_uart(8'h00, 32'h0000_0002); // CONTROL bit1 = stabilizer_start
        repeat (200) @(posedge clk);
        reg_write_uart(8'h00, 32'h0000_0004); // CONTROL bit2 = auth_request
        repeat (200) @(posedge clk);
        reg_read_uart(8'h04); // STATUS
        $display("STATUS=0x%0h (expect bit3=authentication_grant=1)", read_result);
        if (read_result[3] == 1)
            $display("PASS: authentication still succeeds normally after mask enrollment!");
        else
            $display("FAIL: authentication broken after enrollment - masking integration bug");

        $display("================================================");
        $display("PUF reliability-mask enrollment tests (UART) complete");
        $display("================================================");
        $finish;
    end
endmodule
