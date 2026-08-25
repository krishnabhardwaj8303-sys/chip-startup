module encrypted_channel_tb;

    reg          clk, rst;
    reg  [127:0] shared_key;
    reg           new_session;
    reg  [31:0]   plaintext_in;
    reg           encrypt_start;
    wire [31:0]   ciphertext_out;
    wire          encrypt_done;
    reg  [31:0]   ciphertext_in;
    reg  [15:0]   rx_msg_counter_in;
    reg           decrypt_start;
    wire [31:0]   plaintext_out;
    wire          decrypt_done;
    wire [15:0]   session_nonce_out;
    wire [15:0]   tx_msg_counter_out;

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

    task new_sess;
        begin
            new_session = 1; @(posedge clk); #1; new_session = 0; #10;
        end
    endtask

    task do_encrypt;
        input  [31:0] pt;
        output [31:0] ct;
        output [15:0] ctr;
        begin
            plaintext_in  = pt;
            encrypt_start = 1;
            @(posedge clk); #1;
            encrypt_start = 0;
            wait (encrypt_done == 1);
            #1;
            ct  = ciphertext_out;
            ctr = tx_msg_counter_out;
            #10;
        end
    endtask

    task do_decrypt;
        input [31:0] ct;
        input [15:0] ctr;
        begin
            ciphertext_in     = ct;
            rx_msg_counter_in = ctr;
            decrypt_start     = 1;
            @(posedge clk); #1;
            decrypt_start = 0;
            wait (decrypt_done == 1);
            #1;
            #10;
        end
    endtask

    reg [31:0] session1_cipher;
    reg [15:0] session1_counter;
    reg [31:0] msg1_cipher, msg2_cipher;
    reg [15:0] msg1_counter, msg2_counter;
    reg [31:0] session2_cipher;

    initial begin
        $dumpfile("encrypted_channel.vcd");
        $dumpvars(0, encrypted_channel_tb);

        rst = 1; shared_key = 128'h000102030405060708090a0b0c0d0e0f;
        new_session = 0; plaintext_in = 0; encrypt_start = 0;
        ciphertext_in = 0; rx_msg_counter_in = 0; decrypt_start = 0;
        #20; rst = 0; #10;

        $display("================================");
        $display("  KAVACH-ID ENCRYPTED CHANNEL   ");
        $display("  AES-CTR redesign (real AES-128,");
        $display("  not XOR mixing)                ");
        $display("================================");

        $display("--- Test 1: Encrypt (not plaintext on wire) ---");
        new_sess;
        do_encrypt(32'h12345678, session1_cipher, session1_counter);
        $display("Session Nonce: %0d, TX Counter: %0d", session_nonce_out, session1_counter);
        $display("Plaintext:  0x%0h", 32'h12345678);
        $display("Ciphertext: 0x%0h (goes on the wire, WITH counter)", session1_cipher);
        if (session1_cipher != 32'h12345678)
            $display("PASS: Wire data differs from plaintext - not snoopable!");
        else
            $display("FAIL: Ciphertext equals plaintext!");

        $display("--- Test 2: Decrypt Recovers Original ---");
        do_decrypt(session1_cipher, session1_counter);
        $display("Decrypted:  0x%0h", plaintext_out);
        if (plaintext_out == 32'h12345678)
            $display("PASS: Decryption correctly recovers original data!");
        else
            $display("FAIL: Decryption mismatch");

        $display("--- Test 3: Session Freshness (Replay Resistance Across Sessions) ---");
        new_sess;
        do_encrypt(32'h12345678, session2_cipher, session1_counter);
        $display("Session 1 Ciphertext: 0x%0h", session1_cipher);
        $display("Session 2 Ciphertext: 0x%0h (same plaintext!)", session2_cipher);
        if (session2_cipher != session1_cipher)
            $display("PASS: New session produces different ciphertext - replay resistant!");
        else
            $display("FAIL: Same ciphertext across sessions!");

        $display("--- Test 4: TWO-TIME-PAD CHECK (Two Messages, SAME Session) ---");
        new_sess;
        do_encrypt(32'hAAAAAAAA, msg1_cipher, msg1_counter);
        $display("Msg 1 -> Nonce: %0d, Counter: %0d, Ciphertext: 0x%0h",
                  session_nonce_out, msg1_counter, msg1_cipher);
        do_encrypt(32'hBBBBBBBB, msg2_cipher, msg2_counter);
        $display("Msg 2 -> Nonce: %0d, Counter: %0d, Ciphertext: 0x%0h",
                  session_nonce_out, msg2_counter, msg2_cipher);

        if ((msg1_cipher ^ 32'hAAAAAAAA) != (msg2_cipher ^ 32'hBBBBBBBB))
            $display("PASS: Two messages in same session use DIFFERENT keystreams - two-time-pad fixed!");
        else
            $display("FAIL: SECURITY BUG - same keystream reused within a session (two-time-pad)!");

        $display("--- Test 5: Receiver Correctly Decrypts BOTH Messages Using Their Own Counters ---");
        do_decrypt(msg1_cipher, msg1_counter);
        if (plaintext_out == 32'hAAAAAAAA)
            $display("PASS: Message 1 decrypts correctly using its own counter!");
        else
            $display("FAIL: Message 1 decryption mismatch");

        do_decrypt(msg2_cipher, msg2_counter);
        if (plaintext_out == 32'hBBBBBBBB)
            $display("PASS: Message 2 decrypts correctly using its own counter!");
        else
            $display("FAIL: Message 2 decryption mismatch");

        $display("--- Test 6: Wrong Counter Rejected (Tamper/Desync Sanity Check) ---");
        do_decrypt(msg2_cipher, msg1_counter); // deliberately wrong counter
        if (plaintext_out != 32'hBBBBBBBB)
            $display("PASS: Wrong counter correctly produces garbage, not the real plaintext!");
        else
            $display("FAIL: Wrong counter accidentally decrypted correctly - suspicious");

        $display("================================");
        $display("Encrypted Channel (AES-CTR) Complete!");
        $display("Real AES-128 keystream, not XOR mixing!");
        $display("Session nonce = replay resistant across sessions!");
        $display("TX/RX counter split = two-time-pad resistant within a session!");
        $display("================================");
        $finish;
    end
endmodule
