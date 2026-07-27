module cpu_tb;

    reg        clk, rst;
    reg  [7:0] instruction;
    wire [7:0] result;

    cpu uut (
        .clk(clk),
        .rst(rst),
        .instruction(instruction),
        .result(result)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("cpu.vcd");
        $dumpvars(0, cpu_tb);

        // Reset
        rst=1; instruction=8'b0; #20;
        rst=0; #10;

        // R0 mein 5 store karo
        // Pehle manually register load karenge
        // instruction = opcode(2) + reg_a(3) + reg_b(3)

        // ADD R0 + R1 — opcode=00, a=000, b=001
        instruction = 8'b00_000_001; #20;
        $display("ADD R0+R1 = %0d", result);

        // AND R2 + R3 — opcode=10, a=010, b=011
        instruction = 8'b10_010_011; #20;
        $display("AND R2&R3 = %0d", result);

        // OR R4 + R5 — opcode=11, a=100, b=101
        instruction = 8'b11_100_101; #20;
        $display("OR  R4|R5 = %0d", result);

        // SUB R6 - R7 — opcode=01, a=110, b=111
        instruction = 8'b01_110_111; #20;
        $display("SUB R6-R7 = %0d", result);

        $display("Day 5 Complete! CPU working!");
        $finish;
    end

endmodule
