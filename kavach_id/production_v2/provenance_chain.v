module provenance_chain(
    input  wire        clk,
    input  wire        rst,
    input  wire         record_stage,      // Trigger: naya stage record karo
    input  wire [1:0]   stage_id,          // 0=Mfg, 1=Distribution, 2=Retail, 3=Consumer
    input  wire [31:0]  stage_data,        // Stage-specific data (timestamp, location code, etc)
    output reg  [31:0]  chain_hash,        // Current cumulative chain hash
    output reg  [3:0]   stages_completed,  // Bitmask: kaunse stages ho chuke hain
    output reg           sequence_violation, // Stage order galat hai!
    output reg           chain_complete
);
    // Har product ka supply-chain safar 4 fixed 
    // stages se guzarta hai, isi order mein:
    // Manufacturing(0) -> Distribution(1) -> 
    // Retail(2) -> Consumer(3)
    //
    // Har stage apna data ADD karta hai chain 
    // hash mein (pichle hash ke saath mix karke) — 
    // isse ek "tamper-evident" chain banti hai. 
    // Agar koi stage SKIP ho (jaise Mfg se seedha 
    // Consumer, Distribution/Retail bina), yeh 
    // sequence_violation flag karta hai — yeh 
    // exact wahi pattern hai jo counterfeit 
    // products mein dikhta hai (grey-market 
    // diversion, fake relabeling).

    reg [3:0] last_stage_recorded; // One-hot tracking of last valid stage

    // Simple hash mixing function (real chip mein 
    // yeh SHA-256 hota, yahan lightweight XOR-rotate 
    // mixing use kar rahe hain simulation ke liye)
    function [31:0] mix_hash;
        input [31:0] prev_hash;
        input [31:0] new_data;
        input [1:0]  stage;
        begin
            mix_hash = {prev_hash[27:0], prev_hash[31:28]} ^ 
                       new_data ^ {28'h0, stage, stage};
        end
    endfunction

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            chain_hash          <= 32'hA5A5A5A5; // Genesis seed (would be PUF-derived)
            stages_completed     <= 4'b0000;
            sequence_violation   <= 0;
            chain_complete        <= 0;
            last_stage_recorded  <= 4'b0000;
        end
        else if (record_stage) begin
            sequence_violation <= 0;

            case (stage_id)
                2'd0: begin // Manufacturing — must be FIRST
                    if (stages_completed == 4'b0000) begin
                        chain_hash        <= mix_hash(chain_hash, stage_data, stage_id);
                        stages_completed  <= stages_completed | 4'b0001;
                    end
                    else
                        sequence_violation <= 1; // Mfg recorded twice or out of order!
                end

                2'd1: begin // Distribution — must follow Manufacturing
                    if (stages_completed == 4'b0001) begin
                        chain_hash        <= mix_hash(chain_hash, stage_data, stage_id);
                        stages_completed  <= stages_completed | 4'b0010;
                    end
                    else
                        sequence_violation <= 1; // Skipped Mfg or wrong order!
                end

                2'd2: begin // Retail — must follow Distribution
                    if (stages_completed == 4'b0011) begin
                        chain_hash        <= mix_hash(chain_hash, stage_data, stage_id);
                        stages_completed  <= stages_completed | 4'b0100;
                    end
                    else
                        sequence_violation <= 1; // Skipped Distribution!
                end

                2'd3: begin // Consumer — must follow Retail
                    if (stages_completed == 4'b0111) begin
                        chain_hash        <= mix_hash(chain_hash, stage_data, stage_id);
                        stages_completed  <= stages_completed | 4'b1000;
                        chain_complete     <= 1;
                    end
                    else
                        sequence_violation <= 1; // Skipped Retail - grey market!
                end
            endcase
        end
    end
endmodule
