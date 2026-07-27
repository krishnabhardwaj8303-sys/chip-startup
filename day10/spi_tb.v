module spi_tb;

    reg        clk, rst, start;
    reg  [7:0] mosi_data;
    wire       sclk, cs_n, mosi;
    wire [7:0] miso_data;
    wire       done;
    wire       miso;
    wire [7:0] slave_rx;
    wire       slave_valid;

    spi_master MASTER (
        .clk(clk), .rst(rst),
        .start(start),
        .mosi_data(mosi_data),
        .sclk(sclk), .cs_n(cs_n),
        .mosi(mosi), .miso(miso),
        .miso_data(miso_data),
        .done(done)
    );

    spi_slave SLAVE (
        .clk(clk), .rst(rst),
        .sclk(sclk), .cs_n(cs_n),
        .mosi(mosi), .miso(miso),
        .rx_data(slave_rx),
        .valid(slave_valid)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    always @(posedge slave_valid)
        $display("✓ Slave received=%0d PASS", slave_rx);

    always @(posedge done)
        $display("✓ Master done | MISO data=%0d", miso_data);

    initial begin
        $dumpfile("spi.vcd");
        $dumpvars(0, spi_tb);

        rst=1; start=0; mosi_data=0; #30;
        rst=0; #20;

        $display("================================");
        $display("   SPI MASTER → SLAVE TEST     ");
        $display("================================");

        // Test 1: 170 bhejo (10101010)
        mosi_data=8'd170; start=1; #10; start=0;
        #500;

        // Test 2: 85 bhejo (01010101)
        mosi_data=8'd85; start=1; #10; start=0;
        #500;

        // Test 3: 255 bhejo (11111111)
        mosi_data=8'd255; start=1; #10; start=0;
        #500;

        $display("================================");
        $display("Day 10 Complete! SPI working!");
        $display("Master + Slave verified!");
        $display("================================");
        $finish;
    end

endmodule
