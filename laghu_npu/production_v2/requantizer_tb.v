module requantizer_tb;

    reg  signed [31:0] acc_in;
    reg         [4:0]  shift_amt;
    wire signed [7:0]  quant_out;
    wire               overflow_flag, underflow_flag;

    requantizer DUT (
        .acc_in(acc_in),
        .shift_amt(shift_amt),
        .quant_out(quant_out),
        .overflow_flag(overflow_flag),
        .underflow_flag(underflow_flag)
    );

    initial begin
        $dumpfile("requantizer.vcd");
        $dumpvars(0, requantizer_tb);

        $display("================================");
        $display("  LAGHU-NPU PRODUCTION PHASE 1 ");
        $display("  Saturation/Overflow Protection ");
        $display("================================");

        // Test 1: Normal value — no saturation needed
        $display("--- Test 1: Normal Value ---");
        acc_in = 32'sd6400; shift_amt = 5'd6; #10; // 6400>>6 = 100
        $display("Input=6400, shift=6 -> Output=%0d, Overflow=%0d", 
                  quant_out, overflow_flag);
        if (quant_out == 100 && overflow_flag == 0)
            $display("PASS: Normal value passes through correctly!");
        else
            $display("FAIL: Unexpected result");

        // Test 2: Overflow — value bahut bada hai
        $display("--- Test 2: OVERFLOW Case ---");
        acc_in = 32'sd50000; shift_amt = 5'd6; #10; // Would be 781 - way over INT8
        $display("Input=50000, shift=6 -> Output=%0d, Overflow=%0d", 
                  quant_out, overflow_flag);
        if (quant_out == 127 && overflow_flag == 1)
            $display("PASS: Overflow correctly saturated to 127!");
        else
            $display("FAIL: Overflow not handled correctly");

        // Test 3: Underflow — negative value bahut chhota hai
        $display("--- Test 3: UNDERFLOW Case ---");
        acc_in = -32'sd50000; shift_amt = 5'd6; #10;
        $display("Input=-50000, shift=6 -> Output=%0d, Underflow=%0d", 
                  quant_out, underflow_flag);
        if (quant_out == -128 && underflow_flag == 1)
            $display("PASS: Underflow correctly saturated to -128!");
        else
            $display("FAIL: Underflow not handled correctly");

        // Test 4: Boundary case — exactly at limit
        $display("--- Test 4: Boundary Value (127) ---");
        acc_in = 32'sd8128; shift_amt = 5'd6; #10; // 8128>>6 = 127 exactly
        $display("Input=8128, shift=6 -> Output=%0d, Overflow=%0d", 
                  quant_out, overflow_flag);
        if (quant_out == 127 && overflow_flag == 0)
            $display("PASS: Exact boundary handled without false overflow!");
        else
            $display("FAIL: Boundary case incorrect");

        $display("================================");
        $display("Phase 1 Complete!");
        $display("No more silent wraparound bugs!");
        $display("Production-safe quantization verified!");
        $display("================================");
        $finish;
    end
endmodule
