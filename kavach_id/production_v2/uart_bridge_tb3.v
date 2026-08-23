module uart_bridge_tb3;

    reg  clk, rst;
    wire uart_link; // TX output feeds directly into bridge's RX input
    wire uart_tx_out_from_bridge;

    wire        reg_write, reg_read;
    wire [7:0]  reg_addr;
    wire [31:0] reg_wdata;
    wire [31:0] reg_rdata;
    reg         reg_ready;

    assign reg_rdata = 32'h11223344;

    // A separate, standalone uart_tx acts as the "external host" sending
    // commands to the bridge - using the REAL, proven uart_tx module
    // instead of a hand-written bit-banger.
    reg        host_tx_start;
    reg  [7:0] host_tx_data;
    wire       host_tx_busy;

    uart_tx #(.CLKS_PER_BIT(4)) HOST_TX (
        .clk(clk), .rst(rst),
        .tx_start(host_tx_start), .data_in(host_tx_data),
        .tx_out(uart_link), .tx_busy(host_tx_busy)
    );

    uart_to_reg_bridge DUT (
        .clk(clk), .rst(rst),
        .uart_rx_in(uart_link),
        .uart_tx_out(uart_tx_out_from_bridge),
        .reg_write(reg_write), .reg_read(reg_read),
        .reg_addr(reg_addr), .reg_wdata(reg_wdata),
        .reg_rdata(reg_rdata), .reg_ready(reg_ready)
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

    initial begin
        rst = 1; host_tx_start = 0; host_tx_data = 0; reg_ready = 1;
        #20; rst = 0; #20;

        $display("=== TEST 1: WRITE frame via real uart_tx (CMD=0x01, ADDR=0x08, DATA=0xAABBCCDD) ===");
        send_byte(8'h01);
        send_byte(8'h08);
        send_byte(8'hAA);
        send_byte(8'hBB);
        send_byte(8'hCC);
        send_byte(8'hDD);
        repeat (10) @(posedge clk);
        $display("RESULT: reg_addr=0x%0h reg_wdata=0x%0h (expect addr=0x08 wdata=0xAABBCCDD)", reg_addr, reg_wdata);
        if (reg_addr == 8'h08 && reg_wdata == 32'hAABBCCDD)
            $display("PASS: write frame decoded correctly");
        else
            $display("FAIL");

        $finish;
    end
endmodule
