module cpu_v2_tb;

    reg        clk, rst;
    wire [7:0] result;
    wire [2:0] pc_out;

    cpu_v2 uut (
        .clk(clk), .rst(rst),
        .result(result),
        .pc_out(pc_out)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("cpu_v2.vcd");
        $dumpvars(0, cpu_v2_tb);

        rst=1; #20;
        rst=0;

        // 8 instructions execute karo
        repeat(10) begin
            #10;
            $display("PC=%0d | Instruction running | Result=%0d",
                      pc_out, result);
        end

        $display("Day 6 Complete! CPU with Program Counter working!");
        $finish;
    end

endmodule
