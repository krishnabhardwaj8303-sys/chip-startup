module offline_verify_tb;

    reg         clk, rst, verify_request, sync_complete;
    wire [7:0]  offline_budget;
    wire         verify_allowed, sync_required;
    wire [15:0]  total_offline_uses;

    offline_verify_counter DUT (
        .clk(clk), .rst(rst),
        .verify_request(verify_request),
        .sync_complete(sync_complete),
        .offline_budget(offline_budget),
        .verify_allowed(verify_allowed),
        .sync_required(sync_required),
        .total_offline_uses(total_offline_uses)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    integer i;
    reg captured_allowed;

    // Task: ek verification request bhejo aur uska result capture karo
    task do_verify;
        begin
            verify_request = 1;
            @(posedge clk); // Yahan verify_allowed update hoga
            #1; // Small delta for signal to settle
            captured_allowed = verify_allowed;
            verify_request = 0;
            @(posedge clk); // Ek extra cycle - state settle ho jaye
        end
    endtask

    initial begin
        $dumpfile("offline_verify.vcd");
        $dumpvars(0, offline_verify_tb);

        rst = 1; verify_request = 0; sync_complete = 0;
        #20; rst = 0; #10;

        $display("================================");
        $display("  KAVACH-ID OFFLINE-FIRST VERIFY");
        $display("  Unique: Rural/no-internet ready ");
        $display("================================");

        // ── TEST 1: Fresh chip — full offline budget ──
        $display("--- Test 1: Fresh Chip Budget ---");
        $display("Initial Budget: %0d", offline_budget);
        if (offline_budget == 50)
            $display("PASS: Chip starts with factory-provisioned budget!");
        else
            $display("FAIL: Unexpected initial budget");

        // ── TEST 2: Normal offline verification — no internet needed ──
        $display("--- Test 2: Field Verification (No Internet, Rural Farmer) ---");
        do_verify;
        $display("Verify Allowed=%0d, Budget Now=%0d", 
                  captured_allowed, offline_budget);
        if (captured_allowed == 1)
            $display("PASS: Verification works WITHOUT internet connection!");
        else
            $display("FAIL: Offline verification blocked incorrectly");

        // ── TEST 3: Use up most of the budget ──
        $display("--- Test 3: Simulating 48 More Offline Verifications ---");
        for (i = 0; i < 48; i = i + 1) begin
            do_verify;
        end
        $display("Budget after 49 total verifications: %0d", offline_budget);
        $display("Sync Required Warning: %0d", sync_required);
        if (offline_budget == 0 && sync_required == 1)
            $display("PASS: Budget correctly exhausted, sync now required!");
        else
            $display("FAIL: Budget tracking incorrect: %0d", offline_budget);

        // ── TEST 4: Try to verify AFTER budget exhausted — should BLOCK ──
        $display("--- Test 4: Attempt Verify With Zero Budget (Security!) ---");
        do_verify;
        $display("Verify Allowed=%0d (should be 0 - blocked!)", captured_allowed);
        if (captured_allowed == 0)
            $display("PASS: Verification correctly BLOCKED - forces sync!");
        else
            $display("FAIL: SECURITY BUG - verified with exhausted budget!");

        // ── TEST 5: Server sync restores budget ──
        $display("--- Test 5: Server Sync (Internet Available Again) ---");
        sync_complete = 1; @(posedge clk); sync_complete = 0; @(posedge clk);
        $display("Budget After Sync: %0d, Sync Required: %0d", 
                  offline_budget, sync_required);
        if (offline_budget == 50 && sync_required == 0)
            $display("PASS: Sync correctly refreshed offline budget!");
        else
            $display("FAIL: Sync did not properly reset state");

        $display("--- Audit: Total Offline Uses Recorded ---");
        $display("Total Offline Uses: %0d", total_offline_uses);

        $display("================================");
        $display("Offline-First Verification Complete!");
        $display("Works in rural India without internet,");
        $display("with security-preserving mandatory sync!");
        $display("================================");
        $finish;
    end
endmodule
