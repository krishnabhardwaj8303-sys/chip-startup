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
    output reg  [15:0]   session_nonce_out  // Debug/monitoring ke liye
);
    // Fix: shared_key akela fixed hai, isliye sirf usse 
    // keystream banane pe har session same keystream milegi.
    // Real crypto protocols (TLS, etc.) mein ek session 
    // NONCE (number-used-once) hota hai jo har connection pe 
    // increment hota hai — yeh keystream ko session-unique 
    // banata hai, replay attack ko harder karta hai.
    reg [31:0] keystream;
    reg [15:0] session_nonce;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            keystream     <= 32'hFACE_CAFE;
            session_nonce <= 16'h0001;
        end
        else if (new_session) begin
            // Nonce increment karo — har session unique hoga
            session_nonce <= session_nonce + 16'h1;
            keystream <= (shared_key ^ 32'hFACE_CAFE) + 
                         {shared_key[15:0], shared_key[31:16]} + 
                         {session_nonce, session_nonce}; // Nonce mix karo
        end
    end

    always @(*) session_nonce_out = session_nonce;

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
                ciphertext_out <= plaintext_in ^ keystream;
                encrypt_done   <= 1;
            end

            if (decrypt_start) begin
                plaintext_out <= ciphertext_in ^ keystream;
                decrypt_done  <= 1;
            end
        end
    end
endmodule
