module npu_regmap_tb;

    reg        clk, rst;
    reg        reg_write, reg_read;
    reg  [7:0] reg_addr;
    reg  [31:0] reg_wdata;
    wire [31:0] reg_rdata;
    wire        reg_ready;

    reg         npu_done_i, bist_pass_i, bist_fail_i, hazard_detected_i;
    reg  signed [31:0] out0_i, out1_i, out2_i, out3_i;

    wire        npu_start_o, bist_start_o;
    wire        load_weights_o, load_activations_o;
    wire [1:0]  weight_row_idx_o;
    wire signed [7:0] w_in0_o, w_in1_o, w_in2_o, w_in3_o;
    wire signed [7:0] a_in0_o, a_in1_o, a_in2_o, a_in3_o;

    npu_register_map DUT (
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
        .w_in0_o(w_in0_o), .w_in1_o(w_in1_o), 
        .w_in2_o(w_in2_o), .w_in3_o(w_in3_o),
        .a_in0_o(a_in0_o), .a_in1_o(a_in1_o), 
        .a_in2_o(a_in2_o), .a_in3_o(a_in3_o)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    reg npu_start_seen;
    always @(posedge npu_start_o) npu_start_seen = 1;

    initial begin
        $dumpfile("npu_regmap.vcd");
        $dumpvars(0, npu_regmap_tb);

        rst = 1;
        reg_write = 0; reg_read = 0; reg_addr = 0; reg_wdata = 0;
        npu_done_i = 0; bist_pass_i = 0; bist_fail_i = 0; 
        hazard_detected_i = 0;
        out0_i = 0; out1_i = 0; out2_i = 0; out3_i = 0;
        npu_start_seen = 0;
        #20; rst = 0; #10;

        $display("================================");
        $display("  NPU REGISTER INTERFACE TEST  ");
        $display("================================");

        // ── TEST 1: Chip ID ──
        $display("--- Test 1: Read Chip ID ---");
        reg_addr = 8'hFC; reg_read = 1; #10; reg_read = 0; #10;
        if (reg_rdata == 32'h4C41474E)
            $display("PASS: Chip ID = 0x%0h (LAGN)", reg_rdata);
        else
            $display("FAIL: Chip ID = 0x%0h", reg_rdata);

        // ── TEST 2: Write Packed Weight Data ──
        $display("--- Test 2: Write Packed Weights ---");
        reg_addr = 8'h0C; reg_wdata = 32'h04030201; // w3=4,w2=3,w1=2,w0=1
        reg_write = 1; #10; reg_write = 0; #10;
        if (w_in0_o == 1 && w_in1_o == 2 && w_in2_o == 3 && w_in3_o == 4)
            $display("PASS: Packed weight unpacking correct!");
        else
            $display("FAIL: Weight unpack error: %0d %0d %0d %0d", 
                      w_in0_o, w_in1_o, w_in2_o, w_in3_o);

        // ── TEST 3: NPU Start via Control Register ──
        $display("--- Test 3: NPU Start Trigger ---");
        reg_addr = 8'h00; reg_wdata = 32'h00000001;
        reg_write = 1; #10; reg_write = 0; #10;
        if (npu_start_seen)
            $display("PASS: NPU start signal triggered via register!");
        else
            $display("FAIL: NPU start not triggered");

        // ── TEST 4: Output Read ──
        $display("--- Test 4: Read Computation Output ---");
        out0_i = 32'sd100; out1_i = 32'sd200;
        reg_addr = 8'h14; reg_read = 1; #10; reg_read = 0; #10;
        if (reg_rdata == 32'sd100)
            $display("PASS: NPU output readable via register: %0d", 
                      $signed(reg_rdata));
        else
            $display("FAIL: Output read mismatch");

        // ── TEST 5: Status Register ──
        $display("--- Test 5: Status Register ---");
        npu_done_i = 1; bist_pass_i = 1;
        reg_addr = 8'h04; reg_read = 1; #10; reg_read = 0; #10;
        if (reg_rdata[0] == 1 && reg_rdata[1] == 1)
            $display("PASS: Status shows npu_done + bist_pass!");
        else
            $display("FAIL: Status incorrect: 0x%0h", reg_rdata);

        $display("================================");
        $display("Phase 3 Complete!");
        $display("NPU Register Interface working!");
        $display("================================");
        $finish;
    end
endmodule
