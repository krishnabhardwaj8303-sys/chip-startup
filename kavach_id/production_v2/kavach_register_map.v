module kavach_register_map(
    input  wire        clk,
    input  wire        rst,
    input  wire        reg_write,
    input  wire        reg_read,
    input  wire [7:0]  reg_addr,
    input  wire [31:0] reg_wdata,
    output reg  [31:0] reg_rdata,
    output reg          reg_ready,

    input  wire         bist_pass_i,
    input  wire         bist_fail_i,
    input  wire         replay_detected_i,
    input  wire [31:0]  stable_response_i,
    input  wire [5:0]   unstable_bit_count_i,

    input  wire         authentication_grant_i,
    input  wire         auth_denied_bist_i,
    input  wire         auth_denied_replay_i,

    input  wire         sequence_violation_i,
    input  wire         chain_complete_i,
    input  wire [3:0]   stages_completed_i,

    input  wire [7:0]   offline_budget_i,
    input  wire         sync_required_i,
    input  wire [15:0]  total_offline_uses_i,

    output reg          bist_start_o,
    output reg          stabilizer_start_o,
    output reg  [31:0]  challenge_o,
    output reg          auth_request_o,
    output reg          sync_complete_o,
    output reg          record_stage_o,
    output reg  [1:0]   stage_id_o,
    output reg  [31:0]  stage_data_o,

    // ── per-chip key programming interface ──
    input  wire         key_locked_i,
    output reg          prog_enable_o,
    output reg  [127:0] prog_key_in_o,

    input  wire [31:0]  ciphertext_i,
    input  wire [15:0]  tx_counter_i,

    // ── NEW: PUF reliability-mask enrollment interface ──
    output reg          enroll_start_o,
    input  wire         enroll_busy_i,
    input  wire         mask_locked_i,
    input  wire [31:0]  reliability_mask_i
);
    // ── REGISTER MAP ──
    // 0x00: CONTROL (write) - bit0=bist_start, bit1=stabilizer_start,
    //                          bit2=auth_request, bit3=sync_complete,
    //                          bit4=record_stage, bit5=enroll_start
    // 0x04: STATUS (read) - bit0=bist_pass, bit1=bist_fail,
    //                        bit2=replay_detected,
    //                        bit3=authentication_grant,
    //                        bit4=auth_denied_bist,
    //                        bit5=auth_denied_replay
    // 0x08: CHALLENGE (write) - 32-bit challenge input
    // 0x0C: RESPONSE (read) - 32-bit stabilized response (RAW,
    //                          unmasked - for diagnostics; the value
    //                          actually used for authentication is
    //                          masked by reliability_mask downstream
    //                          in kavach_id_top.v before scrambling)
    // 0x10: UNSTABLE_COUNT (read) - noise diagnostics
    // 0x14: STAGE_ID (write) - bits[1:0] = provenance stage_id
    // 0x18: STAGE_DATA (write) - 32-bit provenance stage_data
    // 0x1C: PROVENANCE_STATUS (read) - bit0=sequence_violation,
    //                                   bit1=chain_complete,
    //                                   bits[5:2]=stages_completed
    // 0x20: OFFLINE_STATUS (read) - bits[7:0]=offline_budget,
    //                                bit8=sync_required
    // 0x24: OFFLINE_USES (read) - bits[15:0]=total_offline_uses
    // 0x28: KEY_DATA (write) - write 4 TIMES (MSB word first) to load
    //                          one 128-bit key into the shift register
    // 0x2C: KEY_CONTROL (write) - bit0=1 attempts to lock the key
    // 0x30: KEY_STATUS (read) - bit0=key_locked,
    //                            bits[3:1]=key_word_count
    // 0x34: CIPHERTEXT_DATA (read)
    // 0x38: TX_COUNTER (read)
    // 0x40: RELIABILITY_MASK (read) - 32-bit mask, 1=bit unreliable
    // 0x44: MASK_STATUS (read) - bit0=mask_locked, bit1=enroll_busy
    // 0xFC: CHIP_ID (read)

    parameter ADDR_CONTROL     = 8'h00;
    parameter ADDR_STATUS      = 8'h04;
    parameter ADDR_CHALLENGE   = 8'h08;
    parameter ADDR_RESPONSE    = 8'h0C;
    parameter ADDR_UNSTABLE    = 8'h10;
    parameter ADDR_STAGE_ID    = 8'h14;
    parameter ADDR_STAGE_DATA  = 8'h18;
    parameter ADDR_PROVENANCE  = 8'h1C;
    parameter ADDR_OFFLINE     = 8'h20;
    parameter ADDR_OFFLINE_USES = 8'h24;
    parameter ADDR_KEY_DATA    = 8'h28;
    parameter ADDR_KEY_CONTROL = 8'h2C;
    parameter ADDR_KEY_STATUS  = 8'h30;
    parameter ADDR_CIPHERTEXT  = 8'h34;
    parameter ADDR_TX_COUNTER  = 8'h38;
    parameter ADDR_RELIABILITY_MASK = 8'h40;
    parameter ADDR_MASK_STATUS = 8'h44;
    parameter ADDR_CHIP_ID     = 8'hFC;

    reg [2:0] key_word_count;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            reg_rdata           <= 0;
            reg_ready            <= 0;
            bist_start_o         <= 0;
            stabilizer_start_o   <= 0;
            challenge_o          <= 0;
            auth_request_o       <= 0;
            sync_complete_o      <= 0;
            record_stage_o       <= 0;
            stage_id_o           <= 0;
            stage_data_o         <= 0;
            prog_enable_o        <= 0;
            prog_key_in_o        <= 0;
            key_word_count       <= 0;
            enroll_start_o       <= 0;
        end
        else begin
            reg_ready            <= 0;
            bist_start_o         <= 0; // Pulse
            stabilizer_start_o   <= 0; // Pulse
            auth_request_o       <= 0; // Pulse
            sync_complete_o      <= 0; // Pulse
            record_stage_o       <= 0; // Pulse
            prog_enable_o        <= 0; // Pulse
            enroll_start_o       <= 0; // Pulse

            if (reg_write) begin
                reg_ready <= 1;
                case (reg_addr)
                    ADDR_CONTROL: begin
                        bist_start_o       <= reg_wdata[0];
                        stabilizer_start_o <= reg_wdata[1];
                        auth_request_o     <= reg_wdata[2];
                        sync_complete_o    <= reg_wdata[3];
                        record_stage_o     <= reg_wdata[4];
                        enroll_start_o     <= reg_wdata[5];
                    end
                    ADDR_CHALLENGE:  challenge_o  <= reg_wdata;
                    ADDR_STAGE_ID:   stage_id_o   <= reg_wdata[1:0];
                    ADDR_STAGE_DATA: stage_data_o <= reg_wdata;
                    ADDR_KEY_DATA: begin
                        prog_key_in_o <= {prog_key_in_o[95:0], reg_wdata};
                        if (key_word_count < 3'd4)
                            key_word_count <= key_word_count + 1'b1;
                    end
                    ADDR_KEY_CONTROL: begin
                        prog_enable_o  <= reg_wdata[0] & (key_word_count == 3'd4);
                        key_word_count <= 3'd0;
                    end
                    default: ;
                endcase
            end

            if (reg_read) begin
                reg_ready <= 1;
                case (reg_addr)
                    ADDR_STATUS: reg_rdata <= {26'b0,
                                    auth_denied_replay_i,
                                    auth_denied_bist_i,
                                    authentication_grant_i,
                                    replay_detected_i,
                                    bist_fail_i,
                                    bist_pass_i};
                    ADDR_RESPONSE:  reg_rdata <= stable_response_i;
                    ADDR_UNSTABLE:  reg_rdata <= {26'b0, unstable_bit_count_i};
                    ADDR_PROVENANCE: reg_rdata <= {26'b0,
                                    stages_completed_i,
                                    chain_complete_i,
                                    sequence_violation_i};
                    ADDR_OFFLINE:   reg_rdata <= {23'b0,
                                    sync_required_i,
                                    offline_budget_i};
                    ADDR_OFFLINE_USES: reg_rdata <= {16'b0, total_offline_uses_i};
                    ADDR_CIPHERTEXT: reg_rdata <= ciphertext_i;
                    ADDR_TX_COUNTER:  reg_rdata <= {16'b0, tx_counter_i};
                    ADDR_KEY_STATUS: reg_rdata <= {27'b0, key_word_count, key_locked_i};
                    ADDR_RELIABILITY_MASK: reg_rdata <= reliability_mask_i;
                    ADDR_MASK_STATUS: reg_rdata <= {30'b0, enroll_busy_i, mask_locked_i};
                    ADDR_CHIP_ID:   reg_rdata <= 32'h4B415641; // "KAVA" hex
                    default:        reg_rdata <= 32'h0;
                endcase
            end
        end
    end
endmodule
