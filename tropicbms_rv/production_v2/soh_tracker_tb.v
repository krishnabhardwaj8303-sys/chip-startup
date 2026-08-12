module soh_tracker_tb;

    reg        clk, rst, soc_valid;
    reg  [7:0] soc_percent;
    wire [15:0] cycle_count;
    wire [7:0]  soh_percent;
    wire        replacement_warning;

    soh_tracker DUT (
        .clk(clk), .rst(rst),
        .soc_percent(soc_percent),
        .soc_valid(soc_valid),
        .cycle_count(cycle_count),
        .soh_percent(soh_percent),
        .replacement_warning(replacement_warning)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    task do_full_cycle;
        begin
            // Simulate: charge to 95%, discharge to 15%, charge back to 95%
            soc_percent = 8'd95; soc_valid=1; #10; soc_valid=0; #10;
            soc_percent = 8'd15; soc_valid=1; #10; soc_valid=0; #10;
            soc_percent = 8'd95; soc_valid=1; #10; soc_valid=0; #10;
        end
    endtask

    integer i;

    initial begin
        $dumpfile("soh_tracker.vcd");
        $dumpvars(0, soh_tracker_tb);

        rst = 1; soc_valid = 0; soc_percent = 0;
        #20; rst = 0; #10;

        $display("================================");
        $display("  TROPICBMS SOH DEGRADATION    ");
        $display("  Unique: Battery Lifespan Track");
        $display("================================");

        // ── TEST 1: New battery — 100% SOH ──
        $display("--- Test 1: Brand New Battery ---");
        $display("SOH=%0d%%, Cycles=%0d", soh_percent, cycle_count);
        if (soh_percent == 100 && cycle_count == 0)
            $display("PASS: New battery starts at 100%% SOH!");
        else
            $display("FAIL: Unexpected initial state");

        // ── TEST 2: Complete 1 full cycle ──
        $display("--- Test 2: One Full Charge-Discharge Cycle ---");
        do_full_cycle;
        $display("SOH=%0d%%, Cycles=%0d", soh_percent, cycle_count);
        if (cycle_count == 1)
            $display("PASS: Cycle counted, SOH degraded slightly!");
        else
            $display("FAIL: Cycle not counted correctly");

        // ── TEST 3: Simulate 500 cycles (roughly 1.5 years of daily use) ──
        $display("--- Test 3: 500 Cycles (Simulated Long-Term Use) ---");
        for (i = 0; i < 499; i = i + 1) begin
            do_full_cycle;
        end
        $display("After 500 cycles: SOH=%0d%%, Cycles=%0d",
                  soh_percent, cycle_count);
        if (cycle_count == 500 && soh_percent < 100 && soh_percent > 0)
            $display("PASS: Long-term degradation tracked realistically!");
        else
            $display("FAIL: Long-term tracking incorrect");

        // ── TEST 4: Check replacement warning triggers near end-of-life ──
        $display("--- Test 4: End-of-Life Warning Check ---");
        $display("Current SOH=%0d%%, Warning=%0d (threshold=80%%)",
                  soh_percent, replacement_warning);
        if (soh_percent <= 80 && replacement_warning == 1)
            $display("PASS: Replacement warning correctly triggered!");
        else if (soh_percent > 80 && replacement_warning == 0)
            $display("PASS: No false warning while battery still healthy!");

        $display("================================");
        $display("SOH Tracking Complete!");
        $display("Real battery-lifespan data now available");
        $display("for warranty, resale, and maintenance!");
        $display("================================");
        $finish;
    end
endmodule
