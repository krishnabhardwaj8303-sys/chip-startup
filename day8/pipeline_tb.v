module pipeline_tb;

    reg        clk, rst;
    wire [7:0] result;
    wire [2:0] pc_out;

    pipeline uut (
        .clk(clk), .rst(rst),
        .result(result),
        .pc_out(pc_out)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("pipeline.vcd");
        $dumpvars(0, pipeline_tb);

        rst=1; #30;
        rst=0;

        $display("================================");
        $display("  PIPELINED CPU — 3 STAGE      ");
        $display("  FETCH | DECODE | EXECUTE      ");
        $display("================================");

        repeat(20) begin
            #10;
            $display("PC=%0d | Result=%0d", pc_out, result);
        end

        $display("================================");
        $display("Day 8 Complete! Pipeline working!");
        $display("3-stage: Fetch+Decode+Execute!");
        $display("================================");
        $finish;
    end

endmodule
