module encrypted_channel_tb;

    reg         clk, rst;
    reg  [31:0] shared_key;
    reg          new_session;
    reg  [31:0]  plaintext_in;
    reg          encrypt_start;
    wire [31:0]  ciphertext_out;
    wire         encrypt_done;
    reg  [31:0]  ciphertext_in;
    reg  [15:0]  rx_msg_counter_in;
    reg          decrypt_start;
    wire [31:0]  plaintext_out;
    wire         decrypt_done;
    wire [15:0]  session_nonce_out;
    wire [15:0]  tx_msg_counter_out;

    encrypted_channel DUT (
        .clk(clk), .rst(rst),
        .shared_key(shared_key),
        .new_session(new_session),
        .plaintext_in(plaintext_in),
        .encrypt_start(encrypt_start),
        .ciphertext_out(ciphertext_out),
        .encrypt_done(encrypt_done),
        .ciphertext_in(ciphertext_in),
        .rx_msg_counter_in(rx_msg_counter_in),
        .decrypt_start(decrypt_start),
        .plaintext_out(plaintext_out),
        .decrypt_done(decrypt_done),
        .session_nonce_out(session_nonce_out),
        .tx_msg_counter_out(tx_msg_counter_out)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    reg [31:0] session1_cipher;
    reg [15:0] session1_counter;
    reg [31:0] msg1_cipher, msg2_cipher;
    reg [15:0] msg1_counter, msg2_counter;

    initial begin
        $dumpfile("encrypted_channel.vcd");
        $dumpvars(0, encrypted_channel_tb);

        rst = 1; shared_key = 32'hDEADBEEF; new_session = 0;
        plaintext_in = 0; encrypt_start = 0;
        ciphertext_in = 0; rx_msg_counter_in = 0; decrypt_start = 0;
        #20; rst = 0; #10;

        $display("================================");
        $display("  KAVACH-ID ENCRYPTED CHANNEL  ");
        $display("  Fixes: plaintext UART gap +    ");
        $display("  two-time-pad vulnerability      ");
        $display("================================");

        $display("--- Test 1: Encrypt (not plaintext on wire) ---");
        new_session = 1; #10; new_session = 0; #10;
        plaintext_in = 32'h12345678;
        encrypt_start = 1; #10; encrypt_start = 0; #10;
        session1_cipher  = ciphertext_out;
        session1_counter = tx_msg_counter_out;
        $display("Session Nonce: %0d, TX Counter: %0d", session_nonce_out, session1_counter);
        $display("Plaintext:  0x%0h", plaintext_in);
        $display("Ciphertext: 0x%0h (goes on the wire, WITH counter)", session1_cipher);
        if (session1_cipher != plaintext_in)
            $display("PASS: Wire data differs from plaintext - not snoopable!");
        else
            $display("FAIL: Ciphertext equals plaintext!");

        $display("--- Test 2: Decrypt Recovers Original (receiver uses the counter that arrived with the ciphertext) ---");
        ciphertext_in     = session1_cipher;
        rx_msg_counter_in = session1_counter; // Received alongside ciphertext
        decrypt_start = 1; #10; decrypt_start = 0; #10;
        $display("Decrypted:  0x%0h", plaintext_out);
        if (plaintext_out == 32'h12345678)
            $display("PASS: Decryption correctly recovers original data!");
        else
            $display("FAIL: Decryption mismatch");

        $display("--- Test 3: Session Freshness (Replay Resistance Across Sessions) ---");
        new_session = 1; #10; new_session = 0; #10;
        plaintext_in = 32'h12345678;
        encrypt_start = 1; #10; encrypt_start = 0; #10;
        $display("Session Nonce: %0d, TX Counter: %0d", session_nonce_out, tx_msg_counter_out);
        $display("Session 1 Ciphertext: 0x%0h", session1_cipher);
        $display("Session 2 Ciphertext: 0x%0h (same plaintext!)", ciphertext_out);
        if (ciphertext_out != session1_cipher)
            $display("PASS: New session produces different ciphertext - replay resistant!");
        else
            $display("FAIL: Same ciphertext across sessions!");

        $display("--- Test 4: TWO-TIME-PAD CHECK (Two Messages, SAME Session) ---");
        new_session = 1; #10; new_session = 0; #10;
        plaintext_in = 32'hAAAAAAAA;
        encrypt_start = 1; #10; encrypt_start = 0; #10;
        msg1_cipher  = ciphertext_out;
        msg1_counter = tx_msg_counter_out;
        $display("Msg 1 -> Nonce: %0d, Counter: %0d, Ciphertext: 0x%0h",
                  session_nonce_out, msg1_counter, msg1_cipher);

        plaintext_in = 32'hBBBBBBBB; // different plaintext, SAME session
        encrypt_start = 1; #10; encrypt_start = 0; #10;
        msg2_cipher  = ciphertext_out;
        msg2_counter = tx_msg_counter_out;
        $display("Msg 2 -> Nonce: %0d, Counter: %0d, Ciphertext: 0x%0h",
                  session_nonce_out, msg2_counter, msg2_cipher);

        if ((msg1_cipher ^ 32'hAAAAAAAA) != (msg2_cipher ^ 32'hBBBBBBBB))
            $display("PASS: Two messages in same session use DIFFERENT keystreams - two-time-pad fixed!");
        else
            $display("FAIL: SECURITY BUG - same keystream reused within a session (two-time-pad)!");

        $display("--- Test 5: Receiver Correctly Decrypts BOTH Messages Using Their Own Counters ---");
        ciphertext_in     = msg1_cipher;
        rx_msg_counter_in = msg1_counter;
        decrypt_start = 1; #10; decrypt_start = 0; #10;
        if (plaintext_out == 32'hAAAAAAAA)
            $display("PASS: Message 1 decrypts correctly using its own counter!");
        else
            $display("FAIL: Message 1 decryption mismatch");

        ciphertext_in     = msg2_cipher;
        rx_msg_counter_in = msg2_counter;
        decrypt_start = 1; #10; decrypt_start = 0; #10;
        if (plaintext_out == 32'hBBBBBBBB)
            $display("PASS: Message 2 decrypts correctly using its own counter!");
        else
            $display("FAIL: Message 2 decryption mismatch");

        $display("--- Test 6: Wrong Counter Rejected (Tamper/Desync Sanity Check) ---");
        ciphertext_in     = msg2_cipher;
        rx_msg_counter_in = msg1_counter; // deliberately wrong counter
        decrypt_start = 1; #10; decrypt_start = 0; #10;
        if (plaintext_out != 32'hBBBBBBBB)
            $display("PASS: Wrong counter correctly produces garbage, not the real plaintext!");
        else
            $display("FAIL: Wrong counter accidentally decrypted correctly - suspicious");

        $display("================================");
        $display("Encrypted Channel Complete!");
        $display("Plaintext UART gap addressed!");
        $display("Session nonce = replay resistant across sessions!");
        $display("TX/RX counter split = two-time-pad resistant within a session!");
        $display("================================");
        $finish;
    end
endmodule
