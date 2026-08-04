module production_p2_tb;

    reg         clk, rst;

    // BIST signals
    reg          start_bist;
    wire         bist_pass, bist_fail, bist_done;
    reg  signed [31:0] test_mac_result;

    // Hazard detector signals
    reg          load_weights, load_activations, compute_start;
    wire         hazard_detected;
    wire [1:0]   hazard_type;

    npu_bist BIST (
        .clk(clk), .rst(rst),
        .start_bist(start_bist),
        .bist_pass(bist_pass),
        .bist_fail(bist_fail),
        .bist_done(bist_done),
        .test_mac_result(test_mac_result)
    );

    hazard_detector HAZARD (
        .clk(clk), .rst(rst),
        .load_weights(load_weights),
        .load_activations(load_activations),
        .compute_start(compute_start),
        .hazard_detected(hazard_detected),
        .hazard_type(hazard_type)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("production_p2.vcd");
        $dumpvars(0, production_p2_tb);

        rst = 1;
        start_bist = 0; test_mac_result = 0;
        load_weights = 0; load_activations = 0; compute_start = 0;
        #20; rst = 0; #10;

        $display("================================");
        $display("  LAGHU-NPU PRODUCTION PHASE 2 ");
        $display("  BIST + Hazard Detection        ");
        $display("================================");

        // ── TEST 1: BIST — Healthy PE Array ──
        $display("--- Test 1: BIST (Healthy Chip) ---");
        test_mac_result = 32'sd15; // Correct: 5x3=15
        start_bist = 1; #10; start_bist = 0;
        wait(bist_done);
        if (bist_pass)
            $display("PASS: BIST passed - PE array is healthy!");
        else
            $display("FAIL: BIST failed unexpectedly");
        #20;

        // ── TEST 2: BIST — Faulty PE Array Detection ──
        $display("--- Test 2: BIST (Faulty PE Array) ---");
        rst = 1; #10; rst = 0; #10;
        test_mac_result = 32'sd99; // WRONG - simulate silicon defect
        start_bist = 1; #10; start_bist = 0;
        wait(bist_done);
        if (bist_fail)
            $display("PASS: BIST correctly caught faulty MAC unit!");
        else
            $display("FAIL: BIST missed the defect");
        #20;

        // ── TEST 3: No Hazard — Normal Sequential Operation ──
        $display("--- Test 3: Normal Operation (No Hazard) ---");
        rst = 1; #10; rst = 0; #10;
        load_weights = 1; #10; load_weights = 0; #10;
        compute_start = 1; #10; compute_start = 0;
        if (hazard_detected == 0)
            $display("PASS: No false hazard in normal sequential flow!");
        else
            $display("FAIL: False hazard detected");

        // ── TEST 4: Weight Race Condition ──
        $display("--- Test 4: Weight Load + Compute RACE ---");
        load_weights = 1; compute_start = 1; #10;
        if (hazard_detected && hazard_type == 2'b01)
            $display("PASS: Weight race condition correctly detected!");
        else
            $display("FAIL: Race condition missed - CRITICAL BUG!");
        load_weights = 0; compute_start = 0; #10;

        // ── TEST 5: Activation Race Condition ──
        $display("--- Test 5: Activation Load + Compute RACE ---");
        load_activations = 1; compute_start = 1; #10;
        if (hazard_detected && hazard_type == 2'b10)
            $display("PASS: Activation race condition correctly detected!");
        else
            $display("FAIL: Race condition missed!");

        $display("================================");
        $display("Phase 2 Complete!");
        $display("BIST + Pipeline Hazard Detection verified!");
        $display("No more silent wrong-AI-output bugs!");
        $display("================================");
        $finish;
    end
endmodule
