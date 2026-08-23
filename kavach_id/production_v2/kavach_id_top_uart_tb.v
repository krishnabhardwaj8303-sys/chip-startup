module kavach_id_top_uart_tb;

    reg  clk, rst;
    wire uart_link;      // host -> chip
    wire uart_from_chip; // chip -> host
    wire chip_healthy, verification_blocked;

    // "Host" TX: drives commands into the chip via a real uart_tx
    reg        host_tx_start;
    reg  [7:0] host_tx_data;
    wire       host_tx_busy;

    uart_tx #(.CLKS_PER_BIT(4)) HOST_TX (
        .clk(clk), .rst(rst),
        .tx_start(host_tx_start), .data_in(host_tx_data),
        .tx_out(uart_link), .tx_busy(host_tx_busy)
    );

    // "Host" RX: receives chip responses via a real uart_rx
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
            send_byte(8'h01);          // CMD = WRITE
            send_byte(addr);
            send_byte(data[31:24]);
            send_byte(data[23:16]);
            send_byte(data[15:8]);
            send_byte(data[7:0]);
        end
    endtask

    reg [31:0] read_result;
    integer    read_byte_count;

    task reg_read_uart(input [8:0] addr);
        begin
            read_result = 0;
            read_byte_count = 0;
            send_byte(8'h02);          // CMD = READ
            send_byte(addr[7:0]);
            send_byte(8'h00);          // DATA field unused for reads, still 4 bytes per frame
            send_byte(8'h00);
            send_byte(8'h00);
            send_byte(8'h00);
            // wait for all 4 response bytes to arrive
            wait (read_byte_count == 4);
        end
    endtask

    always @(posedge clk) begin
        if (host_rx_valid) begin
            read_result <= {read_result[23:0], host_rx_byte};
            read_byte_count <= read_byte_count + 1;
        end
    end

    initial begin
        rst = 1; host_tx_start = 0; host_tx_data = 0;
        #20; rst = 0; #40; // extra margin for reset_sync's 2-cycle release

        $display("================================================");
        $display("  KAVACH-ID TOP-LEVEL UART-PROTOCOL INTEGRATION");
        $display("================================================");

        $display("--- Test 1: Run BIST via UART, check chip_healthy ---");
        reg_write_uart(8'h00, 32'h0000_0001); // CONTROL[0] = bist_start
        repeat (10) @(posedge clk);
        $display("chip_healthy=%0d (expect 1)", chip_healthy);
        if (chip_healthy)
            $display("PASS");
        else
            $display("FAIL");

        $display("--- Test 2: Fresh verify -> auth_request -> grant, via UART ---");
        reg_write_uart(8'h08, 32'h1111_1111); // CHALLENGE
        reg_write_uart(8'h00, 32'h0000_0002); // CONTROL[1] = stabilizer_start
        repeat (15) @(posedge clk);
        reg_write_uart(8'h00, 32'h0000_0004); // CONTROL[2] = auth_request
        repeat (10) @(posedge clk);
        read_byte_count = 0;
        reg_read_uart(8'h04); // STATUS
        $display("STATUS=0x%0h (expect bit3=1, authentication_grant)", read_result);
        if (read_result[3] == 1)
            $display("PASS");
        else
            $display("FAIL");

        $display("--- Test 3: Same challenge again -> replay -> blocked ---");
        reg_write_uart(8'h08, 32'h1111_1111); // SAME challenge
        reg_write_uart(8'h00, 32'h0000_0002);
        repeat (15) @(posedge clk);
        reg_write_uart(8'h00, 32'h0000_0004);
        repeat (10) @(posedge clk);
        reg_read_uart(8'h04);
        $display("STATUS=0x%0h, verification_blocked=%0d", read_result, verification_blocked);
        if (read_result[2] == 1 && verification_blocked == 1)
            $display("PASS: replay correctly detected and blocked");
        else
            $display("FAIL");

        $display("--- Test 4: Read ciphertext via CIPHERTEXT_DATA register ---");
        reg_read_uart(8'h34);
        $display("CIPHERTEXT_DATA=0x%0h (non-zero expected if a grant produced ciphertext)", read_result);
        if (read_result != 0)
            $display("PASS: ciphertext readable via register, no auto-push conflict");
        else
            $display("FAIL: unexpected zero ciphertext");

        $display("================================================");
        $display("UART-protocol top-level integration test complete");
        $display("================================================");
        $finish;
    end
endmodule
