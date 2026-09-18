`timescale 1ns/1ps
module binding_cert_real_sha_tb;
    reg clk = 0;
    reg rst = 1;
    reg cert_program_en = 0;
    reg [31:0] cert_program_board_id;
    reg [255:0] cert_program_mac;
    reg verify_start = 0;
    reg [31:0] board_id_live;
    reg [31:0] puf_id;
    reg [127:0] binding_secret_key;

    wire sha_start;
    wire [511:0] sha_block_in;
    wire [255:0] sha_hash_out;
    wire         sha_done;

    wire binding_valid, verify_busy, cert_programmed;

    always #5 clk = ~clk;

    binding_cert_ctrl DUT (
        .clk(clk), .rst(rst),
        .cert_program_en(cert_program_en),
        .cert_program_board_id(cert_program_board_id),
        .cert_program_mac(cert_program_mac),
        .verify_start(verify_start),
        .board_id_live(board_id_live),
        .puf_id(puf_id),
        .binding_secret_key(binding_secret_key),
        .sha_start(sha_start),
        .sha_block_in(sha_block_in),
        .sha_hash_out(sha_hash_out),
        .sha_done(sha_done),
        .binding_valid(binding_valid),
        .verify_busy(verify_busy),
        .cert_programmed(cert_programmed)
    );

    // REAL sha256_core, not a stand-in
    sha256_core SHA (
        .clk(clk), .rst(rst),
        .start(sha_start),
        .block_in(sha_block_in),
        .hash_out(sha_hash_out),
        .done(sha_done)
    );

    wire [511:0] expected_block_w = { binding_secret_key, puf_id, board_id_live,
                                        8'h80, 280'h0, 64'd192 };

    // For test purposes only: compute the "manufacturer-signed" MAC by
    // running the SAME real sha256_core once, off to the side, over the
    // genuine (chip, board) pairing -- mimicking what the factory HSM
    // would produce at provisioning time.
    reg        ref_start;
    reg [511:0] ref_block;
    wire [255:0] ref_hash;
    wire        ref_done;
    sha256_core SHA_REF (
        .clk(clk), .rst(rst),
        .start(ref_start),
        .block_in(ref_block),
        .hash_out(ref_hash),
        .done(ref_done)
    );

    initial begin
        $display("=== binding_cert_ctrl + REAL sha256_core integration test ===");
        ref_start = 0;
        #12 rst = 0;

        binding_secret_key = 128'hDEAD_BEEF_CAFE_BABE_0123_4567_89AB_CDEF;
        puf_id              = 32'hAAAA_BBBB;
        board_id_live       = 32'h1234_5678;
        #1;

        // Compute the genuine MAC using the reference core
        ref_block = expected_block_w;
        @(posedge clk); #1;
        ref_start = 1;
        @(posedge clk); #1;
        ref_start = 0;
        wait (ref_done);
        #1;
        cert_program_mac = ref_hash;
        cert_program_board_id = board_id_live;
        $display("Reference MAC computed: %h", ref_hash);

        // Program the certificate
        @(posedge clk); #1;
        cert_program_en = 1;
        @(posedge clk); #1;
        cert_program_en = 0;
        @(posedge clk); #1;

        if (cert_programmed)
            $display("PASS: cert_programmed latched");
        else
            $display("FAIL: cert_programmed did not latch");

        // Test 1: genuine chip on genuine board -> should verify (real SHA compute)
        verify_start = 1;
        @(posedge clk); #1;
        verify_start = 0;
        wait (!verify_busy);
        #1;
        if (binding_valid)
            $display("PASS: genuine chip+board -> binding_valid = 1 (real SHA-256 match)");
        else
            $display("FAIL: genuine chip+board -> binding_valid should be 1");

        // Test 2: genuine chip, WRONG board (simulated transplant) -> must fail
        board_id_live = 32'hDEAD_0000;
        #1;
        verify_start = 1;
        @(posedge clk); #1;
        verify_start = 0;
        wait (!verify_busy);
        #1;
        if (!binding_valid)
            $display("PASS: genuine chip on WRONG board -> binding_valid = 0 (transplant blocked, real SHA)");
        else
            $display("FAIL: transplant NOT blocked -- SECURITY BUG");

        $display("=== test complete ===");
        $finish;
    end
endmodule
