module kavach_auth_formal(
    input wire clk,
    input wire rst,
    input wire auth_request,
    input wire bist_fail,
    input wire bist_pass,
    input wire replay_detected
);
    wire authentication_grant, auth_denied_bist, auth_denied_replay;

    kavach_auth_gate dut (
        .clk(clk), .rst(rst),
        .auth_request(auth_request),
        .bist_fail(bist_fail), .bist_pass(bist_pass),
        .replay_detected(replay_detected),
        .authentication_grant(authentication_grant),
        .auth_denied_bist(auth_denied_bist),
        .auth_denied_replay(auth_denied_replay)
    );

    kavach_safety_assertions assertion_monitor (
        .clk(clk), .rst(rst),
        .replay_detected(replay_detected),
        .authentication_grant(authentication_grant),
        .bist_fail(bist_fail)
    );

    // ── FORMAL ASSUMPTION 1: BIST pass/fail are mutually exclusive ──
    // (documented reasoning: see kavach_bist.v FSM - DONE_PASS and
    // DONE_FAIL are separate states, never simultaneously true)
    always @(*) assume (!(bist_pass && bist_fail));

    // ── FORMAL ASSUMPTION 2: reset actually happens ──
    // Without this, the solver is free to pick an arbitrary initial
    // register state for authentication_grant/etc at cycle 0 (since
    // rst was never observed to be asserted), producing a "counter-
    // example" that requires a power-up state real silicon can never
    // actually be in. Real hardware always sees rst asserted after
    // power-up; this restores that real-world invariant.
    initial assume (rst);

    always @(posedge clk) cover(authentication_grant);
endmodule
