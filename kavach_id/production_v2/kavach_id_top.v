module kavach_id_top(
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
    wire         bist_start_o, stabilizer_start_o, auth_request_o;
    wire         record_stage_o, verify_request_o, sync_complete_o;
    wire [1:0]   stage_id_o;
    wire [31:0]  stage_data_o;
    wire [31:0]  challenge_o;
    wire         bist_pass_i, bist_fail_i, replay_detected_i;
    wire [31:0]  stable_response_i;
    wire [5:0]   unstable_bit_count_i;
    wire         authentication_grant_i, auth_denied_bist_i, auth_denied_replay_i;
    wire         sequence_violation_i, chain_complete_i;
    wire [3:0]   stages_completed_i;
    wire [31:0]  chain_hash_i;
    wire [7:0]   offline_budget_i;
    wire         verify_allowed_i, sync_required_i;
    wire [15:0]  total_offline_uses_i;

    kavach_register_map REGMAP (
        .clk(clk), .rst(rst),
        .reg_write(reg_write), .reg_read(reg_read),
        .reg_addr(reg_addr), .reg_wdata(reg_wdata),
        .reg_rdata(reg_rdata), .reg_ready(reg_ready),
        .bist_pass_i(bist_pass_i), .bist_fail_i(bist_fail_i),
        .replay_detected_i(replay_detected_i),
        .stable_response_i(stable_response_i),
        .unstable_bit_count_i(unstable_bit_count_i),
        .authentication_grant_i(authentication_grant_i),
        .auth_denied_bist_i(auth_denied_bist_i),
        .auth_denied_replay_i(auth_denied_replay_i),
        .sequence_violation_i(sequence_violation_i),
        .chain_complete_i(chain_complete_i),
        .stages_completed_i(stages_completed_i),
        .chain_hash_i(chain_hash_i),
        .offline_budget_i(offline_budget_i),
        .verify_allowed_i(verify_allowed_i),
        .sync_required_i(sync_required_i),
        .total_offline_uses_i(total_offline_uses_i),
        .bist_start_o(bist_start_o),
        .stabilizer_start_o(stabilizer_start_o),
        .challenge_o(challenge_o),
        .auth_request_o(auth_request_o),
        .record_stage_o(record_stage_o),
        .stage_id_o(stage_id_o),
        .stage_data_o(stage_data_o),
        .verify_request_o(verify_request_o),
        .sync_complete_o(sync_complete_o)
    );

    // ═══════════════════════════════════════════
    // 2. REPLAY DETECTOR
    // ═══════════════════════════════════════════
    wire challenge_ready;
    assign challenge_ready = stabilizer_start_o;

    replay_detector REPLAY (
        .clk(clk), .rst(rst),
        .challenge_ready(challenge_ready),
        .challenge_in(challenge_o),
        .replay_detected(replay_detected_i),
        .last_challenge(),
        .history_hit_count()
    );

    // ═══════════════════════════════════════════
    // 3. PUF ARRAY
    // ═══════════════════════════════════════════
    wire [31:0] puf_response;

    puf_array PUF (
        .clk(clk), .rst(rst),
        .pulse_in(stabilizer_start_o),
        .challenge(challenge_o),
        .response(puf_response)
    );

    // ═══════════════════════════════════════════
    // 4. PUF STABILIZER
    // ═══════════════════════════════════════════
    wire stable_done;

    puf_stabilizer STAB (
        .clk(clk), .rst(rst),
        .start(stabilizer_start_o & ~replay_detected_i),
        .raw_response_1(puf_response),
        .raw_response_2(puf_response),
        .raw_response_3(puf_response),
        .stable_response(stable_response_i),
        .unstable_bit_mask(),
        .stable_done(stable_done),
        .unstable_bit_count(unstable_bit_count_i)
    );

    // ═══════════════════════════════════════════
    // 5. SCRAMBLER
    // ═══════════════════════════════════════════
    wire [31:0] scrambled_response;

    scrambler SCRAM (
        .challenge(challenge_o),
        .raw_response(stable_response_i),
        .scrambled_response(scrambled_response)
    );

    // ═══════════════════════════════════════════
    // 6. BIST
    // ═══════════════════════════════════════════
    kavach_bist BIST (
        .clk(clk), .rst(rst),
        .start_bist(bist_start_o),
        .bist_pass(bist_pass_i),
        .bist_fail(bist_fail_i),
        .bist_done(),
        .test_response(32'hCAFEBABE)
    );

    // ═══════════════════════════════════════════
    // 7. AUTH GATE — real hardware interlock
    // ═══════════════════════════════════════════
    kavach_auth_gate AUTHGATE (
        .clk(clk), .rst(rst),
        .auth_request(auth_request_o),
        .bist_fail(bist_fail_i),
        .bist_pass(bist_pass_i),
        .replay_detected(replay_detected_i),
        .authentication_grant(authentication_grant_i),
        .auth_denied_bist(auth_denied_bist_i),
        .auth_denied_replay(auth_denied_replay_i)
    );

    // ═══════════════════════════════════════════
    // 8. PROVENANCE CHAIN — supply-chain stage tracking
    // ═══════════════════════════════════════════
    provenance_chain PROVENANCE (
        .clk(clk), .rst(rst),
        .record_stage(record_stage_o),
        .stage_id(stage_id_o),
        .stage_data(stage_data_o),
        .chain_hash(chain_hash_i),
        .stages_completed(stages_completed_i),
        .sequence_violation(sequence_violation_i),
        .chain_complete(chain_complete_i)
    );

    // ═══════════════════════════════════════════
    // 9. OFFLINE VERIFY COUNTER
    // ═══════════════════════════════════════════
    offline_verify_counter OFFLINE (
        .clk(clk), .rst(rst),
        .verify_request(verify_request_o),
        .sync_complete(sync_complete_o),
        .offline_budget(offline_budget_i),
        .verify_allowed(verify_allowed_i),
        .sync_required(sync_required_i),
        .total_offline_uses(total_offline_uses_i)
    );

    // ═══════════════════════════════════════════
    // 10. ENCRYPTED CHANNEL
    // ═══════════════════════════════════════════
    wire [31:0] ciphertext_out;
    wire        encrypt_done;

    encrypted_channel ENC (
        .clk(clk), .rst(rst),
        .shared_key(32'hDEADBEEF),
        .new_session(stabilizer_start_o),
        .plaintext_in(scrambled_response),
        .encrypt_start(stable_done),
        .ciphertext_out(ciphertext_out),
        .encrypt_done(encrypt_done),
        .ciphertext_in(32'h0),
        .rx_msg_counter_in(16'h0),
        .decrypt_start(1'b0),
        .plaintext_out(),
        .decrypt_done(),
        .session_nonce_out(),
        .tx_msg_counter_out()
    );

    // ═══════════════════════════════════════════
    // 11. UART TX/RX
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

    // Transmit only when the encryption finished AND the hardware
    // interlock actually granted authentication — not just "not replayed".
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            uart_start <= 0;
            uart_data  <= 0;
        end
        else if (encrypt_done & authentication_grant_i) begin
            uart_data  <= ciphertext_out[31:24];
            uart_start <= 1;
        end
        else begin
            uart_start <= 0;
        end
    end

    // ═══════════════════════════════════════════
    // TOP-LEVEL STATUS
    // ═══════════════════════════════════════════
    assign chip_healthy         = bist_pass_i & ~bist_fail_i;
    assign verification_blocked = replay_detected_i | bist_fail_i | auth_denied_bist_i | auth_denied_replay_i;

endmodule
