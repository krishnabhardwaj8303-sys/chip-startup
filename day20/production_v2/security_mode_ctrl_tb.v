module security_mode_ctrl_tb;

    reg         clk, rst;
    reg          security_mode, auto_escalate_en;
    reg  [31:0]  transaction_value;
    wire         effective_mode, mode_escalated;

    security_mode_ctrl DUT (
        .clk(clk), .rst(rst),
        .security_mode(security_mode),
        .transaction_value(transaction_value),
        .auto_escalate_en(auto_escalate_en),
        .effective_mode(effective_mode),
        .mode_escalated(mode_escalated)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("security_mode.vcd");
        $dumpvars(0, security_mode_ctrl_tb);

        rst = 1; security_mode = 0; auto_escalate_en = 1;
        transaction_value = 0;
        #20; rst = 0; #10;

        $display("================================");
        $display("  NEELCHIP DUAL-MODE SECURITY  ");
        $display("  Unique: Tiered chip, 2 markets");
        $display("================================");

        // ── TEST 1: LITE device, low-value txn -> stays LITE ──
        $display("--- Test 1: LITE Device, Rs 50 chai payment ---");
        security_mode = 0; transaction_value = 32'd5000; // Rs 50
        #10;
        $display("Effective Mode: %0s, Escalated: %0d",
                  effective_mode ? "FULL" : "LITE", mode_escalated);
        if (effective_mode == 0 && mode_escalated == 0)
            $display("PASS: Low-value txn stays fast/cheap LITE mode!");
        else
            $display("FAIL: Unexpected escalation");

        // ── TEST 2: LITE device, high-value txn -> auto-escalates ──
        $display("--- Test 2: LITE Device, Rs 5000 high-value txn ---");
        security_mode = 0; transaction_value = 32'd500000; // Rs 5000
        #10;
        $display("Effective Mode: %0s, Escalated: %0d",
                  effective_mode ? "FULL" : "LITE", mode_escalated);
        if (effective_mode == 1 && mode_escalated == 1)
            $display("PASS: High-value txn auto-escalated to FULL security!");
        else
            $display("FAIL: High-value txn did not escalate - RISK!");

        // ── TEST 3: FULL-tier device -> always FULL, no escalation flag ──
        $display("--- Test 3: Premium FULL-Tier Device (always secure) ---");
        security_mode = 1; transaction_value = 32'd5000; // Even low value
        #10;
        $display("Effective Mode: %0s, Escalated: %0d",
                  effective_mode ? "FULL" : "LITE", mode_escalated);
        if (effective_mode == 1 && mode_escalated == 0)
            $display("PASS: FULL-tier device always FULL, no false escalation flag!");
        else
            $display("FAIL: Unexpected behavior for FULL-tier device");

        // ── TEST 4: Boundary — exactly at threshold ──
        $display("--- Test 4: Exact Threshold (Rs 2000) ---");
        security_mode = 0; transaction_value = 32'd200000;
        #10;
        $display("Effective Mode: %0s, Escalated: %0d",
                  effective_mode ? "FULL" : "LITE", mode_escalated);
        if (effective_mode == 1)
            $display("PASS: Boundary value correctly triggers escalation!");
        else
            $display("FAIL: Boundary case missed");

        $display("================================");
        $display("Dual-Mode Security Complete!");
        $display("One chip, two market tiers, ");
        $display("with automatic high-value protection!");
        $display("================================");
        $finish;
    end
endmodule
