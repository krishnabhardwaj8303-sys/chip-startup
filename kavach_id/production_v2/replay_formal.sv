module replay_formal(
    input wire clk,
    input wire rst,
    input wire challenge_ready,
    input wire [31:0] challenge_in
);
    wire replay_detected;
    wire [31:0] last_challenge;
    wire [7:0] history_hit_count;

    replay_detector dut (
        .clk(clk), .rst(rst),
        .challenge_ready(challenge_ready),
        .challenge_in(challenge_in),
        .replay_detected(replay_detected),
        .last_challenge(last_challenge),
        .history_hit_count(history_hit_count)
    );

    initial assume (rst);

    // ── PROPERTY: history_hit_count never decreases while chip is live ──
    // (a monotonic counter is a strong sanity property: if this fails,
    // something is corrupting the audit trail, which would hide real
    // replay attacks from later review)
    reg [7:0] prev_count;
    reg have_prev;
    initial have_prev = 0;

    always @(posedge clk) begin
        if (rst) begin
            have_prev <= 0;
        end else begin
            if (have_prev)
                assert (history_hit_count >= prev_count);
            prev_count <= history_hit_count;
            have_prev  <= 1;
        end
    end

    always @(posedge clk) cover(replay_detected);
endmodule
