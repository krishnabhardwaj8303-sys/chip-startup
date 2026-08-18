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
    input  wire [15:0]  rx_msg_counter_in,
    input  wire          decrypt_start,
    output reg  [31:0]   plaintext_out,
    output reg            decrypt_done,
    output reg  [15:0]   session_nonce_out,
    output reg  [15:0]   tx_msg_counter_out  // The counter ACTUALLY used
                                               // for ciphertext_out - not
                                               // the live/next counter
);
    // ── FIX v3: register the counter that was actually consumed ──
    // BUG (v2): tx_msg_counter_out was a live combinational read of the
    // internal "next counter" register. Because that register advances
    // on the SAME clock edge that consumes it (non-blocking assignment
    // semantics), by the time the testbench sampled tx_msg_counter_out
    // it was already showing the counter for the NEXT message, not the
    // one that was just used to produce ciphertext_out - an off-by-one
    // that desynced sender and receiver.
    //
    // FIX: latch the counter actually used into tx_msg_counter_out at
    // the SAME time ciphertext_out is registered (both driven by the
    // same encrypt_start edge), exactly like a real protocol packages
    // ciphertext and its nonce/counter together as one unit.

    reg [15:0] session_nonce;
    reg [15:0] next_tx_counter; // internal: counter to use for the NEXT
                                  // encrypt operation

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

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            ciphertext_out     <= 0;
            encrypt_done       <= 0;
            tx_msg_counter_out <= 0;
            plaintext_out      <= 0;
            decrypt_done       <= 0;
        end
        else begin
            encrypt_done <= 0;
            decrypt_done <= 0;

            if (encrypt_start) begin
                // Both driven from the SAME pre-increment counter value
                // -> ciphertext and its reported counter always match.
                ciphertext_out     <= plaintext_in ^
                    derive_keystream(shared_key, session_nonce, next_tx_counter);
                tx_msg_counter_out <= next_tx_counter;
                encrypt_done       <= 1;
            end

            if (decrypt_start) begin
                plaintext_out <= ciphertext_in ^
                    derive_keystream(shared_key, session_nonce, rx_msg_counter_in);
                decrypt_done  <= 1;
            end
        end
    end
endmodule
