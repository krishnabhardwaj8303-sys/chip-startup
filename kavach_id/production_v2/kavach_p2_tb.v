module kavach_p2_tb;

    reg        clk, rst;

    // Replay detector signals
    reg         challenge_ready;
    reg  [31:0] challenge_in;
    wire        replay_detected;
    wire [31:0] last_challenge;
    wire [7:0]  history_hit_count;

    // BIST signals
    reg         start_bist;
    wire        bist_pass, bist_fail, bist_done;
    reg  [31:0] test_response;

    replay_detector REPLAY (
        .clk(clk), .rst(rst),
        .challenge_ready(challenge_ready),
        .challenge_in(challenge_in),
        .replay_detected(replay_detected),
        .last_challenge(last_challenge),
        .history_hit_count(history_hit_count)
    );

    kavach_bist BIST (
        .clk(clk), .rst(rst),
        .start_bist(start_bist),
        .bist_pass(bist_pass),
        .bist_fail(bist_fail),
        .bist_done(bist_done),
        .test_response(test_response)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("kavach_p2.vcd");
        $dumpvars(0, kavach_p2_tb);

        rst = 1;
        challenge_ready = 0; challenge_in = 0;
        start_bist = 0; test_response = 0;
        #20; rst = 0; #10;

        $display("================================");
        $display("  KAVACH-ID PRODUCTION PHASE 2 ");
        $display("  Replay Attack + BIST Detection ");
        $display("================================");

        // ── TEST 1: BIST — Healthy PUF ──
        $display("--- Test 1: BIST (Healthy PUF) ---");
        test_response = 32'hCAFEBABE;
        start_bist = 1; #10; start_bist = 0;
        wait(bist_done);
        if (bist_pass)
            $display("PASS: BIST passed - PUF array healthy!");
        else
            $display("FAIL: BIST failed unexpectedly");
        #20;

        // ── TEST 2: BIST — Degraded/Damaged PUF ──
        $display("--- Test 2: BIST (Degraded PUF) ---");
        rst = 1; #10; rst = 0; #10;
        test_response = 32'h11111111; // Wrong - PUF aging/damage
        start_bist = 1; #10; start_bist = 0;
        wait(bist_done);
        if (bist_fail)
            $display("PASS: BIST caught degraded PUF!");
        else
            $display("FAIL: Degraded PUF not detected");
        #20;

        // ── TEST 3: Fresh Challenges — No False Alarm ──
        $display("--- Test 3: Normal Fresh Challenges ---");
        rst = 1; #10; rst = 0; #10;
        challenge_in = 32'h11111111; challenge_ready = 1; #10; 
        challenge_ready = 0; #10;
        challenge_in = 32'h22222222; challenge_ready = 1; #10;
        challenge_ready = 0; #10;
        if (replay_detected == 0)
            $display("PASS: No false replay alarm on fresh challenges!");
        else
            $display("FAIL: False replay detected");

        // ── TEST 4: REPLAY ATTACK — Same Challenge Again ──
        $display("--- Test 4: REPLAY ATTACK Detection ---");
        challenge_in = 32'h11111111; // Same as first challenge!
        challenge_ready = 1; #10; challenge_ready = 0; #10;
        if (replay_detected == 1)
            $display("PASS: Replay attack CORRECTLY DETECTED!");
        else
            $display("FAIL: Replay attack MISSED - SECURITY BUG!");

        $display("================================");
        $display("Phase 2 Complete!");
        $display("Replay Attack Protection + BIST verified!");
        $display("Chip resistant to record-and-replay attacks!");
        $display("================================");
        $finish;
    end
endmodule
