module uart_bridge_read_tb;

    reg  clk, rst;
    wire uart_link;
    wire uart_tx_out_from_bridge;

    wire        reg_write, reg_read;
    wire [7:0]  reg_addr;
    wire [31:0] reg_wdata;
    wire [31:0] reg_rdata;
    reg         reg_ready;

    assign reg_rdata = 32'h5566_7788; // known value the "register map" would return

    reg        host_tx_start;
    reg  [7:0] host_tx_data;
    wire       host_tx_busy;

    uart_tx #(.CLKS_PER_BIT(4)) HOST_TX (
        .clk(clk), .rst(rst),
        .tx_start(host_tx_start), .data_in(host_tx_data),
        .tx_out(uart_link), .tx_busy(host_tx_busy)
    );

    // A second uart_rx acts as the "host's receiver", listening to the
    // bridge's response on uart_tx_out_from_bridge.
    wire [7:0] host_rx_byte;
    wire       host_rx_valid;

    uart_rx #(.CLKS_PER_BIT(4)) HOST_RX (
        .clk(clk), .rst(rst),
        .rx_in(uart_tx_out_from_bridge),
        .data_out(host_rx_byte),
        .data_valid(host_rx_valid)
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

    reg [31:0] received_bytes;
    integer byte_count;

    always @(posedge clk) begin
        if (host_rx_valid) begin
            received_bytes <= {received_bytes[23:0], host_rx_byte};
            byte_count <= byte_count + 1;
            $display("[t=%0t] host received byte 0x%0h (byte #%0d)", $time, host_rx_byte, byte_count + 1);
        end
    end

    initial begin
        rst = 1; host_tx_start = 0; host_tx_data = 0; reg_ready = 1; byte_count = 0; received_bytes = 0;
        #20; rst = 0; #20;

        $display("=== TEST: READ frame (CMD=0x02, ADDR=0x04), expect 4 response bytes = 0x55667788 ===");
        send_byte(8'h02);
        send_byte(8'h04);
        send_byte(8'h00);
        send_byte(8'h00);
        send_byte(8'h00);
        send_byte(8'h00);

        repeat (300) @(posedge clk); // let all 4 response bytes fully shift out

        $display("RESULT: reg_addr=0x%0h (expect 0x04), assembled response=0x%0h (expect 0x55667788), byte_count=%0d (expect 4)",
                   reg_addr, received_bytes, byte_count);
        if (reg_addr == 8'h04 && received_bytes == 32'h5566_7788 && byte_count == 4)
            $display("PASS: read frame correctly triggers register read and returns all 4 bytes");
        else
            $display("FAIL");

        $finish;
    end
endmodule
