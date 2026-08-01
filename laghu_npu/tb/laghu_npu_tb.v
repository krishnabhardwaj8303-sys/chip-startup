`timescale 1ns/1ps

module laghu_npu_tb;

    reg clk, rst;
    reg start, load_weights, load_activations;
    reg [1:0] weight_row_idx;
    reg signed [7:0] w_in0, w_in1, w_in2, w_in3;
    reg signed [7:0] a_in0, a_in1, a_in2, a_in3;
    wire done;
    wire signed [31:0] out0, out1, out2, out3;

    laghu_npu_top uut (
        .clk(clk), .rst(rst),
        .start(start), .done(done),
        .load_weights(load_weights), .weight_row_idx(weight_row_idx),
        .w_in0(w_in0), .w_in1(w_in1), .w_in2(w_in2), .w_in3(w_in3),
        .load_activations(load_activations),
        .a_in0(a_in0), .a_in1(a_in1), .a_in2(a_in2), .a_in3(a_in3),
        .out0(out0), .out1(out1), .out2(out2), .out3(out3)
    );

    // Clock generation: 10ns period
    always #5 clk = ~clk;

    initial begin
        $dumpfile("laghu_npu.vcd");
        $dumpvars(0, laghu_npu_tb);

        clk = 0;
        rst = 1;
        start = 0;
        load_weights = 0;
        load_activations = 0;
        weight_row_idx = 0;
        w_in0 = 0; w_in1 = 0; w_in2 = 0; w_in3 = 0;
        a_in0 = 0; a_in1 = 0; a_in2 = 0; a_in3 = 0;

        #20 rst = 0;

        // Load weight matrix (identity-like for easy verification)
        // Row 0: [2, 0, 0, 0]
        @(posedge clk);
        load_weights = 1; weight_row_idx = 0;
        w_in0 = 2; w_in1 = 0; w_in2 = 0; w_in3 = 0;
        @(posedge clk);
        // Row 1: [0, 3, 0, 0]
        weight_row_idx = 1;
        w_in0 = 0; w_in1 = 3; w_in2 = 0; w_in3 = 0;
        @(posedge clk);
        // Row 2: [0, 0, 4, 0]
        weight_row_idx = 2;
        w_in0 = 0; w_in1 = 0; w_in2 = 4; w_in3 = 0;
        @(posedge clk);
        // Row 3: [0, 0, 0, 5]
        weight_row_idx = 3;
        w_in0 = 0; w_in1 = 0; w_in2 = 0; w_in3 = 5;
        @(posedge clk);
        load_weights = 0;

        // Load activation vector [10, 10, 10, 10]
        load_activations = 1;
        a_in0 = 10; a_in1 = 10; a_in2 = 10; a_in3 = 10;
        @(posedge clk);
        load_activations = 0;

        // Start computation
        @(posedge clk);
        start = 1;
        @(posedge clk);
        start = 0;

        // Wait for done
        wait(done == 1);
        @(posedge clk);

        $display("========================================");
        $display("Laghu-NPU Test Results");
        $display("Expected: out0=20, out1=30, out2=40, out3=50");
        $display("Got:      out0=%0d, out1=%0d, out2=%0d, out3=%0d", out0, out1, out2, out3);
        $display("========================================");

        if (out0 == 20 && out1 == 30 && out2 == 40 && out3 == 50)
            $display("TEST PASSED!");
        else
            $display("TEST FAILED!");

        #20 $finish;
    end

endmodule
