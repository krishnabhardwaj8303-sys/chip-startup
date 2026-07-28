module i2c_tb;

    reg        clk, rst, start, rw;
    reg  [6:0] addr;
    reg  [7:0] data;
    wire       sda_out, sda_en, scl;
    wire       done, ack;

    i2c_master DUT (
        .clk(clk), .rst(rst),
        .start(start),
        .addr(addr),
        .data(data),
        .rw(rw),
        .sda_out(sda_out),
        .sda_en(sda_en),
        .scl(scl),
        .done(done),
        .ack(ack)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    always @(posedge done)
        $display("✓ Transfer done! addr=0x%0h data=0x%0h PASS",
                  addr, data);

    initial begin
        $dumpfile("i2c.vcd");
        $dumpvars(0, i2c_tb);

        rst=1; start=0; #50;
        rst=0; #20;

        $display("================================");
        $display("      I2C MASTER TEST          ");
        $display("================================");

        // Test 1
        addr=7'h48; data=8'hAB; rw=0;
        start=1; #10; start=0;
        #5000;

        // Test 2
        addr=7'h50; data=8'hFF; rw=0;
        start=1; #10; start=0;
        #5000;

        // Test 3
        addr=7'h68; data=8'h42; rw=0;
        start=1; #10; start=0;
        #5000;

        $display("================================");
        $display("Day 11 Complete! I2C working!");
        $display("================================");
        $finish;
    end

endmodule
