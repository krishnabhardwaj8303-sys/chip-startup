module top_formal(
    input  wire         clk,
    input  wire         rst,
    // register_map interface inputs
    input  wire         reg_write,
    input  wire         reg_read,
    input  wire [7:0]   reg_addr,
    input  wire [31:0]  reg_wdata,
    input  wire         aes_done_i,
    input  wire [127:0] aes_result_i,
    // glitch_detector interface inputs
    input  wire         clk_monitor,
    input  wire [7:0]   voltage_level,
    // watchdog_timer interface inputs
    input  wire         wdt_kick,
    input  wire         wdt_enable,
    // bist_controller interface inputs
    input  wire         start_bist,
    input  wire [7:0]   sbox_test_out,
    input  wire [127:0] aes_test_out,
    input  wire         puf_test_valid,
    // safety_assertions ke liye extra free input
    input  wire         trip_signal
);

    // ---- glitch_detector instance ----
    wire glitch_detected;
    wire glitch_now;
    wire [1:0] glitch_type;
    glitch_detector u_glitch (
        .clk(clk), .rst(rst),
        .clk_monitor(clk_monitor),
        .voltage_level(voltage_level),
        .glitch_detected(glitch_detected),
        .glitch_type(glitch_type),
        .glitch_now(glitch_now)
    );

    // ---- bist_controller instance ----
    wire bist_pass, bist_fail, bist_done;
    wire [3:0] bist_stage;
    bist_controller u_bist (
        .clk(clk), .rst(rst),
        .start_bist(start_bist),
        .bist_pass(bist_pass),
        .bist_fail(bist_fail),
        .bist_done(bist_done),
        .bist_stage(bist_stage),
        .sbox_test_out(sbox_test_out),
        .aes_test_out(aes_test_out),
        .puf_test_valid(puf_test_valid)
    );

    // ---- watchdog_timer instance ----
    wire wdt_timeout;
    wire [15:0] wdt_count;
    watchdog_timer u_wdt (
        .clk(clk), .rst(rst),
        .wdt_kick(wdt_kick),
        .wdt_enable(wdt_enable),
        .wdt_timeout(wdt_timeout),
        .wdt_count(wdt_count)
    );

    // ---- register_map instance (aes_start_o source) ----
    wire [31:0] reg_rdata;
    wire        reg_ready;
    wire        aes_start_o, bist_start_o, wdt_enable_o;
    wire [127:0] aes_key_o, aes_plaintext_o;

    register_map u_regmap (
        .clk(clk), .rst(rst),
        .reg_write(reg_write),
        .reg_read(reg_read),
        .reg_addr(reg_addr),
        .reg_wdata(reg_wdata),
        .reg_rdata(reg_rdata),
        .reg_ready(reg_ready),
        .bist_pass_i(bist_pass),
        .bist_fail_i(bist_fail),
        .wdt_timeout_i(wdt_timeout),
        .glitch_detected_i(glitch_detected),
        .glitch_now_i(glitch_now),
        .aes_done_i(aes_done_i),
        .aes_result_i(aes_result_i),
        .aes_start_o(aes_start_o),
        .bist_start_o(bist_start_o),
        .wdt_enable_o(wdt_enable_o),
        .aes_key_o(aes_key_o),
        .aes_plaintext_o(aes_plaintext_o)
    );

    // ---- safety_assertions instance (real signals connected) ----
    safety_assertions u_assert (
        .clk(clk), .rst(rst),
        .bist_fail(bist_fail),
        .bist_done(bist_done),
        .wdt_timeout(wdt_timeout),
        .glitch_detected(glitch_detected),
        .aes_start_o(aes_start_o),
        .trip_signal(trip_signal)
    );


    // Formal BMC ko force karo ki trace ki shuruaat mein reset ho
    // (warna registers arbitrary/unreachable initial state se shuru ho sakte hain)
    always @(posedge clk) begin
        if ($initstate)
            assume (rst);
    end
endmodule
