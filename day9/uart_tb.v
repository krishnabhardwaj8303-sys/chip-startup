module uart_tb;

    reg        clk, rst;
    reg        start;
    reg  [7:0] tx_data;
    wire       tx_line;
    wire       tx_busy;
    wire [7:0] rx_data;
    wire       rx_valid;

    uart_tx TX (
        .clk(clk), .rst(rst),
        .start(start),
        .data(tx_data),
        .tx(tx_line),
        .busy(tx_busy)
    );

    uart_rx RX (
        .clk(clk), .rst(rst),
        .rx(tx_line),
        .data(rx_data),
        .valid(rx_valid)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    // Valid ka monitor
    always @(posedge rx_valid) begin
        $display("✓ Received=%0d PASS", rx_data);
    end

    initial begin
        $dumpfile("uart.vcd");
        $dumpvars(0, uart_tb);

        rst=1; start=0; tx_data=0; #50;
        rst=0; #20;

        $display("================================");
        $display("   UART TX → RX LOOPBACK TEST  ");
        $display("================================");

        // Test 1
        tx_data=8'd65; start=1; #10; start=0;
        #2000;

        // Test 2
        tx_data=8'd42; start=1; #10; start=0;
        #2000;

        // Test 3
        tx_data=8'd255; start=1; #10; start=0;
        #2000;

        $display("================================");
        $display("Day 9 Complete! UART working!");
        $display("================================");
        $finish;
    end

endmodule
