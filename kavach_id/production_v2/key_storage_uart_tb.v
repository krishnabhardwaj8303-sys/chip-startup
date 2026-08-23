module key_storage_uart_tb;

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
        .clk(clk), .rst(rst),
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
        #20; rst = 0; #40;

        $display("================================================");
        $display("  PER-CHIP KEY STORAGE TESTS (via UART)");
        $display("================================================");

        $display("--- TEST A: Key starts unprogrammed (key_locked = 0) ---");
        reg_read_uart(8'h30); // KEY_STATUS
        $display("KEY_STATUS=0x%0h (expect bit0=0)", read_result);
        if (read_result[0] == 0)
            $display("PASS: key starts unlocked");
        else
            $display("FAIL");

        $display("--- TEST B: Program a key, confirm it locks ---");
        reg_write_uart(8'h28, 32'hCAFEF00D); // KEY_DATA
        reg_write_uart(8'h2C, 32'h0000_0001); // KEY_CONTROL bit0 = prog_enable
        repeat (10) @(posedge clk);
        reg_read_uart(8'h30);
        $display("KEY_STATUS=0x%0h (expect bit0=1)", read_result);
        if (read_result[0] == 1)
            $display("PASS: key is now locked");
        else
            $display("FAIL");

        $display("--- TEST C: Attempt to reprogram - must be rejected ---");
        reg_write_uart(8'h28, 32'hDEADBEEF); // try a DIFFERENT key
        reg_write_uart(8'h2C, 32'h0000_0001); // try to re-trigger prog_enable
        repeat (10) @(posedge clk);
        $display("chip_key internal value = 0x%0h (expect still 0xCAFEF00D)", DUT.chip_key_w);
        if (DUT.chip_key_w == 32'hCAFEF00D)
            $display("PASS: second programming attempt correctly rejected, original key preserved");
        else
            $display("FAIL: SECURITY BUG - key was overwritten after lock");

        $display("================================================");
        $display("Key storage tests (UART) complete");
        $display("================================================");
        $finish;
    end
endmodule
