module sha256_core_tb;

    reg          clk, rst, start;
    reg  [511:0] block_in;
    wire [255:0] hash_out;
    wire         done;

    sha256_core DUT (
        .clk(clk), .rst(rst), .start(start),
        .block_in(block_in),
        .hash_out(hash_out), .done(done)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst = 1; start = 0; block_in = 0;
        #20; rst = 0; #10;

        $display("=== NIST test vector: SHA-256(\"abc\") ===");
        // "abc" (0x616263) + 0x80 padding + zeros + 64-bit length (24 bits)
        block_in = {32'h61626380, {14{32'h00000000}}, 32'h00000018};
        start = 1;
        @(posedge clk); #1;
        start = 0;
        wait (done == 1);
        #1;
        $display("Got:      %064h", hash_out);
        $display("Expected: ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
        if (hash_out == 256'hba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad)
            $display("PASS: matches NIST SHA-256(\"abc\") test vector exactly");
        else
            $display("FAIL: does NOT match NIST test vector");

        #20;

        $display("=== Second test: SHA-256(\"\") (empty string) ===");
        block_in = {32'h80000000, {14{32'h00000000}}, 32'h00000000};
        start = 1;
        @(posedge clk); #1;
        start = 0;
        wait (done == 1);
        #1;
        $display("Got:      %064h", hash_out);
        $display("Expected: e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
        if (hash_out == 256'he3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
            $display("PASS: matches empty-string known-answer test vector");
        else
            $display("FAIL: does NOT match empty-string test vector");

        $finish;
    end
endmodule
