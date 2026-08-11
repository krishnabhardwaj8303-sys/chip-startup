module kavach_id_v2_top(
    input  wire         clk,
    input  wire         rst,

    // ── External Register Interface ──
    input  wire         reg_write,
    input  wire         reg_read,
    input  wire [7:0]   reg_addr,
    input  wire [31:0]  reg_wdata,
    output wire [31:0]  reg_rdata,
    output wire          reg_ready,

    // ── UART Physical Pins (legacy interface, still present) ──
    input  wire         uart_rx_in,
    output wire         uart_tx_out,

    // ── Status ──
    output wire          chip_healthy,
    output wire          verification_blocked
);

    // ═══════════════════════════════════════════
    // 1. REGISTER MAP — host control interface
    // ═══════════════════════════════════════════
    wire         bist_start_o, stabilizer_start_o;
    wire [31:0]  challenge_o;
    wire         bist_pass_i, bist_fail_i, replay_detected_i;
    wire [31:0]  stable_response_i;
    wire [5:0]   unstable_bit_count_i;

    kavach_register_map REGMAP (
        .clk(clk), .rst(rst),
        .reg_write(reg_write), .reg_read(reg_read),
        .reg_addr(reg_addr), .reg_wdata(reg_wdata),
        .reg_rdata(reg_rdata), .reg_ready(reg_ready),
        .bist_pass_i(bist_pass_i), .bist_fail_i(bist_fail_i),
        .replay_detected_i(replay_detected_i),
        .stable_response_i(stable_response_i),
        .unstable_bit_count_i(unstable_bit_count_i),
        .bist_start_o(bist_start_o),
        .stabilizer_start_o(stabilizer_start_o),
        .challenge_o(challenge_o)
    );

    // ═══════════════════════════════════════════
    // 2. REPLAY DETECTOR — blocks repeated challenges
    // ═══════════════════════════════════════════
    wire challenge_ready;
    assign challenge_ready = stabilizer_start_o; // Triggering a verify = new challenge presented

    replay_detector REPLAY (
        .clk(clk), .rst(rst),
        .challenge_ready(challenge_ready),
        .challenge_in(challenge_o),
        .replay_detected(replay_detected_i),
        .last_challenge(),
        .history_hit_count()
    );

    // ═══════════════════════════════════════════
    // 3. PUF ARRAY — raw device fingerprint (3 samples for stabilizer)
    // ═══════════════════════════════════════════
    wire [31:0] puf_response;

    puf_array PUF (
        .clk(clk), .rst(rst),
        .pulse_in(stabilizer_start_o),
        .challenge(challenge_o),
        .response(puf_response)
    );

    // ═══════════════════════════════════════════
    // 4. PUF STABILIZER — majority-voting noise correction
    //    (using the same PUF response sampled 3 times as a 
    //     simplified stand-in for 3 independent physical samples)
    // ═══════════════════════════════════════════
    wire stable_done;

    puf_stabilizer STAB (
        .clk(clk), .rst(rst),
        .start(stabilizer_start_o & ~replay_detected_i), // Blocked on replay!
        .raw_response_1(puf_response),
        .raw_response_2(puf_response),
        .raw_response_3(puf_response),
        .stable_response(stable_response_i),
        .unstable_bit_mask(),
        .stable_done(stable_done),
        .unstable_bit_count(unstable_bit_count_i)
    );

    // ═══════════════════════════════════════════
    // 5. SCRAMBLER — obfuscate before transmission
    // ═══════════════════════════════════════════
    wire [31:0] scrambled_response;

    scrambler SCRAM (
        .challenge(challenge_o),
        .raw_response(stable_response_i),
        .scrambled_response(scrambled_response)
    );

    // ═══════════════════════════════════════════
    // 6. ENCRYPTED CHANNEL — session-nonce keystream over UART
    // ═══════════════════════════════════════════
    wire [31:0] ciphertext_out;
    wire        encrypt_done;

    encrypted_channel ENC (
        .clk(clk), .rst(rst),
        .shared_key(32'hDEADBEEF), // Factory-provisioned (would come from PUF-derived secret)
        .new_session(stabilizer_start_o),
        .plaintext_in(scrambled_response),
        .encrypt_start(stable_done),
        .ciphertext_out(ciphertext_out),
        .encrypt_done(encrypt_done),
        .ciphertext_in(32'h0),
        .decrypt_start(1'b0),
        .plaintext_out(),
        .decrypt_done()
    );

    // ═══════════════════════════════════════════
    // 7. UART TX — send encrypted response out
    // ═══════════════════════════════════════════
    reg  uart_start;
    reg  [7:0] uart_data;
    wire uart_busy;

    uart_tx UART_TX (
        .clk(clk), .rst(rst),
        .tx_start(uart_start),
        .data_in(uart_data),
        .tx_out(uart_tx_out),
        .tx_busy(uart_busy)
    );

    wire [7:0] rx_data_unused;
    wire       rx_valid_unused;

    uart_rx UART_RX (
        .clk(clk), .rst(rst),
        .rx_in(uart_rx_in),
        .data_out(rx_data_unused),
        .data_valid(rx_valid_unused)
    );

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            uart_start <= 0;
            uart_data  <= 0;
        end
        else if (encrypt_done & ~replay_detected_i) begin
            // Only transmit if this wasn't a blocked replay attempt
            uart_data  <= ciphertext_out[31:24];
            uart_start <= 1;
        end
        else begin
            uart_start <= 0;
        end
    end

    // ═══════════════════════════════════════════
    // 8. BIST — self-test on power-up
    // ═══════════════════════════════════════════
    kavach_bist BIST (
        .clk(clk), .rst(rst),
        .start_bist(bist_start_o),
        .bist_pass(bist_pass_i),
        .bist_fail(bist_fail_i),
        .bist_done(),
        .test_response(32'hCAFEBABE) // Known-answer factory test value
    );

    // ═══════════════════════════════════════════
    // TOP-LEVEL STATUS
    // ═══════════════════════════════════════════
    assign chip_healthy         = bist_pass_i & ~bist_fail_i;
    assign verification_blocked = replay_detected_i | bist_fail_i;

endmodule
