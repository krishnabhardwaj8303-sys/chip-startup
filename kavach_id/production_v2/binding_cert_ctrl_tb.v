`timescale 1ns/1ps
module binding_cert_ctrl_tb;
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
    reg  [255:0] sha_hash_out;
    reg          sha_done;

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

    always @(posedge clk) begin
        if (rst) sha_done <= 0;
        else if (sha_start) begin
            sha_hash_out <= sha_block_in[511:256] ^ sha_block_in[255:0];
            sha_done <= 1'b0;
        end else if (!sha_done && DUT.state == 2'd1) begin
            sha_done <= 1'b1;
        end else begin
            sha_done <= 1'b0;
        end
    end

    wire [511:0] expected_block_w = { binding_secret_key, puf_id, board_id_live,
                                        8'h80, 280'h0, 64'd192 };

    initial begin
        $display("=== binding_cert_ctrl standalone test ===");
        #12 rst = 0;

        binding_secret_key = 128'hDEAD_BEEF_CAFE_BABE_0123_4567_89AB_CDEF;
        puf_id              = 32'hAAAA_BBBB;
        board_id_live       = 32'h1234_5678;
        #1;

        cert_program_board_id = board_id_live;
        cert_program_mac      = expected_block_w[511:256] ^ expected_block_w[255:0];

        @(posedge clk); #1;
        cert_program_en = 1;
        @(posedge clk); #1;
        cert_program_en = 0;
        @(posedge clk); #1;

        if (cert_programmed)
            $display("PASS: cert_programmed latched");
        else
            $display("FAIL: cert_programmed did not latch");

        // Test 1: genuine chip on genuine board -> should verify
        verify_start = 1;
        @(posedge clk); #1;
        verify_start = 0;
        wait (!verify_busy);
        #1;
        if (binding_valid)
            $display("PASS: genuine chip+board -> binding_valid = 1");
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
            $display("PASS: genuine chip on WRONG board -> binding_valid = 0 (transplant blocked)");
        else
            $display("FAIL: transplant NOT blocked -- SECURITY BUG");

        // Test 3: second cert_program_en attempt after already programmed -> must be ignored
        cert_program_board_id = 32'hFFFF_FFFF;
        @(posedge clk); #1;
        cert_program_en = 1;
        @(posedge clk); #1;
        cert_program_en = 0;
        @(posedge clk); #1;
        if (DUT.stored_board_id == 32'h1234_5678)
            $display("PASS: re-programming attempt ignored, original cert intact");
        else
            $display("FAIL: cert was overwritten -- write-once violated");

        $display("=== test complete ===");
        $finish;
    end
endmodule
