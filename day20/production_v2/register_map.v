module register_map(
    input  wire        clk,
    input  wire        rst,
    // External interface — koi bhi controller isse baat karta hai
    input  wire        reg_write,
    input  wire        reg_read,
    input  wire [7:0]  reg_addr,
    input  wire [31:0] reg_wdata,
    output reg  [31:0] reg_rdata,
    output reg         reg_ready,

    // Internal chip status signals (input)
    input  wire        bist_pass_i,
    input  wire        bist_fail_i,
    input  wire        wdt_timeout_i,
    input  wire        glitch_detected_i,
    input  wire        glitch_now_i,      // Combinational — turant interlock ke liye
    input  wire        aes_done_i,
    input  wire [127:0] aes_result_i,

    // Internal control signals (output) — 
    // yeh register set hone pe chip ko command dete hain
    output reg         aes_start_o,
    output reg         bist_start_o,
    output reg         wdt_enable_o,
    output reg  [127:0] aes_key_o,
    output reg  [127:0] aes_plaintext_o
);
    // ── REGISTER MAP — Datasheet Standard ──
    // 0x00: CONTROL register (write)
    //   bit 0: aes_start
    //   bit 1: bist_start  
    //   bit 2: wdt_enable
    // 0x04: STATUS register (read-only)
    //   bit 0: aes_done
    //   bit 1: bist_pass
    //   bit 2: bist_fail
    //   bit 3: wdt_timeout
    //   bit 4: glitch_detected
    // 0x08-0x18: AES_KEY (128-bit, 4 words)
    // 0x1C-0x2C: AES_PLAINTEXT (128-bit, 4 words)
    // 0x30-0x40: AES_RESULT (128-bit, read-only, 4 words)
    // 0xFC: CHIP_ID (read-only) — device identification

    parameter ADDR_CONTROL    = 8'h00;
    parameter ADDR_STATUS     = 8'h04;
    parameter ADDR_KEY_0      = 8'h08;
    parameter ADDR_KEY_1      = 8'h0C;
    parameter ADDR_KEY_2      = 8'h10;
    parameter ADDR_KEY_3      = 8'h14;
    parameter ADDR_PLAIN_0    = 8'h18;
    parameter ADDR_PLAIN_1    = 8'h1C;
    parameter ADDR_PLAIN_2    = 8'h20;
    parameter ADDR_PLAIN_3    = 8'h24;
    parameter ADDR_RESULT_0   = 8'h28;
    parameter ADDR_RESULT_1   = 8'h2C;
    parameter ADDR_RESULT_2   = 8'h30;
    parameter ADDR_RESULT_3   = 8'h34;
    parameter ADDR_CHIP_ID    = 8'hFC;

    parameter CHIP_ID_VALUE   = 32'h4E45454C; // "NEEL" in ASCII hex

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            reg_rdata       <= 0;
            reg_ready       <= 0;
            aes_start_o     <= 0;
            bist_start_o    <= 0;
            wdt_enable_o    <= 0;
            aes_key_o       <= 0;
            aes_plaintext_o <= 0;
        end
        else begin
            reg_ready   <= 0;
            aes_start_o  <= 0; // Pulse — auto-clear
            bist_start_o <= 0; // Pulse — auto-clear

            // ── WRITE OPERATIONS ──
            if (reg_write) begin
                reg_ready <= 1;
                case (reg_addr)
                    ADDR_CONTROL: begin
                        // FIX: glitch detect hone par AES start block karo — security interlock
                        aes_start_o  <= reg_wdata[0] && !glitch_now_i;
                        bist_start_o <= reg_wdata[1];
                        wdt_enable_o <= reg_wdata[2];
                    end
                    ADDR_KEY_0:   aes_key_o[127:96] <= reg_wdata;
                    ADDR_KEY_1:   aes_key_o[95:64]  <= reg_wdata;
                    ADDR_KEY_2:   aes_key_o[63:32]  <= reg_wdata;
                    ADDR_KEY_3:   aes_key_o[31:0]   <= reg_wdata;
                    ADDR_PLAIN_0: aes_plaintext_o[127:96] <= reg_wdata;
                    ADDR_PLAIN_1: aes_plaintext_o[95:64]  <= reg_wdata;
                    ADDR_PLAIN_2: aes_plaintext_o[63:32]  <= reg_wdata;
                    ADDR_PLAIN_3: aes_plaintext_o[31:0]   <= reg_wdata;
                    default: ; // Read-only addresses par write ignore karo
                endcase
            end

            // ── READ OPERATIONS ──
            if (reg_read) begin
                reg_ready <= 1;
                case (reg_addr)
                    ADDR_STATUS: reg_rdata <= {27'b0, 
                                    glitch_detected_i,
                                    wdt_timeout_i,
                                    bist_fail_i,
                                    bist_pass_i,
                                    aes_done_i};
                    ADDR_RESULT_0: reg_rdata <= aes_result_i[127:96];
                    ADDR_RESULT_1: reg_rdata <= aes_result_i[95:64];
                    ADDR_RESULT_2: reg_rdata <= aes_result_i[63:32];
                    ADDR_RESULT_3: reg_rdata <= aes_result_i[31:0];
                    ADDR_CHIP_ID:  reg_rdata <= 32'h4E45454C; // "NEEL" in ASCII hex
                    default:       reg_rdata <= 32'h0;
                endcase
            end
        end
    end
endmodule
