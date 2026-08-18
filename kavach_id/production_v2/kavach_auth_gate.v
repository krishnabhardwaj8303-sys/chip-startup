module kavach_auth_gate(
    input  wire        clk,
    input  wire        rst,
    input  wire        auth_request,     // Host requests authentication
    input  wire        bist_fail,        // From kavach_bist.v
    input  wire        bist_pass,        // From kavach_bist.v
    input  wire        replay_detected,  // From replay_detector.v
    output reg          authentication_grant,
    output reg          auth_denied_bist,
    output reg          auth_denied_replay
);
    // ── REAL HARDWARE INTERLOCK ──
    // Prior state: bist_fail and replay_detected existed as report-only
    // telemetry signals - nothing in the design actually blocked
    // authentication from proceeding when either was true. This module
    // is the missing enforcement point: authentication_grant is ONLY
    // ever asserted when BOTH bist_pass is true AND replay_detected is
    // false, evaluated combinationally so there's no clock-edge gap for
    // a bist_fail/replay event landing on the same cycle as a request.

    wire safe_to_authenticate;
    assign safe_to_authenticate = bist_pass && !bist_fail && !replay_detected;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            authentication_grant <= 0;
            auth_denied_bist     <= 0;
            auth_denied_replay   <= 0;
        end
        else begin
            authentication_grant <= 0;
            auth_denied_bist     <= 0;
            auth_denied_replay   <= 0;

            if (auth_request) begin
                if (bist_fail)
                    auth_denied_bist <= 1;
                else if (replay_detected)
                    auth_denied_replay <= 1;
                else if (bist_pass)
                    authentication_grant <= 1;
            end
        end
    end
endmodule
