module offline_provenance_uart_tb;

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

    integer i;

    initial begin
        rst = 1; host_tx_start = 0; host_tx_data = 0;
        #20; rst = 0; #150; // extra margin for POR_CYCLES (8) hold + reset_sync 2-cycle release

        $display("================================================");
        $display("  OFFLINE-VERIFY BUDGET + PROVENANCE (via UART)");
        $display("================================================");

        reg_write_uart(8'h00, 32'h0000_0001); // BIST
        repeat (10) @(posedge clk);

        $display("--- TEST A: Initial offline budget should be 50 ---");
        reg_read_uart(8'h20); // OFFLINE_STATUS
        $display("OFFLINE_STATUS=0x%0h, budget=%0d", read_result, read_result[7:0]);
        if (read_result[7:0] == 8'd50)
            $display("PASS");
        else
            $display("FAIL");

        $display("--- TEST B: Budget decrements by 1 per auth_request (5 requests) ---");
        for (i = 0; i < 5; i = i + 1) begin
            reg_write_uart(8'h08, 32'h3000_0000 + i);
            reg_write_uart(8'h00, 32'h0000_0002);
            repeat (15) @(posedge clk);
            reg_write_uart(8'h00, 32'h0000_0004);
            repeat (10) @(posedge clk);
        end
        reg_read_uart(8'h20);
        $display("After 5 auth_requests, budget=%0d (expect 45)", read_result[7:0]);
        if (read_result[7:0] == 8'd45)
            $display("PASS");
        else
            $display("FAIL");

        $display("--- TEST C: Exhaust remaining 45, confirm denial on 51st ---");
        for (i = 0; i < 45; i = i + 1) begin
            reg_write_uart(8'h08, 32'h4000_0000 + i);
            reg_write_uart(8'h00, 32'h0000_0002);
            repeat (15) @(posedge clk);
            reg_write_uart(8'h00, 32'h0000_0004);
            repeat (10) @(posedge clk);
        end
        reg_read_uart(8'h20);
        $display("Budget after exhaustion: 0x%0h budget=%0d sync_required=%0d",
                   read_result, read_result[7:0], read_result[8]);

        reg_write_uart(8'h08, 32'h5000_0000);
        reg_write_uart(8'h00, 32'h0000_0002);
        repeat (15) @(posedge clk);
        reg_write_uart(8'h00, 32'h0000_0004);
        repeat (10) @(posedge clk);
        reg_read_uart(8'h04); // STATUS
        $display("STATUS after budget-exhausted request = 0x%0h (bit3=grant should be 0)", read_result);
        if (read_result[3] == 0)
            $display("PASS: no grant when budget exhausted");
        else
            $display("FAIL: SECURITY BUG - grant issued despite exhausted budget");
        $display("verification_blocked=%0d (expect 1)", verification_blocked);

        $display("--- TEST D: sync_complete restores budget to 50 ---");
        reg_write_uart(8'h00, 32'h0000_0008); // CONTROL bit3 = sync_complete
        repeat (10) @(posedge clk);
        reg_read_uart(8'h20);
        $display("After sync_complete, budget=%0d (expect 50)", read_result[7:0]);
        if (read_result[7:0] == 8'd50)
            $display("PASS");
        else
            $display("FAIL");

        $display("--- TEST E: Provenance chain - correct sequence completes cleanly ---");
        reg_write_uart(8'h14, 32'h0000_0000); reg_write_uart(8'h18, 32'hAAAA_0000);
        reg_write_uart(8'h00, 32'h0000_0010); repeat (150) @(posedge clk);

        reg_write_uart(8'h14, 32'h0000_0001); reg_write_uart(8'h18, 32'hBBBB_0000);
        reg_write_uart(8'h00, 32'h0000_0010); repeat (150) @(posedge clk);

        reg_write_uart(8'h14, 32'h0000_0002); reg_write_uart(8'h18, 32'hCCCC_0000);
        reg_write_uart(8'h00, 32'h0000_0010); repeat (150) @(posedge clk);

        reg_write_uart(8'h14, 32'h0000_0003); reg_write_uart(8'h18, 32'hDDDD_0000);
        reg_write_uart(8'h00, 32'h0000_0010); repeat (150) @(posedge clk);

        reg_read_uart(8'h1C); // PROVENANCE_STATUS
        $display("PROVENANCE_STATUS=0x%0h (bit0=violation, bit1=chain_complete)", read_result);
        if (read_result[1] == 1 && read_result[0] == 0)
            $display("PASS: chain_complete set, no violation");
        else
            $display("FAIL");

        $display("--- TEST F: Provenance chain - skipped stage triggers violation ---");
        rst = 1; #20; rst = 0; #150; // extra margin for POR_CYCLES (8) hold + reset_sync 2-cycle release // fresh chip

        reg_write_uart(8'h14, 32'h0000_0000); reg_write_uart(8'h18, 32'h1111_0000);
        reg_write_uart(8'h00, 32'h0000_0010); repeat (150) @(posedge clk);

        reg_write_uart(8'h14, 32'h0000_0003); reg_write_uart(8'h18, 32'h2222_0000);
        reg_write_uart(8'h00, 32'h0000_0010); repeat (150) @(posedge clk);

        reg_read_uart(8'h1C);
        $display("PROVENANCE_STATUS=0x%0h", read_result);
        if (read_result[0] == 1)
            $display("PASS: sequence_violation correctly flagged");
        else
            $display("FAIL");

        $display("================================================");
        $display("Offline-verify + provenance (UART) tests complete");
        $display("================================================");
        $finish;
    end
endmodule
