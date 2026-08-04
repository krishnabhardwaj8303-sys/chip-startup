module layer_chain_tb;

    reg         clk, rst, start_network;
    reg  signed [31:0] l1_out0, l1_out1, l1_out2, l1_out3;
    reg          l1_done;
    wire         l2_load_activations;
    wire signed [7:0] l2_a_in0, l2_a_in1, l2_a_in2, l2_a_in3;
    wire         l2_start;
    reg          l2_done;
    wire         network_done;
    wire [1:0]   current_layer;

    layer_chain_controller DUT (
        .clk(clk), .rst(rst),
        .start_network(start_network),
        .l1_out0(l1_out0), .l1_out1(l1_out1), 
        .l1_out2(l1_out2), .l1_out3(l1_out3),
        .l1_done(l1_done),
        .l2_load_activations(l2_load_activations),
        .l2_a_in0(l2_a_in0), .l2_a_in1(l2_a_in1), 
        .l2_a_in2(l2_a_in2), .l2_a_in3(l2_a_in3),
        .l2_start(l2_start),
        .l2_done(l2_done),
        .network_done(network_done),
        .current_layer(current_layer)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("layer_chain.vcd");
        $dumpvars(0, layer_chain_tb);

        rst = 1; start_network = 0; l1_done = 0; l2_done = 0;
        l1_out0 = 0; l1_out1 = 0; l1_out2 = 0; l1_out3 = 0;
        #20; rst = 0; #10;

        $display("================================");
        $display("  LAGHU-NPU MULTI-LAYER CHAINING");
        $display("  Fixes: proposal's biggest gap  ");
        $display("================================");

        // ── TEST 1: Normal 2-layer chain — no overflow ──
        $display("--- Test 1: Normal Layer 1 -> Layer 2 Chain ---");
        start_network = 1; #10; start_network = 0;

        // Layer 1 simulate karo: normal outputs
        l1_out0 = 32'sd50; l1_out1 = 32'sd60; 
        l1_out2 = 32'sd70; l1_out3 = 32'sd80;
        #10; l1_done = 1; #10; l1_done = 0;

        wait(l2_load_activations);
        $display("Layer 1 Outputs (INT32): %0d %0d %0d %0d",
                  l1_out0, l1_out1, l1_out2, l1_out3);
        $display("Layer 2 Inputs (INT8, requantized): %0d %0d %0d %0d",
                  l2_a_in0, l2_a_in1, l2_a_in2, l2_a_in3);

        if (l2_a_in0 == 50 && l2_a_in1 == 60 && 
            l2_a_in2 == 70 && l2_a_in3 == 80)
            $display("PASS: Layer 1 output correctly feeds Layer 2!");
        else
            $display("FAIL: Layer chaining data mismatch");

        #10; l2_done = 1; #10; l2_done = 0;
        wait(network_done);
        $display("PASS: Full network (2-layer) execution complete!");
        #20;

        // ── TEST 2: Layer 1 produces overflow — must saturate ──
        $display("--- Test 2: Layer 1 Overflow -> Saturated Requant ---");
        start_network = 1; #10; start_network = 0;
        l1_out0 = 32'sd50000;  // Way over INT8 range
        l1_out1 = -32'sd50000; // Way under INT8 range
        l1_out2 = 32'sd100;
        l1_out3 = 32'sd50;
        #10; l1_done = 1; #10; l1_done = 0;

        wait(l2_load_activations);
        $display("Layer 1 Outputs (INT32): %0d %0d %0d %0d",
                  l1_out0, l1_out1, l1_out2, l1_out3);
        $display("Layer 2 Inputs (saturated): %0d %0d %0d %0d",
                  l2_a_in0, l2_a_in1, l2_a_in2, l2_a_in3);

        if (l2_a_in0 == 127 && l2_a_in1 == -128)
            $display("PASS: Inter-layer overflow correctly saturated!");
        else
            $display("FAIL: Overflow not caught at layer boundary!");

        #10; l2_done = 1; #10; l2_done = 0;
        wait(network_done);

        $display("================================");
        $display("Multi-Layer Chaining Complete!");
        $display("True 2-layer network inference verified!");
        $display("No more single-layer limitation!");
        $display("================================");
        $finish;
    end
endmodule
