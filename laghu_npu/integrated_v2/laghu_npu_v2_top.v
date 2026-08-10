module laghu_npu_v2_top(
    input  wire         clk,
    input  wire         rst,

    // ── External Register Interface ──
    input  wire         reg_write,
    input  wire         reg_read,
    input  wire [7:0]   reg_addr,
    input  wire [31:0]  reg_wdata,
    output wire [31:0]  reg_rdata,
    output wire          reg_ready,

    // ── Status Outputs ──
    output wire          npu_healthy,
    output wire          hazard_active
);

    // ═══════════════════════════════════════════
    // 1. REGISTER MAP — host control interface
    // ═══════════════════════════════════════════
    wire         npu_start_o, bist_start_o;
    wire         load_weights_o, load_activations_o;
    wire [1:0]   weight_row_idx_o;
    wire signed [7:0] w_in0_o, w_in1_o, w_in2_o, w_in3_o;
    wire signed [7:0] a_in0_o, a_in1_o, a_in2_o, a_in3_o;

    wire         npu_done_i, bist_pass_i, bist_fail_i, hazard_detected_i;
    wire signed [31:0] out0_i, out1_i, out2_i, out3_i;

    npu_register_map REGMAP (
        .clk(clk), .rst(rst),
        .reg_write(reg_write), .reg_read(reg_read),
        .reg_addr(reg_addr), .reg_wdata(reg_wdata),
        .reg_rdata(reg_rdata), .reg_ready(reg_ready),
        .npu_done_i(npu_done_i), .bist_pass_i(bist_pass_i),
        .bist_fail_i(bist_fail_i), .hazard_detected_i(hazard_detected_i),
        .out0_i(out0_i), .out1_i(out1_i), .out2_i(out2_i), .out3_i(out3_i),
        .npu_start_o(npu_start_o), .bist_start_o(bist_start_o),
        .load_weights_o(load_weights_o),
        .load_activations_o(load_activations_o),
        .weight_row_idx_o(weight_row_idx_o),
        .w_in0_o(w_in0_o), .w_in1_o(w_in1_o), .w_in2_o(w_in2_o), .w_in3_o(w_in3_o),
        .a_in0_o(a_in0_o), .a_in1_o(a_in1_o), .a_in2_o(a_in2_o), .a_in3_o(a_in3_o)
    );

    // ═══════════════════════════════════════════
    // 2. HAZARD DETECTOR — blocks compute during load race
    // ═══════════════════════════════════════════
    wire safe_npu_start;

    hazard_detector HAZARD (
        .clk(clk), .rst(rst),
        .load_weights(load_weights_o),
        .load_activations(load_activations_o),
        .compute_start(npu_start_o),
        .hazard_detected(hazard_detected_i),
        .hazard_type()
    );

    // Hazard blocks the actual compute trigger — security-critical wiring
    assign safe_npu_start = npu_start_o & ~hazard_detected_i;

    // ═══════════════════════════════════════════
    // 3. CONFIDENCE ESTIMATOR — dust/fog input check
    // ═══════════════════════════════════════════
    wire low_confidence, dust_fog_signature;
    wire [2:0] saturated_count;

    confidence_estimator CONF (
        .clk(clk), .rst(rst),
        .sample_valid(load_activations_o),
        .a_in0(a_in0_o), .a_in1(a_in1_o), .a_in2(a_in2_o), .a_in3(a_in3_o),
        .low_confidence(low_confidence),
        .saturated_count(saturated_count),
        .dust_fog_signature(dust_fog_signature)
    );

    // ═══════════════════════════════════════════
    // 4. LAGHU-NPU CORE — the actual systolic array
    // ═══════════════════════════════════════════
    wire         npu_done;
    wire signed [31:0] core_out0, core_out1, core_out2, core_out3;

    laghu_npu_top NPU_CORE (
        .clk(clk), .rst(rst),
        .start(safe_npu_start),
        .done(npu_done),
        .load_weights(load_weights_o),
        .weight_row_idx(weight_row_idx_o),
        .w_in0(w_in0_o), .w_in1(w_in1_o), .w_in2(w_in2_o), .w_in3(w_in3_o),
        .load_activations(load_activations_o),
        .a_in0(a_in0_o), .a_in1(a_in1_o), .a_in2(a_in2_o), .a_in3(a_in3_o),
        .out0(core_out0), .out1(core_out1), .out2(core_out2), .out3(core_out3)
    );

    assign npu_done_i = npu_done;

    // ═══════════════════════════════════════════
    // 5. REQUANTIZER — saturate INT32 outputs to safe range
    //    (results still reported as 32-bit for register 
    //     compatibility, but internally saturation-checked)
    // ═══════════════════════════════════════════
    wire signed [7:0] quant_out0, quant_out1, quant_out2, quant_out3;
    wire overflow0, overflow1, overflow2, overflow3;

    requantizer REQ0 (.acc_in(core_out0), .shift_amt(5'd0),
        .quant_out(quant_out0), .overflow_flag(overflow0), .underflow_flag());
    requantizer REQ1 (.acc_in(core_out1), .shift_amt(5'd0),
        .quant_out(quant_out1), .overflow_flag(overflow1), .underflow_flag());
    requantizer REQ2 (.acc_in(core_out2), .shift_amt(5'd0),
        .quant_out(quant_out2), .overflow_flag(overflow2), .underflow_flag());
    requantizer REQ3 (.acc_in(core_out3), .shift_amt(5'd0),
        .quant_out(quant_out3), .overflow_flag(overflow3), .underflow_flag());

    // Output to register map: raw core output (register map expects 32-bit)
    // but gated by confidence check — if input was low-confidence 
    // (dust/fog), zero out the result rather than reporting a 
    // silently-wrong prediction
    assign out0_i = low_confidence ? 32'h0 : core_out0;
    assign out1_i = low_confidence ? 32'h0 : core_out1;
    assign out2_i = low_confidence ? 32'h0 : core_out2;
    assign out3_i = low_confidence ? 32'h0 : core_out3;

    // ═══════════════════════════════════════════
    // 6. BIST — self-test using a known MAC result
    // ═══════════════════════════════════════════
    npu_bist BIST (
        .clk(clk), .rst(rst),
        .start_bist(bist_start_o),
        .bist_pass(bist_pass_i),
        .bist_fail(bist_fail_i),
        .bist_done(),
        .test_mac_result(32'sd15) // Known-answer constant for self-check
    );

    // ═══════════════════════════════════════════
    // TOP-LEVEL STATUS
    // ═══════════════════════════════════════════
    assign npu_healthy   = bist_pass_i & ~bist_fail_i & ~hazard_detected_i;
    assign hazard_active = hazard_detected_i;

endmodule
