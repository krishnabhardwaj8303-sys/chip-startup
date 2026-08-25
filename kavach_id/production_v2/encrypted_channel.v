// encrypted_channel.v — AES-CTR redesign
//
// FIX: derive_keystream() previously used a simple XOR/arithmetic mixing
// function (key ^ constant, rotations, additions) - NOT real cryptography.
// Replaced with a real NIST FIPS-197 AES-128 core (aes128_core.v) run in
// CTR mode: keystream = AES(key, counter_block), where counter_block packs
// the 16-bit session nonce and 16-bit per-message counter into the AES
// core's 128-bit input (upper 96 bits zero). ciphertext = plaintext XOR
// keystream[31:0].
//
// BREAKING CHANGE: shared_key widened from 32 bits to 128 bits. A 32-bit
// key was a weak point independent of the cipher; AES-128 needs a full
// 128-bit key. kavach_id_top.v's shared_key wiring must be updated to
// match - not yet done as of this commit.
//
// TIMING CHANGE: aes128_core is a multi-cycle iterative FSM (~12 clock
// cycles per block), not combinational. encrypt_done/decrypt_done no
// longer assert the cycle after *_start - they pulse once the shared AES
// core finishes. One AES core instance is shared between the encrypt and
// decrypt paths; if both *_start signals arrive in the same cycle,
// encrypt is served first (decrypt_start is not sampled while the FSM is
// busy encrypting) - not exercised by the current testbench, but a real
// serialization constraint of this single-core design.
//
// All session-nonce and TX/RX counter logic (including the v3 fix that
// registers the counter actually consumed alongside its ciphertext) is
// unchanged from the previous version.
module encrypted_channel(
    input  wire         clk,
    input  wire         rst,
    input  wire [127:0] shared_key,
    input  wire          new_session,
    input  wire [31:0]   plaintext_in,
    input  wire           encrypt_start,
    output reg  [31:0]    ciphertext_out,
    output reg             encrypt_done,
    input  wire [31:0]   ciphertext_in,
    input  wire [15:0]   rx_msg_counter_in,
    input  wire           decrypt_start,
    output reg  [31:0]    plaintext_out,
    output reg             decrypt_done,
    output reg  [15:0]    session_nonce_out,
    output reg  [15:0]    tx_msg_counter_out  // counter ACTUALLY used
                                                // for ciphertext_out
);

    reg [15:0] session_nonce;
    reg [15:0] next_tx_counter;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            session_nonce   <= 16'h0001;
            next_tx_counter <= 16'h0000;
        end
        else if (new_session) begin
            session_nonce   <= session_nonce + 16'h1;
            next_tx_counter <= 16'h0000;
        end
        else if (encrypt_start) begin
            next_tx_counter <= next_tx_counter + 16'h1;
        end
    end

    always @(*) session_nonce_out = session_nonce;

    // ── Shared AES-128 core (CTR mode) ──
    reg          aes_start;
    reg  [127:0] aes_block_in;
    wire [127:0] aes_block_out;
    wire         aes_done;

    aes128_core u_aes (
        .clk(clk),
        .rst(rst),
        .start(aes_start),
        .key(shared_key),
        .plaintext(aes_block_in),
        .ciphertext(aes_block_out),
        .done(aes_done)
    );

    localparam ST_IDLE     = 2'd0,
               ST_ENC_WAIT = 2'd1,
               ST_DEC_WAIT = 2'd2;

    reg [1:0]  fsm_state;
    reg [31:0] pending_plaintext;
    reg [15:0] pending_tx_counter;
    reg [31:0] pending_ciphertext_in;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            fsm_state              <= ST_IDLE;
            aes_start               <= 1'b0;
            aes_block_in             <= 128'd0;
            ciphertext_out            <= 32'd0;
            encrypt_done               <= 1'b0;
            plaintext_out                <= 32'd0;
            decrypt_done                   <= 1'b0;
            tx_msg_counter_out               <= 16'd0;
            pending_plaintext                  <= 32'd0;
            pending_tx_counter                   <= 16'd0;
            pending_ciphertext_in                  <= 32'd0;
        end
        else begin
            aes_start    <= 1'b0;
            encrypt_done <= 1'b0;
            decrypt_done <= 1'b0;

            case (fsm_state)
                ST_IDLE: begin
                    if (encrypt_start) begin
                        pending_plaintext  <= plaintext_in;
                        pending_tx_counter <= next_tx_counter;
                        aes_block_in       <= {96'h0, session_nonce, next_tx_counter};
                        aes_start          <= 1'b1;
                        fsm_state          <= ST_ENC_WAIT;
                    end
                    else if (decrypt_start) begin
                        pending_ciphertext_in <= ciphertext_in;
                        aes_block_in          <= {96'h0, session_nonce, rx_msg_counter_in};
                        aes_start             <= 1'b1;
                        fsm_state             <= ST_DEC_WAIT;
                    end
                end

                ST_ENC_WAIT: begin
                    if (aes_done) begin
                        ciphertext_out     <= pending_plaintext ^ aes_block_out[31:0];
                        tx_msg_counter_out <= pending_tx_counter;
                        encrypt_done       <= 1'b1;
                        fsm_state          <= ST_IDLE;
                    end
                end

                ST_DEC_WAIT: begin
                    if (aes_done) begin
                        plaintext_out <= pending_ciphertext_in ^ aes_block_out[31:0];
                        decrypt_done  <= 1'b1;
                        fsm_state     <= ST_IDLE;
                    end
                end

                default: fsm_state <= ST_IDLE;
            endcase
        end
    end
endmodule
