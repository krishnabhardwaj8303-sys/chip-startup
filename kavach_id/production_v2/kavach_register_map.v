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

    // ── NEW: provenance_chain.v ──
    input  wire         sequence_violation_i,
    input  wire         chain_complete_i,
    input  wire [3:0]   stages_completed_i,
    input  wire [31:0]  chain_hash_i,

    // ── NEW: offline_verify_counter.v ──
    input  wire [7:0]   offline_budget_i,
    input  wire         verify_allowed_i,
    input  wire         sync_required_i,
    input  wire [15:0]  total_offline_uses_i,

    output reg          bist_start_o,
    output reg          stabilizer_start_o,
    output reg  [31:0]  challenge_o,
    output reg          auth_request_o,

    // ── NEW outputs ──
    output reg          record_stage_o,
    output reg  [1:0]   stage_id_o,
    output reg  [31:0]  stage_data_o,
    output reg          verify_request_o,
    output reg          sync_complete_o
);
    // ── REGISTER MAP ──
    // 0x00: CONTROL (write) - bit0=bist_start, bit1=stabilizer_start,
    //                          bit2=auth_request, bit3=record_stage (NEW),
    //                          bit4=verify_request (NEW)
    // 0x04: STATUS (read) - bit0=bist_pass, bit1=bist_fail,
    //                        bit2=replay_detected, bit3=authentication_grant,
    //                        bit4=auth_denied_bist, bit5=auth_denied_replay
    // 0x08: CHALLENGE (write) - 32-bit challenge input
    // 0x0C: RESPONSE (read) - 32-bit stabilized response
    // 0x10: UNSTABLE_COUNT (read) - noise diagnostics
    // 0x14: PROVENANCE_STATUS (read, NEW) - bit0=sequence_violation,
    //                          bit1=chain_complete, bits[5:2]=stages_completed
    // 0x18: OFFLINE_BUDGET (read, NEW) - bits[7:0]=offline_budget,
    //                          bit8=verify_allowed, bit9=sync_required
    // 0x1C: OFFLINE_CONTROL (write, NEW) - bit0=sync_complete
    // 0x20: STAGE_ID (write, NEW) - [1:0], held until next write
    // 0x24: STAGE_DATA (write, NEW) - [31:0], held until next write
    // 0x28: CHAIN_HASH (read, NEW)
    // 0x2C: TOTAL_OFFLINE_USES (read, NEW)
    // 0xFC: CHIP_ID (read)

    parameter ADDR_CONTROL      = 8'h00;
    parameter ADDR_STATUS       = 8'h04;
    parameter ADDR_CHALLENGE    = 8'h08;
    parameter ADDR_RESPONSE     = 8'h0C;
    parameter ADDR_UNSTABLE     = 8'h10;
    parameter ADDR_PROVENANCE   = 8'h14;
    parameter ADDR_OFFLINE_BUD  = 8'h18;
    parameter ADDR_OFFLINE_CTRL = 8'h1C;
    parameter ADDR_STAGE_ID     = 8'h20;
    parameter ADDR_STAGE_DATA   = 8'h24;
    parameter ADDR_CHAIN_HASH   = 8'h28;
    parameter ADDR_TOTAL_OFFL   = 8'h2C;
    parameter ADDR_CHIP_ID      = 8'hFC;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            reg_rdata          <= 0;
            reg_ready           <= 0;
            bist_start_o        <= 0;
            stabilizer_start_o  <= 0;
            challenge_o         <= 0;
            auth_request_o      <= 0;
            record_stage_o      <= 0;
            stage_id_o          <= 0;
            stage_data_o        <= 0;
            verify_request_o    <= 0;
            sync_complete_o     <= 0;
        end
        else begin
            reg_ready           <= 0;
            bist_start_o         <= 0; // Pulse
            stabilizer_start_o   <= 0; // Pulse
            auth_request_o       <= 0; // Pulse
            record_stage_o       <= 0; // Pulse
            verify_request_o     <= 0; // Pulse
            sync_complete_o      <= 0; // Pulse

            if (reg_write) begin
                reg_ready <= 1;
                case (reg_addr)
                    ADDR_CONTROL: begin
                        bist_start_o       <= reg_wdata[0];
                        stabilizer_start_o <= reg_wdata[1];
                        auth_request_o     <= reg_wdata[2];
                        record_stage_o     <= reg_wdata[3];
                        verify_request_o   <= reg_wdata[4];
                    end
                    ADDR_CHALLENGE:    challenge_o     <= reg_wdata;
                    ADDR_OFFLINE_CTRL: sync_complete_o <= reg_wdata[0];
                    ADDR_STAGE_ID:     stage_id_o      <= reg_wdata[1:0];
                    ADDR_STAGE_DATA:   stage_data_o    <= reg_wdata;
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
                    ADDR_RESPONSE:   reg_rdata <= stable_response_i;
                    ADDR_UNSTABLE:   reg_rdata <= {26'b0, unstable_bit_count_i};
                    ADDR_PROVENANCE: reg_rdata <= {26'b0,
                                    stages_completed_i,
                                    chain_complete_i,
                                    sequence_violation_i};
                    ADDR_OFFLINE_BUD: reg_rdata <= {22'b0,
                                    sync_required_i,
                                    verify_allowed_i,
                                    offline_budget_i};
                    ADDR_CHAIN_HASH:  reg_rdata <= chain_hash_i;
                    ADDR_TOTAL_OFFL:  reg_rdata <= {16'b0, total_offline_uses_i};
                    ADDR_CHIP_ID:     reg_rdata <= 32'h4B415641; // "KAVA" hex
                    default:          reg_rdata <= 32'h0;
                endcase
            end
        end
    end
endmodule
