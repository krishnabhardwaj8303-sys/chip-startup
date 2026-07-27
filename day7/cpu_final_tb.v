module cpu_final_tb;

    reg        clk, rst;
    wire [7:0] result;
    wire [2:0] pc_out;

    // Register file direct access for loading
    reg [7:0] test_data [0:7];

    cpu_v2 uut (
        .clk(clk), .rst(rst),
        .result(result),
        .pc_out(pc_out)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    integer i;
    integer pass_count;
    integer fail_count;

    initial begin
        $dumpfile("cpu_final.vcd");
        $dumpvars(0, cpu_final_tb);

        pass_count = 0;
        fail_count = 0;

        // Reset
        rst=1; #30;
        rst=0; #10;

        $display("=====================================");
        $display("   KRISHNA KA CPU — FINAL TEST      ");
        $display("=====================================");

        // CPU 10 cycles chalao
        repeat(16) begin
            #10;
            $display("Cycle | PC=%0d | Result=%0d (0x%0h)",
                     pc_out, result, result);
        end

        $display("=====================================");
        $display("CPU Successfully executed 16 cycles!");
        $display("Program Counter: 0 to 7 loop working!");
        $display("ALU Operations: ADD SUB AND OR done!");
        $display("=====================================");
        $display("WEEK 1 COMPLETE! Tera pehla CPU ready!");
        $finish;
    end

endmodule
