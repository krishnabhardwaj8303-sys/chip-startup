module alu_tb;

    reg  [3:0] a, b;
    reg  [2:0] op;
    wire [4:0] result;
    wire       zero;

    alu uut (.a(a), .b(b), .op(op), .result(result), .zero(zero));

    initial begin
        $dumpfile("alu.vcd");
        $dumpvars(0, alu_tb);

        // ADD test
        a=4'd5; b=4'd3; op=3'b000; #10;
        if(result==8) $display("✓ ADD: 5+3=%0d PASS", result);
        else          $display("✗ ADD FAIL");

        // SUB test
        a=4'd9; b=4'd4; op=3'b001; #10;
        if(result==5) $display("✓ SUB: 9-4=%0d PASS", result);
        else          $display("✗ SUB FAIL");

        // AND test
        a=4'b1100; b=4'b1010; op=3'b010; #10;
        if(result==4'b1000) $display("✓ AND PASS");
        else                $display("✗ AND FAIL");

        // OR test
        a=4'b1100; b=4'b1010; op=3'b011; #10;
        if(result==4'b1110) $display("✓ OR PASS");
        else                $display("✗ OR FAIL");

        // XOR test
        a=4'b1100; b=4'b1100; op=3'b100; #10;
        if(result==0 && zero==1) $display("✓ XOR + ZERO FLAG PASS");
        else                     $display("✗ XOR FAIL");

        // SHIFT LEFT
        a=4'b0001; b=4'd0; op=3'b110; #10;
        if(result==4'b0010) $display("✓ SHIFT LEFT PASS");
        else                $display("✗ SHIFT LEFT FAIL");

        $display("Day 3 Complete! ALU working!");
        $finish;
    end

endmodule
