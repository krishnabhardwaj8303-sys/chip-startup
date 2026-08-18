module kavach_safety_assertions(
    input wire clk,
    input wire rst,
    input wire replay_detected,
    input wire authentication_grant,
    input wire bist_fail
);

    // ── PROPERTY 1: Replay detection must block authentication ──
    // authentication_grant is a REGISTERED decision: it reflects the
    // bist_fail/replay_detected values sampled at auth_request time,
    // becoming visible one clock cycle later. Comparing it against
    // THIS cycle's (unconstrained, freely-changing in formal) inputs
    // is a cycle-alignment mismatch, not a real hardware bug - the
    // correct comparison is against $past() values, i.e. the inputs
    // that were actually present when the grant decision was made.
    always @(posedge clk) begin
        if (!rst && $past(1'b1) && !$past(rst))
            assert (!(authentication_grant && $past(replay_detected)));
    end

    // ── PROPERTY 2: Faulty PUF must never authenticate ──
    always @(posedge clk) begin
        if (!rst && $past(1'b1) && !$past(rst))
            assert (!(authentication_grant && $past(bist_fail)));
    end

endmodule
