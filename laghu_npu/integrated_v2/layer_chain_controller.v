module layer_chain_controller(
    input  wire        clk,
    input  wire        rst,
    input  wire        start_network,      // Poora network chalao
    // Layer 1 outputs (4 values, INT32)
    input  wire signed [31:0] l1_out0, l1_out1, l1_out2, l1_out3,
    input  wire         l1_done,
    // Layer 2 control (yeh module Layer 2 ko drive karega)
    output reg           l2_load_activations,
    output reg  signed [7:0] l2_a_in0, l2_a_in1, l2_a_in2, l2_a_in3,
    output reg           l2_start,
    input  wire          l2_done,
    // Overall network status
    output reg           network_done,
    output reg  [1:0]    current_layer  // Debug: kaunsi layer chal rahi hai
);
    // Yeh proposal ka sabse bada gap fix karta hai:
    // "Multi-layer chaining so the output of one layer 
    //  feeds the next (true network inference, not a 
    //  single layer)"
    //
    // Layer 1 ka INT32 output -> requantize (saturate to INT8) 
    // -> Layer 2 ka activation input. Yeh EXACT wahi cheez hai 
    // jo ek real neural network ke layers ke beech hoti hai.

    parameter IDLE       = 3'd0;
    parameter WAIT_L1    = 3'd1;
    parameter REQUANT    = 3'd2;
    parameter LOAD_L2    = 3'd3;
    parameter WAIT_L2    = 3'd4;
    parameter DONE       = 3'd5;

    reg [2:0] state;

    // Saturating requantize function (reuse Phase 1 logic 
    // — INT32 accumulator -> INT8 for next layer)
    function signed [7:0] saturate;
        input signed [31:0] val;
        begin
            if (val > 32'sd127)
                saturate = 8'sd127;
            else if (val < -32'sd128)
                saturate = -8'sd128;
            else
                saturate = val[7:0];
        end
    endfunction

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state                <= IDLE;
            l2_load_activations  <= 0;
            l2_start             <= 0;
            network_done         <= 0;
            current_layer        <= 0;
            l2_a_in0 <= 0; l2_a_in1 <= 0; l2_a_in2 <= 0; l2_a_in3 <= 0;
        end
        else begin
            l2_load_activations <= 0; // Pulse
            l2_start            <= 0; // Pulse

            case (state)
                IDLE: begin
                    network_done  <= 0;
                    current_layer <= 2'd1;
                    if (start_network)
                        state <= WAIT_L1;
                end

                // Layer 1 ke compute complete hone ka wait karo
                WAIT_L1: begin
                    if (l1_done)
                        state <= REQUANT;
                end

                // CRITICAL STEP: Layer 1 ke INT32 outputs ko 
                // saturating requantize karke INT8 mein convert 
                // karo — yehi hai "layer boundary" jahan bina 
                // saturation ke silent overflow bug aata hai
                REQUANT: begin
                    l2_a_in0 <= saturate(l1_out0);
                    l2_a_in1 <= saturate(l1_out1);
                    l2_a_in2 <= saturate(l1_out2);
                    l2_a_in3 <= saturate(l1_out3);
                    state    <= LOAD_L2;
                end

                // Layer 2 mein requantized values load karo
                LOAD_L2: begin
                    l2_load_activations <= 1;
                    current_layer       <= 2'd2;
                    state                <= WAIT_L2;
                end

                WAIT_L2: begin
                    l2_start <= 1;
                    if (l2_done)
                        state <= DONE;
                end

                DONE: begin
                    network_done <= 1;
                    state        <= IDLE;
                end
            endcase
        end
    end
endmodule
