// Supply-Chain Provenance Chain — real SHA-256 redesign
//
// FIX: mix_hash() previously used a simple XOR-rotate mixing function -
// NOT real cryptography, same class of weakness as encrypted_channel.v's
// old derive_keystream(). Replaced with real NIST FIPS-180-4 SHA-256
// (sha256_core.v): each stage's hash update = SHA256(prev chain_hash ||
// stage_data || stage_id, standard-padded to one 512-bit block).
//
// BREAKING CHANGE: chain_hash widened 32->256 bits (real SHA-256 output
// size - truncating to 32 bits would have thrown away the collision
// resistance the whole point of using SHA-256 is meant to provide).
// chain_hash is not currently wired to any top-level port in
// kavach_id_top.v (.chain_hash() is left unconnected there), so this
// change requires no top-level wiring update.
//
// TIMING CHANGE: sha256_core is a multi-cycle iterative FSM (~120
// clock cycles per hash), not combinational. A new hash_busy output
// is asserted while a hash update is in flight; record_stage is
// IGNORED while hash_busy is high (the FSM only samples record_stage
// in its IDLE state) - the caller (top-level/register map) must wait
// for hash_busy to clear before issuing the next record_stage, the
// same discipline as encrypted_channel.v's AES busy handshake.
//
// All stage-order validation logic (sequence_violation, the exact
// required-predecessor checks per stage_id) is UNCHANGED and still
// fires the cycle after an invalid record_stage - this does not
// depend on the hash function and needs no multi-cycle wait.
module provenance_chain(
    input  wire         clk,
    input  wire         rst,
    input  wire          record_stage,
    input  wire [1:0]    stage_id,
    input  wire [31:0]   stage_data,
    output reg  [255:0]  chain_hash,
    output reg  [3:0]    stages_completed,
    output reg            sequence_violation,
    output reg            chain_complete,
    output reg            hash_busy
);

    wire         sha_done;
    wire [255:0] sha_hash_out;
    reg          sha_start;
    reg  [511:0] sha_block_in;

    sha256_core SHA (
        .clk(clk), .rst(rst),
        .start(sha_start),
        .block_in(sha_block_in),
        .hash_out(sha_hash_out),
        .done(sha_done)
    );

    localparam ST_IDLE      = 1'b0,
               ST_HASH_WAIT = 1'b1;

    reg        state;
    reg [3:0]  pending_stage_mask;
    reg        pending_is_final;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            // Genesis seed (would be PUF-derived on real silicon)
            chain_hash         <= 256'hA5A5A5A5A5A5A5A5A5A5A5A5A5A5A5A5A5A5A5A5A5A5A5A5A5A5A5A5A5A5A5A5;
            stages_completed    <= 4'b0000;
            sequence_violation   <= 1'b0;
            chain_complete        <= 1'b0;
            hash_busy              <= 1'b0;
            state                    <= ST_IDLE;
            sha_start                 <= 1'b0;
            sha_block_in               <= 512'd0;
            pending_stage_mask           <= 4'b0000;
            pending_is_final               <= 1'b0;
        end
        else begin
            sha_start          <= 1'b0;
            sequence_violation <= 1'b0; // pulse

            case (state)
                ST_IDLE: begin
                    if (record_stage) begin
                        case (stage_id)
                            2'd0: begin // Manufacturing — must be FIRST
                                if (stages_completed == 4'b0000) begin
                                    sha_block_in       <= {chain_hash, stage_data, stage_id,
                                                            1'b1, 157'b0, 64'd290};
                                    pending_stage_mask <= 4'b0001;
                                    pending_is_final   <= 1'b0;
                                    sha_start          <= 1'b1;
                                    hash_busy          <= 1'b1;
                                    state              <= ST_HASH_WAIT;
                                end
                                else
                                    sequence_violation <= 1'b1;
                            end
                            2'd1: begin // Distribution — must follow Manufacturing
                                if (stages_completed == 4'b0001) begin
                                    sha_block_in       <= {chain_hash, stage_data, stage_id,
                                                            1'b1, 157'b0, 64'd290};
                                    pending_stage_mask <= 4'b0010;
                                    pending_is_final   <= 1'b0;
                                    sha_start          <= 1'b1;
                                    hash_busy          <= 1'b1;
                                    state              <= ST_HASH_WAIT;
                                end
                                else
                                    sequence_violation <= 1'b1;
                            end
                            2'd2: begin // Retail — must follow Distribution
                                if (stages_completed == 4'b0011) begin
                                    sha_block_in       <= {chain_hash, stage_data, stage_id,
                                                            1'b1, 157'b0, 64'd290};
                                    pending_stage_mask <= 4'b0100;
                                    pending_is_final   <= 1'b0;
                                    sha_start          <= 1'b1;
                                    hash_busy          <= 1'b1;
                                    state              <= ST_HASH_WAIT;
                                end
                                else
                                    sequence_violation <= 1'b1;
                            end
                            2'd3: begin // Consumer — must follow Retail
                                if (stages_completed == 4'b0111) begin
                                    sha_block_in       <= {chain_hash, stage_data, stage_id,
                                                            1'b1, 157'b0, 64'd290};
                                    pending_stage_mask <= 4'b1000;
                                    pending_is_final   <= 1'b1;
                                    sha_start          <= 1'b1;
                                    hash_busy          <= 1'b1;
                                    state              <= ST_HASH_WAIT;
                                end
                                else
                                    sequence_violation <= 1'b1;
                            end
                        endcase
                    end
                end

                ST_HASH_WAIT: begin
                    if (sha_done) begin
                        chain_hash       <= sha_hash_out;
                        stages_completed <= stages_completed | pending_stage_mask;
                        if (pending_is_final)
                            chain_complete <= 1'b1;
                        hash_busy <= 1'b0;
                        state     <= ST_IDLE;
                    end
                end

                default: state <= ST_IDLE;
            endcase
        end
    end
endmodule
