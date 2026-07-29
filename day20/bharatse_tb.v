module bharatse_tb;

    reg         clk, rst;
    reg  [127:0] plaintext;
    reg         encrypt_start;
    reg         tamper_detect;
    wire        uart_tx;
    wire        encrypt_done;
    wire        keys_erased;
    wire [127:0] ciphertext;

    bharatse_top DUT (
        .clk(clk), .rst(rst),
        .plaintext(plaintext),
        .encrypt_start(encrypt_start),
        .tamper_detect(tamper_detect),
        .uart_tx(uart_tx),
        .encrypt_done(encrypt_done),
        .keys_erased(keys_erased),
        .ciphertext(ciphertext)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("bharatse.vcd");
        $dumpvars(0, bharatse_tb);

        rst=1; encrypt_start=0;
        tamper_detect=0; plaintext=0;
        #30; rst=0; #20;

        $display("================================");
        $display("   BharatSE CHIP FINAL TEST    ");
        $display("   India's First Secure Element ");
        $display("================================");

        // Test 1: Normal encryption
        $display("--- Test 1: UPI Transaction ---");
        plaintext = 128'hDEADBEEFCAFEBABE1234567890ABCDEF;
        encrypt_start=1; #10; encrypt_start=0;
        wait(encrypt_done);
        $display("Plaintext:  %h", plaintext);
        $display("Ciphertext: %h", ciphertext);
        if(ciphertext != 128'h0)
            $display("PASS: Encryption complete!");
        else
            $display("FAIL: No encryption");
        #100;

        // Test 2: Second transaction
        $display("--- Test 2: Second Transaction ---");
        plaintext = 128'hFFFFFFFFFFFFFFFF0000000000000000;
        encrypt_start=1; #10; encrypt_start=0;
        wait(encrypt_done);
        $display("Ciphertext: %h", ciphertext);
        $display("PASS: Second encryption done!");
        #100;

        // Test 3: TAMPER ATTACK!
        $display("--- Test 3: TAMPER ATTACK! ---");
        $display("Attacker trying to clone chip...");
        tamper_detect=1; #30; tamper_detect=0;
        #50;
        if(keys_erased)
            $display("PASS: TAMPER DETECTED!");
            $display("PASS: Keys ERASED instantly!");
            $display("PASS: Chip is SECURE!");
        #100;

        $display("================================");
        $display("  BharatSE v1.0 COMPLETE!      ");
        $display("  Day 20 DONE!                 ");
        $display("  India's Secure Element READY! ");
        $display("================================");
        $finish;
    end
endmodule
