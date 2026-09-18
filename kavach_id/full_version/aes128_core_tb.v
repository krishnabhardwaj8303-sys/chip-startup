module aes128_core_tb;

    reg         clk, rst, start;
    reg  [127:0] key, plaintext;
    wire [127:0] ciphertext;
    wire         done;

    aes128_core DUT (
        .clk(clk), .rst(rst), .start(start),
        .key(key), .plaintext(plaintext),
        .ciphertext(ciphertext), .done(done)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst = 1; start = 0; key = 0; plaintext = 0;
        #20; rst = 0; #10;

        $display("=== NIST FIPS-197 Appendix B known-answer test ===");
        key       = 128'h000102030405060708090a0b0c0d0e0f;
        plaintext = 128'h00112233445566778899aabbccddeeff;

        start = 1;
        @(posedge clk); #1;
        start = 0;

        wait (done == 1);
        #1;
        $display("Got:      %032h", ciphertext);
        $display("Expected: 69c4e0d86a7b0430d8cdb78070b4c55a");
        if (ciphertext == 128'h69c4e0d86a7b0430d8cdb78070b4c55a)
            $display("PASS: matches NIST FIPS-197 test vector exactly");
        else
            $display("FAIL: does NOT match NIST test vector");

        #20;

        $display("=== Second test: all-zero key and plaintext ===");
        key       = 128'h0;
        plaintext = 128'h0;
        start = 1;
        @(posedge clk); #1;
        start = 0;
        wait (done == 1);
        #1;
        $display("Got:      %032h", ciphertext);
        $display("Expected: 66e94bd4ef8a2c3b884cfa59ca342b2e");
        if (ciphertext == 128'h66e94bd4ef8a2c3b884cfa59ca342b2e)
            $display("PASS: matches all-zero known-answer test vector");
        else
            $display("FAIL: does NOT match all-zero test vector");

        $finish;
    end
endmodule
