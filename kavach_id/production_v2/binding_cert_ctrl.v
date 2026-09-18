// =============================================================================
// binding_cert_ctrl.v
// -----------------------------------------------------------------------------
// Layer 1: Manufacturer-signed binding certificate (Pramaan-ID)
//
//   tamper_fuse_ctrl   -> "was THIS chip ever removed from ITS board?"
//   binding_cert_ctrl  -> "is THIS chip certified for the board it's on NOW?"
//
// Message = secret_key(128) || puf_id(32) || board_id(32) = 192 bits,
// static-concatenated, padded by sha256_core's caller to one 512-bit block
// (0x80 byte + zero pad + 64-bit length = fixed, no runtime padding logic).
//
// secret_key comes from a DEDICATED key_storage instance (separate from the
// main chip_key used for AES) so a leak in one domain doesn't compromise
// the other.
// =============================================================================

module binding_cert_ctrl (
    input  wire         clk,
    input  wire         rst,

    // ---- Manufacturing-time programming (write-once) ----
    input  wire         cert_program_en,       // pulse, factory-only
    input  wire [31:0]  cert_program_board_id,
    input  wire [255:0] cert_program_mac,      // SHA256(secret_key||puf_id||board_id),
                                                // computed OFF-CHIP by manufacturer HSM
                                                // and written in once at production time

    // ---- Runtime interface ----
    input  wire         verify_start,          // pulse: start a binding check
    input  wire [31:0]  board_id_live,         // board_id read live from board-side OTP
    input  wire [31:0]  puf_id,                // stable_response_i from existing PUF chain
    input  wire [127:0] binding_secret_key,    // from dedicated BINDING_KEY_STORE instance

    // ---- sha256_core interface (reuse existing core, one instance shared/arbitrated
    //      at top level -- see wiring notes below) ----
    output reg           sha_start,
    output reg  [511:0]  sha_block_in,          // fully-padded 512-bit block, built here
    input  wire [255:0]  sha_hash_out,
    input  wire           sha_done,

    // ---- Result ----
    output reg           binding_valid,         // gates authentication_grant
    output reg           verify_busy,
    output reg           cert_programmed        // latched once, mirrors tamper-fuse style latch
);

    // On-chip OTP-style storage for the certificate (write-once)
    reg [31:0]  stored_board_id;
    reg [255:0] stored_mac;

    localparam S_IDLE      = 2'd0,
               S_HASH_WAIT = 2'd1,
               S_COMPARE   = 2'd2;

    reg [1:0] state;

    // ---------------------------------------------------------------
    // Write-once certificate programming
    // ---------------------------------------------------------------
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            stored_board_id <= 32'h0;
            stored_mac      <= 256'h0;
            cert_programmed <= 1'b0;
        end else if (cert_program_en && !cert_programmed) begin
            // Only allowed ONCE, exactly like key_storage's key_locked pattern.
            stored_board_id <= cert_program_board_id;
            stored_mac      <= cert_program_mac;
            cert_programmed <= 1'b1;
        end
    end

    // ---------------------------------------------------------------
    // Static padding builder:
    //   message  = secret_key(128) || puf_id(32) || board_id(32)  = 192 bits
    //   pad      = 0x80 || zeros || 64-bit bit-length (192 = 64'd192)
    //   total    = 192 + 8 + 296 + 16 = 512 bits (fixed layout, no branches)
    // ---------------------------------------------------------------
    wire [511:0] padded_block = {
        binding_secret_key,   // 128 bits
        puf_id,                // 32 bits
        board_id_live,         // 32 bits
        8'h80,                 // pad start bit
        280'h0,                // zero padding (280 bits)
        64'd192                 // original message length in bits
    };

    // ---------------------------------------------------------------
    // Runtime verification: recompute SHA256(padded_block), compare
    // to stored_mac.
    // ---------------------------------------------------------------
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state         <= S_IDLE;
            sha_start     <= 1'b0;
            sha_block_in  <= 512'h0;
            binding_valid <= 1'b0;
            verify_busy   <= 1'b0;
        end else begin
            case (state)
                S_IDLE: begin
                    sha_start <= 1'b0;
                    if (verify_start) begin
                        if (!cert_programmed) begin
                            // No certificate ever programmed -> fail safe (deny).
                            binding_valid <= 1'b0;
                        end else begin
                            sha_block_in <= padded_block;
                            sha_start    <= 1'b1;
                            verify_busy  <= 1'b1;
                            state        <= S_HASH_WAIT;
                        end
                    end
                end

                S_HASH_WAIT: begin
                    sha_start <= 1'b0;
                    if (sha_done)
                        state <= S_COMPARE;
                end

                S_COMPARE: begin
                    binding_valid <= (sha_hash_out == stored_mac) &&
                                      (board_id_live == stored_board_id);
                    verify_busy   <= 1'b0;
                    state         <= S_IDLE;
                end

                default: state <= S_IDLE;
            endcase
        end
    end

endmodule
