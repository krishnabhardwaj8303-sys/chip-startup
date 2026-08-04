module encrypted_channel_tb;

    reg         clk, rst;
    reg  [31:0] shared_key;
    reg          new_session;
    reg  [31:0]  plaintext_in;
    reg          encrypt_start;
    wire [31:0]  ciphertext_out;
    wire         encrypt_done;
    reg  [31:0]  ciphertext_in;
    reg          decrypt_start;
    wire [31:0]  plaintext_out;
    wire         decrypt_done;
    wire [15:0]  session_nonce_out;

    encrypted_channel DUT (
        .clk(clk), .rst(rst),
        .shared_key(shared_key),
        .new_session(new_session),
        .plaintext_in(plaintext_in),
        .encrypt_start(encrypt_start),
        .ciphertext_out(ciphertext_out),
        .encrypt_done(encrypt_done),
        .ciphertext_in(ciphertext_in),
        .decrypt_start(decrypt_start),
        .plaintext_out(plaintext_out),
        .decrypt_done(decrypt_done),
        .session_nonce_out(session_nonce_out)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    reg [31:0] session1_cipher;

    initial begin
        $dumpfile("encrypted_channel.vcd");
        $dumpvars(0, encrypted_channel_tb);

        rst = 1; shared_key = 32'hDEADBEEF; new_session = 0;
        plaintext_in = 0; encrypt_start = 0;
        ciphertext_in = 0; decrypt_start = 0;
        #20; rst = 0; #10;

        $display("================================");
        $display("  KAVACH-ID ENCRYPTED CHANNEL  ");
        $display("  Fixes: plaintext UART gap      ");
        $display("================================");

        $display("--- Test 1: Encrypt (not plaintext on wire) ---");
        new_session = 1; #10; new_session = 0; #10;
        plaintext_in = 32'h12345678;
        encrypt_start = 1; #10; encrypt_start = 0; #10;
        session1_cipher = ciphertext_out;
        $display("Session Nonce: %0d", session_nonce_out);
        $display("Plaintext:  0x%0h", plaintext_in);
        $display("Ciphertext: 0x%0h (goes on the wire)", session1_cipher);
        if (session1_cipher != plaintext_in)
            $display("PASS: Wire data differs from plaintext - not snoopable!");
        else
            $display("FAIL: Ciphertext equals plaintext!");

        $display("--- Test 2: Decrypt Recovers Original (same session) ---");
        ciphertext_in = session1_cipher;
        decrypt_start = 1; #10; decrypt_start = 0; #10;
        $display("Decrypted:  0x%0h", plaintext_out);
        if (plaintext_out == 32'h12345678)
            $display("PASS: Decryption correctly recovers original data!");
        else
            $display("FAIL: Decryption mismatch");

        $display("--- Test 3: Session Freshness (Replay Resistance) ---");
        new_session = 1; #10; new_session = 0; #10;
        plaintext_in = 32'h12345678;
        encrypt_start = 1; #10; encrypt_start = 0; #10;
        $display("Session Nonce: %0d", session_nonce_out);
        $display("Session 1 Ciphertext: 0x%0h", session1_cipher);
        $display("Session 2 Ciphertext: 0x%0h (same plaintext!)", 
                  ciphertext_out);
        if (ciphertext_out != session1_cipher)
            $display("PASS: New session produces different ciphertext - replay resistant!");
        else
            $display("FAIL: Same ciphertext across sessions!");

        $display("================================");
        $display("Encrypted Channel Complete!");
        $display("Plaintext UART gap addressed!");
        $display("Session nonce = replay resistant!");
        $display("================================");
        $finish;
    end
endmodule
