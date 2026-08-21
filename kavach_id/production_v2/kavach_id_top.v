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

    // ═══════════════════════════════════════════
    // 1. REGISTER MAP
    // ═══════════════════════════════════════════
    wire         bist_start_o, stabilizer_start_o, auth_request_o;
    reg          auth_request_prev;
    wire         auth_request_pulse;
    always @(posedge clk or posedge rst) begin
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
    // (see prior integration commit for full rationale: bist_pass/
    // bist_fail/authentication_grant/auth_denied_* are all one-cycle
    // pulses from their source modules and must be latched here for a
    // real host to reliably observe them via register polling)
    reg bist_pass_i, bist_fail_i;
    reg authentication_grant_i, auth_denied_bist_i, auth_denied_replay_i;
    reg auth_denied_budget_i; // NEW: offline budget exhausted denial

    always @(posedge clk or posedge rst) begin
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

    // Final grant now also requires the offline-verification budget to
    // be non-exhausted (verify_allowed_i), enforcing the same property
    // formally proven for offline_verify_counter.v in isolation: a
    // zero-budget device must never be able to authenticate.
    wire final_grant_this_cycle = auth_grant_raw & verify_allowed_i;
    wire budget_denial_this_cycle = auth_grant_raw & ~verify_allowed_i;

    always @(posedge clk or posedge rst) begin
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
        .stage_data_o(stage_data_o)
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
    // KNOWN LIMITATION (see README): all three "samples" are the same
    // combinational puf_response value in this integration.
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
    wire bist_done_unused;

    kavach_bist BIST (
        .clk(clk), .rst(rst),
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
        .clk(clk), .rst(rst),
        .auth_request(auth_request_pulse),
        .bist_fail(bist_fail_i),
        .bist_pass(bist_pass_i),
        .replay_detected(replay_detected_i),
        .authentication_grant(auth_grant_raw),
        .auth_denied_bist(auth_denied_bist_raw),
        .auth_denied_replay(auth_denied_replay_raw)
    );

    // ═══════════════════════════════════════════
    // 8. OFFLINE VERIFICATION BUDGET (NEW - was previously unwired)
    // Every auth_request consumes one unit of offline budget - closes
    // the same real-world gap the module's own README documents (rural/
    // low-connectivity deployment) at the top-chip level, not just in
    // isolated simulation.
    // ═══════════════════════════════════════════
    offline_verify_counter OFFLINE (
        .clk(clk), .rst(rst),
        .verify_request(auth_request_pulse),
        .sync_complete(sync_complete_o),
        .offline_budget(offline_budget_i),
        .verify_allowed(verify_allowed_i),
        .sync_required(sync_required_i),
        .total_offline_uses(total_offline_uses_i)
    );

    // ═══════════════════════════════════════════
    // 9. SUPPLY-CHAIN PROVENANCE CHAIN (NEW - was previously unwired)
    // Host drives this independently via STAGE_ID/STAGE_DATA/CONTROL[4]
    // - it is a separate audit function from device authentication, not
    // part of the auth_request critical path.
    // ═══════════════════════════════════════════
    provenance_chain PROVENANCE (
        .clk(clk), .rst(rst),
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
        .clk(clk), .rst(rst),
        .shared_key(32'hDEADBEEF),
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
