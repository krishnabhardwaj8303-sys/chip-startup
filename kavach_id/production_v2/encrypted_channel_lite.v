module encrypted_channel(
    input  wire        clk,
    input  wire        rst,
    input  wire [31:0] shared_key,
    input  wire         new_session,
    input  wire [31:0]  plaintext_in,
    input  wire          encrypt_start,
    output reg  [31:0]   ciphertext_out,
    output reg            encrypt_done,
    input  wire [31:0]  ciphertext_in,
    input  wire          decrypt_start,
    output reg  [31:0]   plaintext_out,
    output reg            decrypt_done,
    output reg  [15:0]   session_nonce_out,  // Debug/monitoring
    output reg  [15:0]   msg_counter_out     // Debug/monitoring
);
    // ── FIX: two-time-pad vulnerability ──
    // BUG (original): keystream was derived only from shared_key +
    // session_nonce, regenerated ONLY on new_session. If two messages
    // were encrypted within the SAME session (two encrypt_start pulses
    // without an intervening new_session), both used the IDENTICAL
    // keystream — a classic "two-time pad" weakness (the same failure
    // that broke WEP Wi-Fi encryption). XOR of the two ciphertexts
    // leaks the XOR of the two plaintexts.
    //
    // FIX: add a per-message counter (msg_counter) that advances on
    // every encrypt/decrypt operation, and mix it into the keystream
    // alongside the session nonce. Every individual message — even
    // within the same session — now gets a distinct keystream.

    reg [15:0] session_nonce;
    reg [15:0] msg_counter;

    function [31:0] derive_keystream;
        input [31:0] key;
        input [15:0] nonce;
        input [15:0] ctr;
        begin
            derive_keystream = (key ^ 32'hFACE_CAFE) +
                                {key[15:0], key[31:16]} +
                                {nonce, nonce} +
                                {ctr, ~ctr};
        end
    endfunction

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            session_nonce <= 16'h0001;
            msg_counter   <= 16'h0000;
        end
        else if (new_session) begin
            // New session: nonce advances, message counter resets.
            // NOTE (usage requirement): new_session must be pulsed and
            // allowed to settle for one clock cycle BEFORE the first
            // encrypt_start/decrypt_start of that session — asserting
            // both in the same cycle would use the previous session's
            // nonce/counter for that first message. The existing
            // testbench protocol already follows this ordering.
            session_nonce <= session_nonce + 16'h1;
            msg_counter   <= 16'h0000;
        end
        else if (encrypt_start || decrypt_start) begin
            msg_counter <= msg_counter + 16'h1;
        end
    end

    always @(*) begin
        session_nonce_out = session_nonce;
        msg_counter_out   = msg_counter;
    end

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            ciphertext_out <= 0;
            encrypt_done   <= 0;
            plaintext_out  <= 0;
            decrypt_done   <= 0;
        end
        else begin
            encrypt_done <= 0;
            decrypt_done <= 0;

            if (encrypt_start) begin
                ciphertext_out <= plaintext_in ^
                    derive_keystream(shared_key, session_nonce, msg_counter);
                encrypt_done   <= 1;
            end

            if (decrypt_start) begin
                plaintext_out <= ciphertext_in ^
                    derive_keystream(shared_key, session_nonce, msg_counter);
                decrypt_done  <= 1;
            end
        end
    end
endmodule
