module kavach_safety_assertions(
    input wire clk,
    input wire rst,
    input wire replay_detected,
    input wire authentication_grant,
    input wire bist_fail
);

    // ── PROPERTY 1: Replay detection must block authentication ──
    property p_replay_blocks_auth;
        @(posedge clk) disable iff (rst)
        replay_detected |-> !authentication_grant;
    endproperty
    assert property (p_replay_blocks_auth)
        else $error("SECURITY VIOLATION: Auth granted during replay attack!");

    // ── PROPERTY 2: Faulty PUF must never authenticate ──
    property p_bist_fail_blocks_auth;
        @(posedge clk) disable iff (rst)
        bist_fail |-> ##[0:2] !authentication_grant;
    endproperty
    assert property (p_bist_fail_blocks_auth)
        else $error("SAFETY VIOLATION: Degraded chip granted authentication!");

endmodule
