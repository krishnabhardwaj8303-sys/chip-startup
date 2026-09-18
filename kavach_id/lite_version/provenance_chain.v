// Supply-Chain Provenance Chain — LITE variant
//
// Uses a lightweight XOR-rotate mixing function instead of SHA-256.
// This trades cryptographic collision-resistance for a much smaller
// die area, appropriate for high-volume, price-sensitive markets
// (see LITE vs FULL comparison document). Sequence-order validation
// (sequence_violation) is IDENTICAL to the FULL variant — it does not
// depend on the hash function at all.
//
// Security note: mix_hash() is NOT cryptographically secure. It
// detects accidental/casual tampering and out-of-order recording but
// does not resist a dedicated attacker who can compute preimages.
// This is a disclosed, deliberate trade-off for the LITE tier.
module provenance_chain(
    input  wire        clk,
    input  wire        rst,
    input  wire         record_stage,
    input  wire [1:0]   stage_id,
    input  wire [31:0]  stage_data,
    output reg  [31:0]  chain_hash,
    output reg  [3:0]   stages_completed,
    output reg           sequence_violation,
    output reg           chain_complete
);

    function [31:0] mix_hash;
        input [31:0] prev_hash;
        input [31:0] data;
        input [1:0]  id;
        begin
            mix_hash = ({prev_hash[18:0], prev_hash[31:19]} ^ data)
                       + {28'b0, id, ~id};
        end
    endfunction

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            chain_hash         <= 32'hA5A5A5A5;
            stages_completed   <= 4'b0000;
            sequence_violation <= 1'b0;
            chain_complete     <= 1'b0;
        end
        else begin
            sequence_violation <= 1'b0;

            if (record_stage) begin
                case (stage_id)
                    2'd0: begin
                        if (stages_completed == 4'b0000) begin
                            chain_hash       <= mix_hash(chain_hash, stage_data, stage_id);
                            stages_completed <= stages_completed | 4'b0001;
                        end
                        else
                            sequence_violation <= 1'b1;
                    end
                    2'd1: begin
                        if (stages_completed == 4'b0001) begin
                            chain_hash       <= mix_hash(chain_hash, stage_data, stage_id);
                            stages_completed <= stages_completed | 4'b0010;
                        end
                        else
                            sequence_violation <= 1'b1;
                    end
                    2'd2: begin
                        if (stages_completed == 4'b0011) begin
                            chain_hash       <= mix_hash(chain_hash, stage_data, stage_id);
                            stages_completed <= stages_completed | 4'b0100;
                        end
                        else
                            sequence_violation <= 1'b1;
                    end
                    2'd3: begin
                        if (stages_completed == 4'b0111) begin
                            chain_hash       <= mix_hash(chain_hash, stage_data, stage_id);
                            stages_completed <= stages_completed | 4'b1000;
                            chain_complete   <= 1'b1;
                        end
                        else
                            sequence_violation <= 1'b1;
                    end
                endcase
            end
        end
    end
endmodule
