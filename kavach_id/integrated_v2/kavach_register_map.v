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

    output reg          bist_start_o,
    output reg          stabilizer_start_o,
    output reg  [31:0]  challenge_o
);
    // ── REGISTER MAP ──
    // 0x00: CONTROL (write) - bit0=bist_start, bit1=stabilizer_start
    // 0x04: STATUS (read) - bit0=bist_pass, bit1=bist_fail, bit2=replay_detected
    // 0x08: CHALLENGE (write) - 32-bit challenge input
    // 0x0C: RESPONSE (read) - 32-bit stabilized response
    // 0x10: UNSTABLE_COUNT (read) - noise diagnostics
    // 0xFC: CHIP_ID (read)

    parameter ADDR_CONTROL   = 8'h00;
    parameter ADDR_STATUS    = 8'h04;
    parameter ADDR_CHALLENGE = 8'h08;
    parameter ADDR_RESPONSE  = 8'h0C;
    parameter ADDR_UNSTABLE  = 8'h10;
    parameter ADDR_CHIP_ID   = 8'hFC;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            reg_rdata          <= 0;
            reg_ready           <= 0;
            bist_start_o        <= 0;
            stabilizer_start_o  <= 0;
            challenge_o         <= 0;
        end
        else begin
            reg_ready          <= 0;
            bist_start_o        <= 0; // Pulse
            stabilizer_start_o  <= 0; // Pulse

            if (reg_write) begin
                reg_ready <= 1;
                case (reg_addr)
                    ADDR_CONTROL: begin
                        bist_start_o       <= reg_wdata[0];
                        stabilizer_start_o <= reg_wdata[1];
                    end
                    ADDR_CHALLENGE: challenge_o <= reg_wdata;
                    default: ;
                endcase
            end

            if (reg_read) begin
                reg_ready <= 1;
                case (reg_addr)
                    ADDR_STATUS: reg_rdata <= {29'b0,
                                    replay_detected_i,
                                    bist_fail_i,
                                    bist_pass_i};
                    ADDR_RESPONSE: reg_rdata <= stable_response_i;
                    ADDR_UNSTABLE: reg_rdata <= {26'b0, unstable_bit_count_i};
                    ADDR_CHIP_ID:  reg_rdata <= 32'h4B415641; // "KAVA" hex
                    default:       reg_rdata <= 32'h0;
                endcase
            end
        end
    end
endmodule
