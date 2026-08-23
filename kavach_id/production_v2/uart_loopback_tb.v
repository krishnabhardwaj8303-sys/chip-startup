module uart_loopback_tb;

    reg  clk, rst;
    reg  tx_start;
    reg  [7:0] tx_data;
    wire tx_out, tx_busy;
    wire [7:0] rx_data_out;
    wire rx_valid;

    uart_tx #(.CLKS_PER_BIT(4)) TX (
        .clk(clk), .rst(rst),
        .tx_start(tx_start), .data_in(tx_data),
        .tx_out(tx_out), .tx_busy(tx_busy)
    );

    uart_rx #(.CLKS_PER_BIT(4)) RX (
        .clk(clk), .rst(rst),
        .rx_in(tx_out),           // <-- direct loopback, TX output feeds RX input
        .data_out(rx_data_out),
        .data_valid(rx_valid)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst = 1; tx_start = 0; tx_data = 0;
        #20; rst = 0; #20;

        $display("=== Sending 0x01 via uart_tx, receiving via uart_rx (true loopback) ===");
        tx_data = 8'h01;
        tx_start = 1;
        @(posedge clk); #1;
        tx_start = 0;

        wait (rx_valid == 1);
        $display("RESULT: sent=0x01 received=0x%0h", rx_data_out);
        if (rx_data_out == 8'h01)
            $display("PASS: TX->RX loopback correct");
        else
            $display("FAIL: TX->RX loopback mismatch - this IS a real RTL bug");

        #50;
        $display("=== Sending 0xA5 (alternating bits, stress pattern) ===");
        tx_data = 8'hA5;
        tx_start = 1;
        @(posedge clk); #1;
        tx_start = 0;

        wait (rx_valid == 1);
        $display("RESULT: sent=0xA5 received=0x%0h", rx_data_out);
        if (rx_data_out == 8'hA5)
            $display("PASS: TX->RX loopback correct");
        else
            $display("FAIL: TX->RX loopback mismatch - this IS a real RTL bug");

        $finish;
    end
endmodule
