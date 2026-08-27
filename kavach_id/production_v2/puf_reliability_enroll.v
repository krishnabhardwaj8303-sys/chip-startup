// PUF Reliability Enrollment — chronically-unstable bit masking
//
// PURPOSE: puf_stabilizer.v's 3-sample majority vote corrects noise
// WITHIN a single read-attempt, but (as documented in that file and
// confirmed via puf_bitcheck_tb.v) does not guarantee the SAME bit
// stays consistent ACROSS separate read-attempts if its underlying
// cell is persistently near-metastable. This module runs a one-time
// enrollment process (factory-test time) that samples ENROLL_ROUNDS
// independent stabilized reads of a FIXED reference challenge and
// flags any bit position that ever changed value across those rounds
// as unreliable, producing a permanent reliability_mask.
//
// SCOPE: this is a simple EXCLUSION mask, not a full fuzzy-extractor /
// error-correcting-code scheme. Bits flagged unreliable are forced to
// a fixed value (0) at every future use (see kavach_id_top.v's
// masking of stable_response before it reaches the scrambler), rather
// than corrected via syndrome/helper data. This trades a small amount
// of response entropy (one bit lost per masked position) for
// eliminating cross-read-attempt authentication failures on those
// bits - the same practical tradeoff real PUF-backed products make.
//
// Write-once + lock, same behavioral pattern as key_storage.v: not a
// real OTP/e-fuse hardware macro, a behavioral model of one-time
// programmability for simulation/testing. Real tape-out will need the
// target process's actual OTP/e-fuse macro here.
module puf_reliability_enroll #(
    parameter [3:0] ENROLL_ROUNDS = 4'd8
) (
    input  wire        clk,
    input  wire         rst,
    input  wire          enroll_start,       // pulse: begin enrollment (only takes effect once, before lock)
    input  wire           stable_sample_valid, // pulse: a fresh stabilized response is ready this cycle
    input  wire [31:0]     stable_sample,      // stabilized response for the current enrollment round
    output reg              enroll_busy,        // high while an enrollment round is in progress
    output reg               enroll_done,        // pulses once, the cycle enrollment finishes
    output reg  [31:0]        reliability_mask,   // 1 = bit is unreliable, must be masked out
    output reg                 mask_locked         // 1 once enrollment has completed and locked
);
    reg [3:0] round_ctr;
    reg [3:0] ones_count [0:31];
    integer   i;

    localparam ST_IDLE      = 2'd0,
               ST_ENROLLING = 2'd1,
               ST_DONE      = 2'd2;

    reg [1:0] state;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state            <= ST_IDLE;
            round_ctr        <= 4'd0;
            enroll_busy      <= 1'b0;
            enroll_done      <= 1'b0;
            reliability_mask <= 32'd0;
            mask_locked      <= 1'b0;
            for (i = 0; i < 32; i = i + 1)
                ones_count[i] <= 4'd0;
        end
        else begin
            enroll_done <= 1'b0;

            case (state)
                ST_IDLE: begin
                    if (enroll_start && !mask_locked) begin
                        round_ctr   <= 4'd0;
                        enroll_busy <= 1'b1;
                        for (i = 0; i < 32; i = i + 1)
                            ones_count[i] <= 4'd0;
                        state <= ST_ENROLLING;
                    end
                end

                ST_ENROLLING: begin
                    if (stable_sample_valid) begin
                        for (i = 0; i < 32; i = i + 1)
                            if (stable_sample[i])
                                ones_count[i] <= ones_count[i] + 4'd1;
                        if (round_ctr == ENROLL_ROUNDS - 1'b1) begin
                            state <= ST_DONE;
                        end
                        else begin
                            round_ctr <= round_ctr + 4'd1;
                        end
                    end
                end

                ST_DONE: begin
                    // A bit is reliable iff it was 0 in every round or
                    // 1 in every round (ones_count == 0 or ==
                    // ENROLL_ROUNDS). Anything in between means it
                    // changed value across at least two rounds.
                    for (i = 0; i < 32; i = i + 1)
                        reliability_mask[i] <=
                            (ones_count[i] != 4'd0) && (ones_count[i] != ENROLL_ROUNDS);
                    mask_locked <= 1'b1;
                    enroll_busy <= 1'b0;
                    enroll_done <= 1'b1;
                    state       <= ST_IDLE;
                end

                default: state <= ST_IDLE;
            endcase
        end
    end
endmodule
