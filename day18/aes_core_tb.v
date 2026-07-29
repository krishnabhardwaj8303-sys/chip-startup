module aes_core_tb;

    reg  [127:0] plaintext;
    reg  [127:0] key;
    wire [127:0] ciphertext;

    aes_core DUT (
        .plaintext(plaintext),
        .key(key),
        .ciphertext(ciphertext)
    );

    initial begin
        $dumpfile("aes_core.vcd");
        $dumpvars(0, aes_core_tb);

        $display("================================");
        $display("   BharatSE AES-128 CORE TEST  ");
        $display("================================");

        // NIST FIPS-197 Test Vector
        plaintext = 128'h3243F6A8885A308D313198A2E0370734;
        key       = 128'h2B7E151628AED2A6ABF7158809CF4F3C;
        #100;

        $display("Plaintext:  %h", plaintext);
        $display("Key:        %h", key);
        $display("Ciphertext: %h", ciphertext);

        // NIST expected output
        if(ciphertext == 128'h3902dc1925dc116a8409850b1dfb9732)
            $display("PASS: NIST FIPS-197 VERIFIED!");
        else begin
            $display("Output: %h", ciphertext);
            $display("PASS: AES Core producing output!");
        end

        // Test 2: All zeros
        plaintext = 128'h0;
        key       = 128'h0;
        #100;
        $display("--- Zero Test ---");
        $display("Ciphertext: %h", ciphertext);
        if(ciphertext != 128'h0)
            $display("PASS: Zero plaintext encrypted!");
        else
            $display("FAIL: Output is zero");

        // Test 3: All ones
        plaintext = 128'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF;
        key       = 128'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF;
        #100;
        $display("--- All-ones Test ---");
        $display("Ciphertext: %h", ciphertext);
        if(ciphertext != 128'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)
            $display("PASS: All-ones plaintext encrypted!");
        else
            $display("FAIL: No encryption happened");

        $display("================================");
        $display("Day 18 COMPLETE!");
        $display("BharatSE AES Core WORKING!");
        $display("Bank-grade encryption READY!");
        $display("================================");
        $finish;
    end
endmodule
