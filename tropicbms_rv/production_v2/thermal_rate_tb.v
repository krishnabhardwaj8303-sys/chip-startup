module thermal_rate_tb;

    reg         clk, rst, sample_tick;
    reg  [11:0] current_temp;
    wire         rate_warning;
    wire signed [12:0] temp_delta;
    wire [11:0]  temp_at_last_sample;

    thermal_rate_detector DUT (
        .clk(clk), .rst(rst),
        .sample_tick(sample_tick),
        .current_temp(current_temp),
        .rate_warning(rate_warning),
        .temp_delta(temp_delta),
        .temp_at_last_sample(temp_at_last_sample)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("thermal_rate.vcd");
        $dumpvars(0, thermal_rate_tb);

        rst = 1; sample_tick = 0; current_temp = 0;
        #20; rst = 0; #10;

        $display("================================");
        $display("  TROPICBMS RATE-OF-CHANGE      ");
        $display("  Unique: Predictive, not reactive");
        $display("================================");

        // ── TEST 1: First sample — establish baseline, no warning ──
        $display("--- Test 1: First Sample (Baseline) ---");
        current_temp = 12'd2000; sample_tick = 1; #10; sample_tick = 0; #10;
        $display("Temp=%0d, Warning=%0d", current_temp, rate_warning);
        if (rate_warning == 0)
            $display("PASS: No false warning on baseline sample!");
        else
            $display("FAIL: Unexpected warning on first sample");

        // ── TEST 2: Slow, normal temperature rise — no warning ──
        $display("--- Test 2: Slow Normal Rise (Sunny Day Heating) ---");
        current_temp = 12'd2050; sample_tick = 1; #10; sample_tick = 0; #10;
        $display("Temp=%0d, Delta=%0d, Warning=%0d", 
                  current_temp, temp_delta, rate_warning);
        if (rate_warning == 0)
            $display("PASS: Normal slow rise does not trigger false alarm!");
        else
            $display("FAIL: False alarm on normal heating");

        // ── TEST 3: RAPID RISE — thermal runaway pattern! ──
        $display("--- Test 3: RAPID RISE (Thermal Runaway Signature!) ---");
        current_temp = 12'd2400; // Jumped by 350 in one sample interval!
        sample_tick = 1; #10; sample_tick = 0; #10;
        $display("Temp=%0d, Delta=%0d, Warning=%0d", 
                  current_temp, temp_delta, rate_warning);
        if (rate_warning == 1)
            $display("PASS: Rapid rise correctly caught BEFORE absolute threshold!");
        else
            $display("FAIL: Dangerous rapid rise MISSED - critical bug!");

        // ── TEST 4: Note this rise happened while still below trip threshold ──
        $display("--- Test 4: Confirm This Is EARLY Warning ---");
        $display("Current temp (%0d) is still below typical trip threshold (~3200)", 
                  current_temp);
        if (current_temp < 12'd3200 && rate_warning == 1)
            $display("PASS: Warning fired BEFORE absolute danger zone - predictive!");
        else
            $display("Note: Check threshold relationship");

        // ── TEST 5: Cooling down — negative delta, no warning ──
        $display("--- Test 5: Cooling Down (Negative Rate) ---");
        current_temp = 12'd2300; sample_tick = 1; #10; sample_tick = 0; #10;
        $display("Temp=%0d, Delta=%0d, Warning=%0d", 
                  current_temp, temp_delta, rate_warning);
        if (rate_warning == 0)
            $display("PASS: Cooling correctly shows no warning!");
        else
            $display("FAIL: False warning while cooling");

        $display("================================");
        $display("Rate-of-Change Detection Complete!");
        $display("Catches thermal runaway EARLY,");
        $display("before absolute threshold is reached!");
        $display("================================");
        $finish;
    end
endmodule
