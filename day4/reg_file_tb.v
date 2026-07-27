module reg_file_tb;

    reg        clk, rst, wr_en;
    reg  [2:0] wr_addr, rd_addr1, rd_addr2;
    reg  [7:0] wr_data;
    wire [7:0] rd_data1, rd_data2;

    reg_file uut (
        .clk(clk), .rst(rst),
        .wr_en(wr_en), .wr_addr(wr_addr),
        .wr_data(wr_data),
        .rd_addr1(rd_addr1), .rd_addr2(rd_addr2),
        .rd_data1(rd_data1), .rd_data2(rd_data2)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("reg_file.vcd");
        $dumpvars(0, reg_file_tb);

        rst=1; wr_en=0; #20;
        rst=0;

        wr_en=1; wr_addr=3'd0; wr_data=8'd42; #10;
        rd_addr1=3'd0; #1;
        if(rd_data1==8'd42)
            $display("✓ R0 = 42 PASS");
        else
            $display("✗ R0 FAIL");

        wr_addr=3'd1; wr_data=8'd100; #10;
        wr_addr=3'd2; wr_data=8'd255; #10;

        wr_en=0;
        rd_addr1=3'd1; rd_addr2=3'd2; #10;
        if(rd_data1==8'd100 && rd_data2==8'd255)
            $display("✓ R1=100, R2=255 — Dual Read PASS");
        else
            $display("✗ Dual Read FAIL");

        rst=1; #20; rst=0;
        rd_addr1=3'd0; #10;
        if(rd_data1==8'd0)
            $display("✓ Reset — R0=0 PASS");
        else
            $display("✗ Reset FAIL");

        $display("Day 4 Complete! Register File working!");
        $finish;
    end

endmodule
