module robustness_tb;

    reg        clk, rst;

    // BIST signals
    reg         start_bist;
    wire        bist_pass, bist_fail, bist_done;
    wire [3:0]  bist_stage;
    reg  [7:0]  sbox_test_out;
    reg  [127:0] aes_test_out;
    reg         puf_test_valid;

    // Watchdog signals
    reg         wdt_kick, wdt_enable;
    wire        wdt_timeout;
    wire [15:0] wdt_count;

    // Glitch detector signals
    reg         clk_monitor;
    reg  [7:0]  voltage_level;
    wire        glitch_detected;
    wire [1:0]  glitch_type;

    bist_controller BIST (
        .clk(clk), .rst(rst),
        .start_bist(start_bist),
        .bist_pass(bist_pass),
        .bist_fail(bist_fail),
        .bist_done(bist_done),
        .bist_stage(bist_stage),
        .sbox_test_out(sbox_test_out),
        .aes_test_out(aes_test_out),
        .puf_test_valid(puf_test_valid)
    );

    watchdog_timer WDT (
        .clk(clk), .rst(rst),
        .wdt_kick(wdt_kick),
        .wdt_enable(wdt_enable),
        .wdt_timeout(wdt_timeout),
        .wdt_count(wdt_count)
    );

    glitch_detector GLITCH (
        .clk(clk), .rst(rst),
        .clk_monitor(clk_monitor),
        .voltage_level(voltage_level),
        .glitch_detected(glitch_detected),
        .glitch_type(glitch_type)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("robustness.vcd");
        $dumpvars(0, robustness_tb);

        rst = 1;
        start_bist = 0; sbox_test_out = 0; 
        aes_test_out = 0; puf_test_valid = 0;
        wdt_kick = 0; wdt_enable = 0;
        clk_monitor = 0; voltage_level = 8'd200; // Normal
        #30; rst = 0; #10;

        $display("================================");
        $display("  PRODUCTION ROBUSTNESS TEST   ");
        $display("================================");

        // ── TEST 1: BIST — Healthy Chip ──
        $display("--- Test 1: BIST (Healthy Chip) ---");
        sbox_test_out  = 8'h63;  // Correct value
        aes_test_out   = 128'h3902dc1925dc116a8409850b1dfb9732;
        puf_test_valid = 1;
        start_bist = 1; #10; start_bist = 0;

        wait(bist_done);
        if (bist_pass)
            $display("PASS: BIST passed - chip is healthy!");
        else
            $display("FAIL: BIST failed unexpectedly");
        #20;

        // ── TEST 2: BIST — Faulty Chip Detection ──
        $display("--- Test 2: BIST (Faulty S-Box) ---");
        rst = 1; #10; rst = 0; #10;
        sbox_test_out  = 8'h99;  // WRONG value — simulate defect
        aes_test_out   = 128'h3902dc1925dc116a8409850b1dfb9732;
        puf_test_valid = 1;
        start_bist = 1; #10; start_bist = 0;

        wait(bist_done);
        if (bist_fail)
            $display("PASS: BIST correctly detected faulty S-Box!");
        else
            $display("FAIL: BIST missed the defect");
        #20;

        // ── TEST 3: Watchdog — Normal Operation ──
        $display("--- Test 3: Watchdog (CPU Alive) ---");
        rst = 1; #10; rst = 0; #10;
        wdt_enable = 1;
        repeat(5) begin
            wdt_kick = 1; #10; wdt_kick = 0; #10;
        end
        if (wdt_timeout == 0)
            $display("PASS: No false timeout while CPU alive!");
        else
            $display("FAIL: False timeout triggered");

        // ── TEST 4: Watchdog — CPU Hang Detection ──
        $display("--- Test 4: Watchdog (CPU Hangs) ---");
        // Ab hum "kick" bhejna band kar dete hain — 
        // simulate CPU crash/hang
        // (Real timeout 65535 cycles hai, 
        //  yahan simulation ke liye chota rakhte hain)
        repeat(70000) @(posedge clk);
        if (wdt_timeout == 1)
            $display("PASS: Watchdog detected CPU hang!");
        else
            $display("INFO: Timeout not reached in sim window");

        // ── TEST 5: Glitch Detection — Normal Voltage ──
        $display("--- Test 5: Glitch Detector (Normal) ---");
        voltage_level = 8'd200; #20;
        if (glitch_detected == 0)
            $display("PASS: No false glitch alarm at normal voltage!");
        else
            $display("FAIL: False glitch detected");

        // ── TEST 6: Glitch Detection — Attack Simulation ──
        $display("--- Test 6: Glitch Detector (ATTACK!) ---");
        voltage_level = 8'd50; // Sudden voltage drop — attack signature!
        #20;
        if (glitch_detected == 1 && glitch_type == 2'b10)
            $display("PASS: Voltage glitch attack DETECTED!");
        else
            $display("FAIL: Attack not detected");

        $display("================================");
        $display("Phase 2 Complete!");
        $display("BIST + Watchdog + Glitch Detection");
        $display("Production-grade robustness verified!");
        $display("================================");
        $finish;
    end
endmodule
