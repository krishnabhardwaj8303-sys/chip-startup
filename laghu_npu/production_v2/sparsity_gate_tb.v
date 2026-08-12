module sparsity_gate_tb;

    reg  clk, rst;
    reg  signed [7:0] w00,w01,w02,w03,w10,w11,w12,w13;
    reg  signed [7:0] w20,w21,w22,w23,w30,w31,w32,w33;
    wire [15:0] pe_clock_enable;
    wire [4:0]  zero_weight_count;
    wire [7:0]  power_saved_percent;

    sparsity_gate DUT (
        .clk(clk), .rst(rst),
        .w00(w00), .w01(w01), .w02(w02), .w03(w03),
        .w10(w10), .w11(w11), .w12(w12), .w13(w13),
        .w20(w20), .w21(w21), .w22(w22), .w23(w23),
        .w30(w30), .w31(w31), .w32(w32), .w33(w33),
        .pe_clock_enable(pe_clock_enable),
        .zero_weight_count(zero_weight_count),
        .power_saved_percent(power_saved_percent)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("sparsity.vcd");
        $dumpvars(0, sparsity_gate_tb);

        rst = 1;
        w00=1;w01=2;w02=3;w03=4; w10=5;w11=6;w12=7;w13=8;
        w20=9;w21=10;w22=11;w23=12; w30=13;w31=14;w32=15;w33=16;
        #20; rst = 0; #10;

        $display("================================");
        $display("  LAGHU-NPU SPARSITY-AWARE MAC ");
        $display("  Unique: Power-Efficient Skip  ");
        $display("================================");

        // ── TEST 1: Dense weights — no zeros, all PEs active ──
        $display("--- Test 1: Dense Matrix (No Sparsity) ---");
        #10;
        $display("PE Enable=0x%0h, Zero Count=%0d, Power Saved=%0d%%",
                  pe_clock_enable, zero_weight_count, power_saved_percent);
        if (pe_clock_enable == 16'hFFFF && zero_weight_count == 0)
            $display("PASS: All PEs active for dense weights, no false skip!");
        else
            $display("FAIL: Unexpected gating on dense matrix");

        // ── TEST 2: Pruned model — 50% weights zero (typical pruned NN) ──
        $display("--- Test 2: 50%% Sparse (Typical Pruned Model) ---");
        rst = 1; #10; rst = 0; #10;
        w00=0; w01=2; w02=0; w03=4; 
        w10=0; w11=6; w12=0; w13=8;
        w20=9; w21=0; w22=11; w23=0;
        w30=13; w31=0; w32=15; w33=0;
        #10;
        $display("PE Enable=0x%0h, Zero Count=%0d, Power Saved=%0d%%",
                  pe_clock_enable, zero_weight_count, power_saved_percent);
        if (zero_weight_count == 8 && power_saved_percent == 50)
            $display("PASS: 50%% sparsity correctly detected, 50%% power saved!");
        else
            $display("FAIL: Sparsity detection incorrect");

        // ── TEST 3: Heavily pruned — 75% sparse ──
        $display("--- Test 3: 75%% Sparse (Aggressive Pruning) ---");
        rst = 1; #10; rst = 0; #10;
        w00=0;w01=0;w02=0;w03=4; w10=0;w11=0;w12=0;w13=8;
        w20=0;w21=0;w22=0;w23=12; w30=0;w31=0;w32=0;w33=16;
        #10;
        $display("Zero Count=%0d, Power Saved=%0d%%",
                  zero_weight_count, power_saved_percent);
        if (zero_weight_count == 12 && power_saved_percent == 75)
            $display("PASS: Aggressive pruning saves 75%% power!");
        else
            $display("FAIL: High-sparsity case incorrect");

        // ── TEST 4: Specific PE disable check — w00 zero -> PE0 disabled ──
        $display("--- Test 4: Individual PE Gating Check ---");
        rst = 1; #10; rst = 0; #10;
        w00=0; w01=5; w02=5; w03=5; w10=5;w11=5;w12=5;w13=5;
        w20=5;w21=5;w22=5;w23=5; w30=5;w31=5;w32=5;w33=5;
        #10;
        if (pe_clock_enable[0] == 0 && pe_clock_enable[1] == 1)
            $display("PASS: Only PE0 disabled (matching zero weight w00)!");
        else
            $display("FAIL: PE gating did not target correct PE");

        $display("================================");
        $display("Sparsity-Aware Gating Complete!");
        $display("Zero-weight PEs skip MAC operation,");
        $display("saving real power on pruned models!");
        $display("================================");
        $finish;
    end
endmodule
