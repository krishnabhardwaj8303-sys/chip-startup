module provenance_formal(
    input wire clk,
    input wire rst,
    input wire record_stage,
    input wire [1:0] stage_id,
    input wire [31:0] stage_data
);
    wire [255:0] chain_hash;
    wire [3:0]   stages_completed;
    wire         sequence_violation;
    wire         chain_complete;
    wire         hash_busy;

    provenance_chain dut (
        .clk(clk), .rst(rst),
        .record_stage(record_stage),
        .stage_id(stage_id),
        .stage_data(stage_data),
        .chain_hash(chain_hash),
        .stages_completed(stages_completed),
        .sequence_violation(sequence_violation),
        .chain_complete(chain_complete),
        .hash_busy(hash_busy)
    );

    initial assume (rst);

    // ── PROPERTY 1: an out-of-order stage attempt is ALWAYS flagged ──
    // Only applies when the module was actually IDLE (not mid-hash)
    // when record_stage fired - a request arriving while hash_busy is
    // correctly ignored by the RTL (see property 3), not evaluated
    // for sequence validity.
    always @(posedge clk) begin
        if (!rst && $past(1'b1) && !$past(rst) && $past(record_stage) && !$past(hash_busy)) begin
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

    // ── PROPERTY 3: a record_stage arriving while busy never
    // itself changes stages_completed/chain_complete ──
    // FIX: only checked when hash_busy is STILL high this cycle too
    // (i.e. the FSM is still mid-hash, not completing this cycle).
    // Without this guard, a legitimate hash completion landing the
    // cycle right after a stray record_stage was sampled would look
    // like a false "stray request changed state" violation, even
    // though the change was due to genuine completion of the ORIGINAL
    // (correctly-accepted) hash, not the stray request.
    always @(posedge clk) begin
        if (!rst && $past(1'b1) && !$past(rst) && $past(record_stage) && $past(hash_busy) && hash_busy) begin
            assert (stages_completed == $past(stages_completed));
            assert (chain_complete == $past(chain_complete));
        end
    end

    always @(posedge clk) cover(chain_complete);
    always @(posedge clk) cover(sequence_violation);
endmodule
