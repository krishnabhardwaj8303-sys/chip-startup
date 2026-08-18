module provenance_formal(
    input wire clk,
    input wire rst,
    input wire record_stage,
    input wire [1:0] stage_id,
    input wire [31:0] stage_data
);
    wire [31:0] chain_hash;
    wire [3:0]  stages_completed;
    wire        sequence_violation;
    wire        chain_complete;

    provenance_chain dut (
        .clk(clk), .rst(rst),
        .record_stage(record_stage),
        .stage_id(stage_id),
        .stage_data(stage_data),
        .chain_hash(chain_hash),
        .stages_completed(stages_completed),
        .sequence_violation(sequence_violation),
        .chain_complete(chain_complete)
    );

    initial assume (rst);

    // ── PROPERTY 1: an out-of-order stage attempt is ALWAYS flagged ──
    // For each stage_id, the RTL requires a specific predecessor
    // stages_completed value before accepting it. This property checks
    // the exhaustive converse: whenever record_stage fires with a
    // stages_completed pattern that does NOT match the required
    // predecessor for that stage_id, sequence_violation must be raised
    // on the next cycle - i.e. there is no invalid transition the
    // hardware silently accepts.
    always @(posedge clk) begin
        if (!rst && $past(1'b1) && !$past(rst) && $past(record_stage)) begin
            if ($past(stage_id) == 2'd0 && $past(stages_completed) != 4'b0000)
                assert (sequence_violation);
            if ($past(stage_id) == 2'd1 && $past(stages_completed) != 4'b0001)
                assert (sequence_violation);
            if ($past(stage_id) == 2'd2 && $past(stages_completed) != 4'b0011)
                assert (sequence_violation);
            if ($past(stage_id) == 2'd3 && $past(stages_completed) != 4'b0111)
                assert (sequence_violation);
        end
    end

    // ── PROPERTY 2: chain_complete only after all 4 stages ──
    always @(posedge clk) begin
        if (!rst)
            assert (!chain_complete || stages_completed == 4'b1111);
    end

    always @(posedge clk) cover(chain_complete);
    always @(posedge clk) cover(sequence_violation);
endmodule
