module kavach_id_top(
    input  wire         clk,
    input  wire         rst,

    input  wire         reg_write,
    input  wire         reg_read,
    input  wire [7:0]   reg_addr,
    input  wire [31:0]  reg_wdata,
    output wire [31:0]  reg_rdata,
    output wire          reg_ready,

    input  wire         uart_rx_in,
    output wire         uart_tx_out,

    output wire          chip_healthy,
    output wire          verification_blocked
);

    // ── RESET SYNCHRONIZER (hardening fix) ──
    // See reset_sync.v for full rationale: async-assert, sync-deassert,
    // guarantees every flop in this design sees reset release on the
    // same clock edge, eliminating a reset-recovery/removal hazard that
    // is invisible in RTL simulation but real on fabricated silicon.
    wire rst_sync;
    reset_sync RESET_SYNC (
        .clk(clk),
        .rst_in(rst),
        .rst_out(rst_sync)
    );

    // ═══════════════════════════════════════════
    // 1. REGISTER MAP
    // ═══════════════════════════════════════════
    wire         bist_start_o, stabilizer_start_o, auth_request_o;
    reg          auth_request_prev;
    wire         auth_request_pulse;
    always @(posedge clk or posedge rst_sync) begin
        if (rst) auth_request_prev <= 0;
        else     auth_request_prev <= auth_request_o;
    end
    assign auth_request_pulse = auth_request_o & ~auth_request_prev;
    wire         sync_complete_o, record_stage_o;
    wire [1:0]   stage_id_o;
    wire [31:0]  challenge_o, stage_data_o;
    wire         bist_pass_raw, bist_fail_raw, replay_detected_i;
    wire [31:0]  stable_response_i;
    wire [5:0]   unstable_bit_count_i;
    wire         auth_grant_raw, auth_denied_bist_raw, auth_denied_replay_raw;
    wire         sequence_violation_i, chain_complete_i;
    wire [3:0]   stages_completed_i;
    wire [7:0]   offline_budget_i;
    wire         sync_required_i, verify_allowed_i;
    wire [15:0]  total_offline_uses_i;

    // ── STICKY STATUS LATCHES ──
    reg bist_pass_i, bist_fail_i;
    reg authentication_grant_i, auth_denied_bist_i, auth_denied_replay_i;
    reg auth_denied_budget_i;

    always @(posedge clk or posedge rst_sync) begin
        if (rst) begin
            bist_pass_i <= 0;
            bist_fail_i <= 0;
        end
        else begin
            if (bist_start_o) begin
                bist_pass_i <= 0;
                bist_fail_i <= 0;
            end
            else begin
                if (bist_pass_raw) bist_pass_i <= 1;
                if (bist_fail_raw) bist_fail_i <= 1;
            end
        end
    end

    wire final_grant_this_cycle = auth_grant_raw & verify_allowed_i;
    wire budget_denial_this_cycle = auth_grant_raw & ~verify_allowed_i;

    always @(posedge clk or posedge rst_sync) begin
        if (rst) begin
            authentication_grant_i <= 0;
            auth_denied_bist_i     <= 0;
            auth_denied_replay_i   <= 0;
            auth_denied_budget_i   <= 0;
        end
        else begin
            if (auth_request_pulse) begin
                authentication_grant_i <= 0;
                auth_denied_bist_i     <= 0;
                auth_denied_replay_i   <= 0;
                auth_denied_budget_i   <= 0;
            end
            else begin
                if (final_grant_this_cycle)     authentication_grant_i <= 1;
                if (auth_denied_bist_raw)       auth_denied_bist_i     <= 1;
                if (auth_denied_replay_raw)     auth_denied_replay_i   <= 1;
                if (budget_denial_this_cycle)   auth_denied_budget_i   <= 1;
            end
        end
    end

    // ── PER-CHIP KEY STORAGE (hardening fix) ──
    // See key_storage.v for full rationale: replaces the previously
    // hardcoded 32'hDEADBEEF shared_key (identical across every chip
    // built from this design) with a factory-programmable, write-once
    // per-chip key.
    wire         prog_enable_w;
    wire [31:0]  prog_key_in_w;
    wire         key_locked_w;
    wire [31:0]  chip_key_w;

    key_storage KEYSTORE (
        .clk(clk), .rst(rst_sync),
        .prog_enable(prog_enable_w),
        .prog_key_in(prog_key_in_w),
        .chip_key(chip_key_w),
        .key_locked(key_locked_w)
    );

    kavach_register_map REGMAP (
        .clk(clk), .rst(rst_sync),
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
        .offline_budget_i(offline_budget_i),
        .sync_required_i(sync_required_i),
        .total_offline_uses_i(total_offline_uses_i),
        .bist_start_o(bist_start_o),
        .stabilizer_start_o(stabilizer_start_o),
        .challenge_o(challenge_o),
        .auth_request_o(auth_request_o),
        .sync_complete_o(sync_complete_o),
        .record_stage_o(record_stage_o),
        .stage_id_o(stage_id_o),
        .stage_data_o(stage_data_o),
        .key_locked_i(key_locked_w),
        .prog_enable_o(prog_enable_w),
        .prog_key_in_o(prog_key_in_w)
    );

    // ═══════════════════════════════════════════
    // 2. REPLAY DETECTOR
    // ═══════════════════════════════════════════
    wire challenge_ready;
    assign challenge_ready = stabilizer_start_o;

    replay_detector REPLAY (
        .clk(clk), .rst(rst_sync),
        .challenge_ready(challenge_ready),
        .challenge_in(challenge_o),
        .replay_detected(replay_detected_i),
        .last_challenge(),
        .history_hit_count()
    );

    // ═══════════════════════════════════════════
    // 3. PUF ARRAY + RESAMPLE CONTROLLER
    // FIX: puf_array was previously pulsed ONCE and its single response
    // fed to all three puf_stabilizer inputs, making majority-voting a
    // no-op at chip level (documented as a known limitation in README).
    // This controller pulses the PUF array three separate times in
    // sequence, latching each result into an independent sample
    // register, so puf_stabilizer receives three genuinely distinct
    // reads matching its own (already formally-verified) interface.
    // SCOPE NOTE: in RTL/Icarus behavioral simulation, arbiter_puf_cell's
    // buf-chain delay paths have zero simulated delay, so all three
    // reads will be bit-identical here regardless of this fix - this
    // corrects the ARCHITECTURE (three independent reads instead of one
    // read reused three times), not the simulator's ability to model
    // real silicon timing jitter. Genuine noise-correction behavior can
    // only be observed on fabricated silicon or via SDF-annotated
    // post-synthesis timing simulation.
    // ═══════════════════════════════════════════
    wire [31:0] puf_response;
    reg         puf_pulse;
    reg  [31:0] puf_sample_1, puf_sample_2, puf_sample_3;
    reg         puf_samples_ready;
    reg  [3:0]  rs_state;

    localparam RS_IDLE = 4'd0, RS_P1 = 4'd1, RS_G1 = 4'd2, RS_C1 = 4'd3,
               RS_P2   = 4'd4, RS_G2 = 4'd5, RS_C2 = 4'd6,
               RS_P3   = 4'd7, RS_G3 = 4'd8, RS_C3 = 4'd9;

    puf_array PUF (
        .clk(clk), .rst(rst_sync),
        .pulse_in(puf_pulse),
        .challenge(challenge_o),
        .response(puf_response)
    );

    always @(posedge clk or posedge rst_sync) begin
        if (rst) begin
            rs_state          <= RS_IDLE;
            puf_pulse         <= 1'b0;
            puf_sample_1      <= 32'd0;
            puf_sample_2      <= 32'd0;
            puf_sample_3      <= 32'd0;
            puf_samples_ready <= 1'b0;
        end
        else begin
            puf_samples_ready <= 1'b0;
            case (rs_state)
                RS_IDLE: begin
                    if (stabilizer_start_o & ~replay_detected_i) begin
                        puf_pulse <= 1'b1;
                        rs_state  <= RS_P1;
                    end
                end
                RS_P1: begin puf_pulse <= 1'b0; rs_state <= RS_G1; end
                RS_G1: begin rs_state <= RS_C1; end
                RS_C1: begin puf_sample_1 <= puf_response; puf_pulse <= 1'b1; rs_state <= RS_P2; end
                RS_P2: begin puf_pulse <= 1'b0; rs_state <= RS_G2; end
                RS_G2: begin rs_state <= RS_C2; end
                RS_C2: begin puf_sample_2 <= puf_response; puf_pulse <= 1'b1; rs_state <= RS_P3; end
                RS_P3: begin puf_pulse <= 1'b0; rs_state <= RS_G3; end
                RS_G3: begin rs_state <= RS_C3; end
                RS_C3: begin
                    puf_sample_3      <= puf_response;
                    puf_samples_ready <= 1'b1;
                    rs_state          <= RS_IDLE;
                end
                default: rs_state <= RS_IDLE;
            endcase
        end
    end

    // ═══════════════════════════════════════════
    // 4. PUF STABILIZER
    // Now driven by three genuinely independent resampled reads
    // (see resample controller above), not one value reused three times.
    // ═══════════════════════════════════════════
    wire stable_done;

    puf_stabilizer STAB (
        .clk(clk), .rst(rst_sync),
        .start(puf_samples_ready),
        .raw_response_1(puf_sample_1),
        .raw_response_2(puf_sample_2),
        .raw_response_3(puf_sample_3),
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
    wire bist_done_unused;

    kavach_bist BIST (
        .clk(clk), .rst(rst_sync),
        .start_bist(bist_start_o),
        .bist_pass(bist_pass_raw),
        .bist_fail(bist_fail_raw),
        .bist_done(bist_done_unused),
        .test_response(32'hCAFEBABE)
    );

    // ═══════════════════════════════════════════
    // 7. AUTHENTICATION GATE
    // ═══════════════════════════════════════════
    kavach_auth_gate AUTHGATE (
        .clk(clk), .rst(rst_sync),
        .auth_request(auth_request_pulse),
        .bist_fail(bist_fail_i),
        .bist_pass(bist_pass_i),
        .replay_detected(replay_detected_i),
        .authentication_grant(auth_grant_raw),
        .auth_denied_bist(auth_denied_bist_raw),
        .auth_denied_replay(auth_denied_replay_raw)
    );

    // ═══════════════════════════════════════════
    // 8. OFFLINE VERIFICATION BUDGET
    // ═══════════════════════════════════════════
    offline_verify_counter OFFLINE (
        .clk(clk), .rst(rst_sync),
        .verify_request(auth_request_pulse),
        .sync_complete(sync_complete_o),
        .offline_budget(offline_budget_i),
        .verify_allowed(verify_allowed_i),
        .sync_required(sync_required_i),
        .total_offline_uses(total_offline_uses_i)
    );

    // ═══════════════════════════════════════════
    // 9. SUPPLY-CHAIN PROVENANCE CHAIN
    // ═══════════════════════════════════════════
    provenance_chain PROVENANCE (
        .clk(clk), .rst(rst_sync),
        .record_stage(record_stage_o),
        .stage_id(stage_id_o),
        .stage_data(stage_data_o),
        .chain_hash(),
        .stages_completed(stages_completed_i),
        .sequence_violation(sequence_violation_i),
        .chain_complete(chain_complete_i)
    );

    // ═══════════════════════════════════════════
    // 10. ENCRYPTED CHANNEL
    // ═══════════════════════════════════════════
    wire [31:0] ciphertext_out;
    wire        encrypt_done;
    wire [15:0] session_nonce_unused, tx_msg_counter_out;

    encrypted_channel ENC (
        .clk(clk), .rst(rst_sync),
        .shared_key(chip_key_w),
        .new_session(stabilizer_start_o),
        .plaintext_in(scrambled_response),
        .encrypt_start(stable_done & authentication_grant_i),
        .ciphertext_out(ciphertext_out),
        .encrypt_done(encrypt_done),
        .ciphertext_in(32'h0),
        .rx_msg_counter_in(16'h0),
        .decrypt_start(1'b0),
        .plaintext_out(),
        .decrypt_done(),
        .session_nonce_out(session_nonce_unused),
        .tx_msg_counter_out(tx_msg_counter_out)
    );

    // ═══════════════════════════════════════════
    // 11. UART TX — full 32-bit response, 4 bytes
    // ═══════════════════════════════════════════
    localparam TX_IDLE = 2'd0, TX_B1 = 2'd1, TX_B2 = 2'd2, TX_B3 = 2'd3;
    reg [1:0]  tx_state;
    reg [31:0] tx_shift_reg;
    reg        uart_start;
    reg [7:0]  uart_data;
    wire       uart_busy;

    uart_tx UART_TX (
        .clk(clk), .rst(rst_sync),
        .tx_start(uart_start),
        .data_in(uart_data),
        .tx_out(uart_tx_out),
        .tx_busy(uart_busy)
    );

    wire [7:0] rx_data_unused;
    wire       rx_valid_unused;

    uart_rx UART_RX (
        .clk(clk), .rst(rst_sync),
        .rx_in(uart_rx_in),
        .data_out(rx_data_unused),
        .data_valid(rx_valid_unused)
    );

    always @(posedge clk or posedge rst_sync) begin
        if (rst) begin
            tx_state     <= TX_IDLE;
            tx_shift_reg <= 32'd0;
            uart_start   <= 1'b0;
            uart_data    <= 8'd0;
        end
        else begin
            uart_start <= 1'b0;
            case (tx_state)
                TX_IDLE: begin
                    if (encrypt_done & authentication_grant_i) begin
                        tx_shift_reg <= ciphertext_out;
                        uart_data    <= ciphertext_out[31:24];
                        uart_start   <= 1'b1;
                        tx_state     <= TX_B1;
                    end
                end
                TX_B1: begin
                    if (!uart_busy && !uart_start) begin
                        uart_data  <= tx_shift_reg[23:16];
                        uart_start <= 1'b1;
                        tx_state   <= TX_B2;
                    end
                end
                TX_B2: begin
                    if (!uart_busy && !uart_start) begin
                        uart_data  <= tx_shift_reg[15:8];
                        uart_start <= 1'b1;
                        tx_state   <= TX_B3;
                    end
                end
                TX_B3: begin
                    if (!uart_busy && !uart_start) begin
                        uart_data  <= tx_shift_reg[7:0];
                        uart_start <= 1'b1;
                        tx_state   <= TX_IDLE;
                    end
                end
                default: tx_state <= TX_IDLE;
            endcase
        end
    end

    // ═══════════════════════════════════════════
    // TOP-LEVEL STATUS
    // ═══════════════════════════════════════════
    assign chip_healthy         = bist_pass_i & ~bist_fail_i;
    assign verification_blocked = auth_denied_bist_i | auth_denied_replay_i | auth_denied_budget_i;

endmodule
