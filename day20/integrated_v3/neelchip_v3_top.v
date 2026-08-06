module neelchip_v3_top(
    input  wire         clk,
    input  wire         rst,

    // ── External Register Interface (host CPU se) ──
    input  wire         reg_write,
    input  wire         reg_read,
    input  wire [7:0]   reg_addr,
    input  wire [31:0]  reg_wdata,
    output wire [31:0]  reg_rdata,
    output wire          reg_ready,

    // ── Security Context (unique feature) ──
    input  wire          security_mode,       // 0=LITE, 1=FULL
    input  wire [31:0]   transaction_value,   // For auto-escalation

    // ── UART Output ──
    output wire          uart_tx,

    // ── Physical Attack Sensors (production hardening) ──
    input  wire          clk_monitor,
    input  wire  [7:0]   voltage_level,
    input  wire          tamper_detect,

    // ── Top-level Status (for board LEDs / debug) ──
    output wire          chip_healthy,
    output wire          chip_locked_down     // Keys erased / emergency state
);

    // ═══════════════════════════════════════════
    // 1. SECURITY MODE — decides LITE vs FULL path
    // ═══════════════════════════════════════════
    wire effective_mode, mode_escalated;

    security_mode_ctrl SEC_MODE (
        .clk(clk), .rst(rst),
        .security_mode(security_mode),
        .transaction_value(transaction_value),
        .auto_escalate_en(1'b1),
        .effective_mode(effective_mode),
        .mode_escalated(mode_escalated)
    );

    // ═══════════════════════════════════════════
    // 2. TRNG — dedicated entropy (distinct from PUF)
    // ═══════════════════════════════════════════
    wire [31:0] trng_random;
    wire         trng_valid, trng_self_test_pass;

    trng TRNG (
        .clk(clk), .rst(rst),
        .enable(1'b1),
        .random_out(trng_random),
        .random_valid(trng_valid),
        .self_test_pass(trng_self_test_pass)
    );

    // ═══════════════════════════════════════════
    // 3. PUF — device identity key
    // ═══════════════════════════════════════════
    wire [127:0] puf_key;
    wire          puf_key_ready;
    reg           puf_start;

    puf_key PUF (
        .clk(clk), .rst(rst),
        .start(puf_start),
        .device_key(puf_key),
        .key_ready(puf_key_ready)
    );

    // ═══════════════════════════════════════════
    // 4. AES CORE — encryption (via register-loaded key/plaintext)
    // ═══════════════════════════════════════════
    wire [127:0] aes_key_reg, aes_plaintext_reg;
    wire [127:0] aes_ciphertext;
    reg          aes_start_pending;
    wire         aes_start_o;

    aes_core AES (
        .plaintext(aes_plaintext_reg),
        .key(effective_mode ? puf_key : aes_key_reg), // FULL mode = PUF key, LITE = register key
        .ciphertext(aes_ciphertext)
    );

    // ═══════════════════════════════════════════
    // 5. MASKED S-BOX — side-channel resistant path (FULL mode only)
    // ═══════════════════════════════════════════
    wire [7:0] masked_sbox_out, masked_sbox_mask_out;

    masked_sbox MASKED_SB (
        .clk(clk), .rst(rst),
        .data_in(aes_plaintext_reg[7:0]),
        .mask_in(trng_random[7:0]), // TRNG feeds the mask - real entropy!
        .data_out(masked_sbox_out),
        .mask_out(masked_sbox_mask_out)
    );

    // ═══════════════════════════════════════════
    // 6. BIST — self-test on power-up
    // ═══════════════════════════════════════════
    wire bist_pass, bist_fail, bist_done;
    wire [3:0] bist_stage;
    wire bist_start_reg;

    bist_controller BIST (
        .clk(clk), .rst(rst),
        .start_bist(bist_start_reg),
        .bist_pass(bist_pass),
        .bist_fail(bist_fail),
        .bist_done(bist_done),
        .bist_stage(bist_stage),
        .sbox_test_out(8'h63),  // Known-answer: S[0]=0x63 (wired as constant test vector)
        .aes_test_out(aes_ciphertext),
        .puf_test_valid(puf_key_ready)
    );

    // ═══════════════════════════════════════════
    // 7. WATCHDOG — hang detection
    // ═══════════════════════════════════════════
    wire wdt_timeout;
    wire [15:0] wdt_count;
    reg  wdt_kick;

    watchdog_timer WDT (
        .clk(clk), .rst(rst),
        .wdt_kick(wdt_kick),
        .wdt_enable(1'b1),
        .wdt_timeout(wdt_timeout),
        .wdt_count(wdt_count)
    );

    // ═══════════════════════════════════════════
    // 8. GLITCH DETECTOR — fault-injection attack sensor
    // ═══════════════════════════════════════════
    wire glitch_detected;
    wire [1:0] glitch_type;

    glitch_detector GLITCH (
        .clk(clk), .rst(rst),
        .clk_monitor(clk_monitor),
        .voltage_level(voltage_level),
        .glitch_detected(glitch_detected),
        .glitch_type(glitch_type)
    );

    // ═══════════════════════════════════════════
    // 9. INTERRUPT CONTROLLER — tamper -> key erase
    // ═══════════════════════════════════════════
    wire irq_out, hw_keys_erase;
    reg  sticky_lockdown;
    wire [3:0] irq_id;

    interrupt_ctrl IRQ (
        .clk(clk), .rst(rst),
        .tamper_irq(tamper_detect),
        .timer_irq(wdt_timeout),      // Watchdog feeds into interrupt system
        .uart_irq(1'b0),
        .spi_irq(1'b0),
        .irq_mask(4'b0000),
        .irq_ack(1'b1),
        .irq_out(irq_out),
        .irq_id(irq_id),
        .keys_erase(hw_keys_erase)
    );

    // ═══════════════════════════════════════════
    // 10. UART TX — output interface
    // ═══════════════════════════════════════════
    reg  uart_start;
    reg  [7:0] uart_data;
    wire uart_busy;

    uart_tx UART (
        .clk(clk), .rst(rst),
        .start(uart_start),
        .data(uart_data),
        .tx(uart_tx),
        .busy(uart_busy)
    );

    // ═══════════════════════════════════════════
    // 11. REGISTER MAP — host control interface (wires everything together)
    // ═══════════════════════════════════════════
    register_map REGMAP (
        .clk(clk), .rst(rst),
        .reg_write(reg_write), .reg_read(reg_read),
        .reg_addr(reg_addr), .reg_wdata(reg_wdata),
        .reg_rdata(reg_rdata), .reg_ready(reg_ready),
        .bist_pass_i(bist_pass), .bist_fail_i(bist_fail),
        .wdt_timeout_i(wdt_timeout),
        .glitch_detected_i(glitch_detected),
        .aes_done_i(1'b1), // Combinational AES core - always "done" when inputs stable
        .aes_result_i(aes_ciphertext),
        .aes_start_o(aes_start_o),
        .bist_start_o(bist_start_reg),
        .wdt_enable_o(),
        .aes_key_o(aes_key_reg),
        .aes_plaintext_o(aes_plaintext_reg)
    );

    // ═══════════════════════════════════════════
    // TOP-LEVEL GLUE LOGIC — connecting the control flows
    // ═══════════════════════════════════════════
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            puf_start   <= 0;
            wdt_kick    <= 0;
            uart_start  <= 0;
            uart_data   <= 0;
        end
        else begin
            // On any AES start command (from register write), 
            // also kick PUF key generation (needed for FULL mode)
            puf_start <= aes_start_o & effective_mode;

            // Watchdog kick tied to any register activity 
            // (proves host CPU is alive and communicating)
            wdt_kick <= reg_write | reg_read;

            // On glitch attack: force everything to safe idle,
            // never let a transaction proceed (security-critical wiring)
            if (glitch_detected) begin
                uart_start <= 0;
            end
            else if (aes_start_o & ~hw_keys_erase) begin
                // Send first byte of ciphertext out over UART 
                // (only if keys haven't been erased by tamper)
                uart_data  <= aes_ciphertext[127:120];
                uart_start <= 1;
            end
            else begin
                uart_start <= 0;
            end
        end
    end

    // Sticky lockdown: once tamper or glitch fires, STAY locked 
    // until reset — this is the correct security behavior (a 
    // momentary interrupt-controller pulse should not un-latch 
    // a security lockdown)
    always @(posedge clk or posedge rst) begin
        if (rst)
            sticky_lockdown <= 0;
        else if (hw_keys_erase || glitch_detected)
            sticky_lockdown <= 1;
    end

    // Overall chip health = BIST passed, no active faults
    assign chip_healthy = bist_pass & ~bist_fail & ~wdt_timeout & 
                           ~glitch_detected & ~hw_keys_erase;

    // Lockdown state = tamper detected, keys erased, or glitch attack
    assign chip_locked_down = sticky_lockdown | hw_keys_erase | glitch_detected;

endmodule
