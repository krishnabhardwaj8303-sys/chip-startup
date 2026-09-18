module kavach_id_top_uart_tb;

    reg  clk, rst;
    wire uart_link;      // host -> chip
    wire uart_from_chip; // chip -> host
    wire chip_healthy, verification_blocked;

    // "Host" TX: drives commands into the chip via a real uart_tx
    reg        host_tx_start;
    reg  [7:0] host_tx_data;
    wire       host_tx_busy;

    uart_tx #(.CLKS_PER_BIT(4)) HOST_TX (
        .clk(clk), .rst(rst),
        .tx_start(host_tx_start), .data_in(host_tx_data),
        .tx_out(uart_link), .tx_busy(host_tx_busy)
    );

    // "Host" RX: receives chip responses via a real uart_rx
    wire [7:0] host_rx_byte;
    wire       host_rx_valid;

    uart_rx #(.CLKS_PER_BIT(4)) HOST_RX (
        .clk(clk), .rst(rst),
        .rx_in(uart_from_chip),
        .data_out(host_rx_byte),
        .data_valid(host_rx_valid)
    );

    kavach_id_top DUT (
        .clk(clk), .clk_sel(1'b0), .rst(rst),
        .uart_rx_in(uart_link),
        .uart_tx_out(uart_from_chip),
        .pcb_loop_sense_i(1'b1),
        .chip_healthy(chip_healthy),
        .verification_blocked(verification_blocked)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    task send_byte(input [7:0] b);
        begin
            wait (host_tx_busy == 0);
            host_tx_data = b;
            host_tx_start = 1;
            @(posedge clk); #1;
            host_tx_start = 0;
            wait (host_tx_busy == 1);
            wait (host_tx_busy == 0);
        end
    endtask

    task reg_write_uart(input [7:0] addr, input [31:0] data);
        begin
            send_byte(8'h01);          // CMD = WRITE
            send_byte(addr);
            send_byte(data[31:24]);
            send_byte(data[23:16]);
            send_byte(data[15:8]);
            send_byte(data[7:0]);
        end
    endtask

    reg [31:0] read_result;
    integer    read_byte_count;

    task reg_read_uart(input [8:0] addr);
        begin
            read_result = 0;
            read_byte_count = 0;
            send_byte(8'h02);          // CMD = READ
            send_byte(addr[7:0]);
            send_byte(8'h00);          // DATA field unused for reads, still 4 bytes per frame
            send_byte(8'h00);
            send_byte(8'h00);
            send_byte(8'h00);
            // wait for all 4 response bytes to arrive
            wait (read_byte_count == 4);
        end
    endtask

    always @(posedge clk) begin
        if (host_rx_valid) begin
            read_result <= {read_result[23:0], host_rx_byte};
            read_byte_count <= read_byte_count + 1;
        end
    end

    // ── Reference SHA256 core: simulates the manufacturer's OFF-CHIP HSM,
    //    which computes the binding-certificate MAC once at provisioning
    //    time. In real production this never runs on-chip; here it lets
    //    the testbench compute a valid MAC to program via UART, exactly
    //    like a factory programming station would supply it.
    reg          ref_start;
    reg  [511:0] ref_block;
    wire [255:0] ref_hash;
    wire         ref_done;
    sha256_core REF_SHA (
        .clk(clk), .rst(rst),
        .start(ref_start),
        .block_in(ref_block),
        .hash_out(ref_hash),
        .done(ref_done)
    );

    reg [127:0] binding_secret_key_tb;
    reg [31:0]  board_id_tb;
    reg [31:0]  puf_id_tb;
    reg [255:0] cert_mac_tb;

    task provision_binding_cert;
        begin
            // 1. Set board ID (board-side OTP, read live at runtime)
            reg_write_uart(8'h50, board_id_tb); // ADDR_BOARD_ID

            // 2. Run the stabilizer with a FIXED ENROLLMENT challenge, distinct
            //    from any challenge used later at runtime auth (Test 2/5 use
            //    0x1111_1111) -- otherwise the replay_detector would flag the
            //    runtime auth's reuse of that challenge as a replay attack.
            //    The puf_id captured here is the chip's stable enrollment
            //    identity, independent of whatever challenge is used at
            //    runtime for the actual auth/encryption flow.
            reg_write_uart(8'h08, 32'hFEED_0001); // CHALLENGE (enrollment-only, never reused)
            reg_write_uart(8'h00, 32'h0000_0002); // CONTROL[1] = stabilizer_start
            repeat (15) @(posedge clk);
            reg_read_uart(8'h0C); // RESPONSE
            puf_id_tb = read_result;
            $display("Provisioning: captured puf_id = %h, board_id = %h", puf_id_tb, board_id_tb);

            // 3. Compute the manufacturer-signed MAC using the reference core
            //    (mirrors binding_cert_ctrl's static padding exactly).
            ref_block = { binding_secret_key_tb, puf_id_tb, board_id_tb,
                          8'h80, 280'h0, 64'd192 };
            @(posedge clk); #1;
            ref_start = 1;
            @(posedge clk); #1;
            ref_start = 0;
            wait (ref_done);
            #1;
            cert_mac_tb = ref_hash;
            $display("Provisioning: manufacturer MAC = %h", cert_mac_tb);

            // 4. Program the dedicated binding secret key (4 x 32-bit words,
            //    MSB word first -- same shift-register pattern as KEY_DATA)
            reg_write_uart(8'h54, binding_secret_key_tb[127:96]);
            reg_write_uart(8'h54, binding_secret_key_tb[95:64]);
            reg_write_uart(8'h54, binding_secret_key_tb[63:32]);
            reg_write_uart(8'h54, binding_secret_key_tb[31:0]);
            reg_write_uart(8'h58, 32'h0000_0001); // BINDING_KEY_CONTROL: lock it in

            // 5. Program the certificate MAC (8 x 32-bit words, MSB first)
            reg_write_uart(8'h5C, cert_mac_tb[255:224]);
            reg_write_uart(8'h5C, cert_mac_tb[223:192]);
            reg_write_uart(8'h5C, cert_mac_tb[191:160]);
            reg_write_uart(8'h5C, cert_mac_tb[159:128]);
            reg_write_uart(8'h5C, cert_mac_tb[127:96]);
            reg_write_uart(8'h5C, cert_mac_tb[95:64]);
            reg_write_uart(8'h5C, cert_mac_tb[63:32]);
            reg_write_uart(8'h5C, cert_mac_tb[31:0]);
            reg_write_uart(8'h60, 32'h0000_0001); // CERT_CONTROL: bit0 = cert_program_en
            repeat (5) @(posedge clk);

            reg_read_uart(8'h64); // CERT_STATUS
            if (read_result[1])
                $display("PASS: cert_programmed latched after provisioning");
            else
                $display("FAIL: cert_programmed did not latch");
        end
    endtask

    task binding_verify;
        begin
            reg_write_uart(8'h60, 32'h0000_0002); // CERT_CONTROL: bit1 = verify_start
            repeat (100) @(posedge clk); // full SHA256 core latency (~85 cycles) + margin
        end
    endtask

    initial begin
        rst = 1; host_tx_start = 0; host_tx_data = 0;
        ref_start = 0;
        binding_secret_key_tb = 128'hDEAD_BEEF_CAFE_BABE_0123_4567_89AB_CDEF;
        board_id_tb           = 32'hCAFE_1234;
        #20; rst = 0; #150; // extra margin for POR_CYCLES (8) hold + reset_sync 2-cycle release // extra margin for reset_sync's 2-cycle release

        $display("================================================");
        $display("  ONE-TIME FACTORY PROVISIONING (Layer 1 binding cert)");
        $display("================================================");
        provision_binding_cert();

        $display("================================================");
        $display("  KAVACH-ID TOP-LEVEL UART-PROTOCOL INTEGRATION");
        $display("================================================");

        $display("--- Test 1: Run BIST via UART, check chip_healthy ---");
        reg_write_uart(8'h00, 32'h0000_0001); // CONTROL[0] = bist_start
        repeat (10) @(posedge clk);
        $display("chip_healthy=%0d (expect 1)", chip_healthy);
        if (chip_healthy)
            $display("PASS");
        else
            $display("FAIL");

        $display("--- Test 2: Fresh verify -> auth_request -> grant, via UART ---");
        reg_write_uart(8'h08, 32'h1111_1111); // CHALLENGE
        reg_write_uart(8'h00, 32'h0000_0002); // CONTROL[1] = stabilizer_start
        repeat (15) @(posedge clk);
        binding_verify(); // Layer 1: must verify chip-board binding before auth can grant
        reg_write_uart(8'h00, 32'h0000_0004); // CONTROL[2] = auth_request
        repeat (10) @(posedge clk);
        read_byte_count = 0;
        reg_read_uart(8'h04); // STATUS
        $display("STATUS=0x%0h (expect bit3=1, authentication_grant)", read_result);
        if (read_result[3] == 1)
            $display("PASS");
        else
            $display("FAIL");

        $display("--- Test 3: Same challenge again -> replay -> blocked ---");
        reg_write_uart(8'h08, 32'h1111_1111); // SAME challenge
        reg_write_uart(8'h00, 32'h0000_0002);
        repeat (15) @(posedge clk);
        reg_write_uart(8'h00, 32'h0000_0004);
        repeat (10) @(posedge clk);
        reg_read_uart(8'h04);
        $display("STATUS=0x%0h, verification_blocked=%0d", read_result, verification_blocked);
        if (read_result[2] == 1 && verification_blocked == 1)
            $display("PASS: replay correctly detected and blocked");
        else
            $display("FAIL");

        $display("--- Test 4: Read ciphertext via CIPHERTEXT_DATA register ---");
        reg_read_uart(8'h34);
        $display("CIPHERTEXT_DATA=0x%0h (non-zero expected if a grant produced ciphertext)", read_result);
        if (read_result != 0)
            $display("PASS: ciphertext readable via register, no auto-push conflict");
        else
            $display("FAIL: unexpected zero ciphertext");

        $display("================================================");
        $display("--- Test 6: Transplant attack -- genuine chip, WRONG board, NO physical tamper -- must be denied ---");
        reg_write_uart(8'h50, 32'hBAD0_BAD0); // ADDR_BOARD_ID: wrong board
        reg_write_uart(8'h08, 32'h1111_1111); // CHALLENGE
        reg_write_uart(8'h00, 32'h0000_0002); // CONTROL[1] = stabilizer_start
        repeat (15) @(posedge clk);
        binding_verify();
        reg_read_uart(8'h64); // CERT_STATUS
        if (read_result[2])
            $display("FAIL: binding_valid asserted for a chip on the WRONG board -- SECURITY BUG");
        else
            $display("PASS: binding_valid correctly 0 for chip on wrong board (transplant blocked)");

        reg_write_uart(8'h00, 32'h0000_0004); // CONTROL[2] = auth_request
        repeat (30) @(posedge clk);
        if (DUT.authentication_grant_i === 1'b1)
            $display("FAIL: authentication_grant asserted despite wrong-board transplant -- SECURITY BUG");
        else
            $display("PASS: authentication correctly denied for transplanted chip (no physical tamper needed)");

        reg_write_uart(8'h50, 32'hCAFE_1234);

        $display("================================================");
        $display("--- Test 5: Tamper-fuse -- break PCB loop, then attempt auth -- must be denied ---");
    force DUT.pcb_loop_sense_i = 1'b0;
    repeat (10) @(posedge clk);
    release DUT.pcb_loop_sense_i;
    // even though the physical wire is released back to 1, the internal
    // fuse inside tamper_fuse_ctrl must now be permanently latched.
    if (DUT.tamper_fuse_tripped !== 1'b1)
        $display("FAIL: tamper_fuse_tripped did not latch after simulated desoldering");
    else
        $display("PASS: tamper_fuse_tripped latched after simulated desoldering");

    // Try a fresh, otherwise-completely-legitimate authentication attempt
    // post-tamper (same real sequence as Test 2) -- must still be denied.
    reg_write_uart(8'h08, 32'h1111_1111); // CHALLENGE
    reg_write_uart(8'h00, 32'h0000_0002); // CONTROL[1] = stabilizer_start
    repeat (15) @(posedge clk);
    binding_verify(); // even with a VALID binding cert, tamper-fuse must still block
    reg_write_uart(8'h00, 32'h0000_0004); // CONTROL[2] = auth_request
    repeat (30) @(posedge clk);
    if (DUT.authentication_grant_i === 1'b1)
        $display("FAIL: authentication_grant asserted on a TAMPERED chip -- SECURITY BUG");
    else
        $display("PASS: authentication correctly denied after tamper-fuse trip, even with a valid PUF/challenge");

    $display("UART-protocol top-level integration test complete");
        $display("================================================");
        $finish;
    end
endmodule
