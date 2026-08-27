module kavach_id_top(
    input  wire         clk,        // external clock (bench/lab testing)
    input  wire         rst,        // external reset (optional; POR also generates one internally)
    input  wire         clk_sel,    // 0 = use external clk, 1 = use internal ring_oscillator (deployed/passive operation)

    input  wire         uart_rx_in,
    output wire         uart_tx_out,

    output wire          chip_healthy,
    output wire          verification_blocked
);

    // ── CLOCK SOURCE SELECTION (deployment hardening) ──
    // See ring_oscillator.v for full rationale: enables operation
    // without any external crystal/clock source for deployed/passive
    // (e.g. NFC-powered) use cases, while preserving external-clock
    // capability for bench testing and characterization.
    wire osc_clk;
    ring_oscillator OSC (
        .enable(1'b1),   // free-runs unconditionally; unused output when clk_sel=0
        .clk_out(osc_clk)
    );
    wire int_clk = clk_sel ? osc_clk : clk;

    // ── POWER-ON-RESET (deployment hardening) ──
    // See por_circuit.v for full rationale: guarantees the chip enters
    // a known reset state purely from power arriving, with no
    // dependency on an external reset signal (essential for deployed/
    // passive operation where no host may be present at power-up to
    // drive rst). ORed with the external rst so either source can
    // trigger a reset.
    wire por_reset;
    por_circuit POR (
        .clk(int_clk),
        .por_reset(por_reset)
    );
    wire combined_rst = rst | por_reset;

    // ── RESET SYNCHRONIZER (hardening fix) ──
    wire rst_sync;
    reset_sync RESET_SYNC (
        .clk(int_clk),
        .rst_in(combined_rst),
        .rst_out(rst_sync)
    );

    // ═══════════════════════════════════════════
    // 0. UART-TO-REGISTER BRIDGE (interface hardening fix)
    // FIX: kavach_id_top.v previously exposed its internal parallel
    // register bus (reg_write/reg_read/reg_addr[7:0]/reg_wdata[31:0]/
    // reg_rdata[31:0]/reg_ready - ~50 pins) directly as TOP-LEVEL CHIP
    // PINS. No realistic reader device or phone can wire to a ~50-pin
    // parallel bus. This bridge moves the register bus fully INSIDE
    // the chip: externally, only clk/rst/uart_rx_in/uart_tx_out are
    // exposed. See uart_to_reg_bridge.v for the 6-byte frame protocol.
    // ═══════════════════════════════════════════
    wire         reg_write, reg_read;
    wire [7:0]   reg_addr;
    wire [31:0]  reg_wdata;
    wire [31:0]  reg_rdata;
    wire         reg_ready;

    uart_to_reg_bridge BRIDGE (
        .clk(int_clk), .rst(rst_sync),
        .uart_rx_in(uart_rx_in),
        .uart_tx_out(uart_tx_out),
        .reg_write(reg_write), .reg_read(reg_read),
        .reg_addr(reg_addr), .reg_wdata(reg_wdata),
        .reg_rdata(reg_rdata), .reg_ready(reg_ready)
    );

    // ═══════════════════════════════════════════
    // 1. REGISTER MAP
    // ═══════════════════════════════════════════
    wire         bist_start_o, stabilizer_start_o, auth_request_o;
    reg          auth_request_prev;
    wire         auth_request_pulse;
    always @(posedge int_clk or posedge rst_sync) begin
        if (rst_sync) auth_request_prev <= 0;
        else          auth_request_prev <= auth_request_o;
    end
    assign auth_request_pulse = auth_request_o & ~auth_request_prev;
    wire         sync_complete_o, record_stage_o;
    wire [1:0]   stage_id_o;
    wire [31:0]  challenge_o, stage_data_o;
    wire         bist_pass_raw, bist_fail_raw, replay_detected_i;
    wire [31:0]  stable_response_i;
    wire [5:0]   unstable_bit_count_i;
    wire         auth_grant_raw, auth_denied_bist_raw, auth_denied_replay_raw;
    wire         sequence_violation_raw, chain_complete_i;
    reg          sequence_violation_i;
    wire [3:0]   stages_completed_i;
    wire [7:0]   offline_budget_i;
    wire         sync_required_i, verify_allowed_i;
    wire [15:0]  total_offline_uses_i;

    // ── STICKY STATUS LATCHES ──
    reg bist_pass_i, bist_fail_i;
    reg authentication_grant_i, auth_denied_bist_i, auth_denied_replay_i;
    reg auth_denied_budget_i;

    always @(posedge int_clk or posedge rst_sync) begin
        if (rst_sync) begin
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

    // FIX: sequence_violation from provenance_chain.v is a single-cycle
    // pulse (mirrors the original module's design - see
    // provenance_chain.v). It was previously wired directly to the
    // register map with no latch, so a host reading PROVENANCE_STATUS
    // even a few cycles after the violation-detecting cycle would see
    // it already cleared and incorrectly conclude no violation
    // occurred - confirmed via offline_provenance_uart_tb.v's TEST F
    // after provenance_chain.v's SHA-256 redesign (~120-cycle hash
    // latency between record_stage and the status becoming stable)
    // made this window impossible to hit by accident, whereas the
    // prior XOR-hash version's near-combinational timing had
    // apparently made this pass by coincidence in earlier testing.
    // chain_complete does not need this fix: it is already latched
    // inside provenance_chain.v itself (only cleared by reset).
    always @(posedge int_clk or posedge rst_sync) begin
        if (rst_sync)
            sequence_violation_i <= 1'b0;
        else if (record_stage_o)
            sequence_violation_i <= 1'b0; // clear at the start of each new attempt
        else if (sequence_violation_raw)
            sequence_violation_i <= 1'b1;
    end

    wire final_grant_this_cycle = auth_grant_raw & verify_allowed_i;
    wire budget_denial_this_cycle = auth_grant_raw & ~verify_allowed_i;

    always @(posedge int_clk or posedge rst_sync) begin
        if (rst_sync) begin
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
    wire         prog_enable_w;
    wire [127:0] prog_key_in_w;
    wire         key_locked_w;
    wire [127:0] chip_key_w;

    key_storage KEYSTORE (
        .clk(int_clk), .rst(rst_sync),
        .prog_enable(prog_enable_w),
        .prog_key_in(prog_key_in_w),
        .chip_key(chip_key_w),
        .key_locked(key_locked_w)
    );

    kavach_register_map REGMAP (
        .clk(int_clk), .rst(rst_sync),
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
        .prog_key_in_o(prog_key_in_w),
        .ciphertext_i(ciphertext_out),
        .tx_counter_i(tx_msg_counter_out)
    );

    // ═══════════════════════════════════════════
    // 2. REPLAY DETECTOR
    // ═══════════════════════════════════════════
    wire challenge_ready;
    assign challenge_ready = stabilizer_start_o;

    replay_detector REPLAY (
        .clk(int_clk), .rst(rst_sync),
        .challenge_ready(challenge_ready),
        .challenge_in(challenge_o),
        .replay_detected(replay_detected_i),
        .last_challenge(),
        .history_hit_count()
    );

    // ═══════════════════════════════════════════
    // 3. PUF ARRAY + RESAMPLE CONTROLLER
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
        .clk(int_clk), .rst(rst_sync),
        .pulse_in(puf_pulse),
        .challenge(challenge_o),
        .response(puf_response)
    );

    always @(posedge int_clk or posedge rst_sync) begin
        if (rst_sync) begin
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
    // ═══════════════════════════════════════════
    wire stable_done;

    puf_stabilizer STAB (
        .clk(int_clk), .rst(rst_sync),
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
        .clk(int_clk), .rst(rst_sync),
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
        .clk(int_clk), .rst(rst_sync),
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
        .clk(int_clk), .rst(rst_sync),
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
        .clk(int_clk), .rst(rst_sync),
        .record_stage(record_stage_o),
        .stage_id(stage_id_o),
        .stage_data(stage_data_o),
        .chain_hash(),
        .stages_completed(stages_completed_i),
        .sequence_violation(sequence_violation_raw),
        .chain_complete(chain_complete_i)
    );

    // ═══════════════════════════════════════════
    // 10. ENCRYPTED CHANNEL
    // FIX: previously drove a dedicated, always-listening UART_TX that
    // auto-pushed ciphertext on every successful authentication - this
    // conflicted with the host-driven command/response protocol on the
    // SAME physical uart_tx_out pin (see bridge above). The channel's
    // ciphertext_out/tx_msg_counter_out are now exposed as read-only
    // registers (CIPHERTEXT_DATA 0x34, TX_COUNTER 0x38); the host
    // explicitly reads them via the bridge instead of the chip pushing
    // unsolicited data that could collide with an in-flight command.
    // ═══════════════════════════════════════════
    wire [31:0] ciphertext_out;
    wire        encrypt_done;
    wire [15:0] session_nonce_unused, tx_msg_counter_out;

    encrypted_channel ENC (
        .clk(int_clk), .rst(rst_sync),
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
    // TOP-LEVEL STATUS
    // ═══════════════════════════════════════════
    assign chip_healthy         = bist_pass_i & ~bist_fail_i;
    assign verification_blocked = auth_denied_bist_i | auth_denied_replay_i | auth_denied_budget_i;

endmodule
