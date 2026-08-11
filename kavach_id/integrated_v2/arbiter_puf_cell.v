// Single Arbiter PUF cell
// Uses two parallel delay paths with switchable routing (based on challenge bit)
// Manufacturing variation determines which path is faster -> unique 1-bit output
module arbiter_puf_cell (
    input  wire clk,
    input  wire rst,
    input  wire challenge_bit,   // Selects routing of the delay paths
    input  wire pulse_in,        // Trigger pulse that races through both paths
    output reg  puf_bit          // Output: which path won the race
);
    // Two delay path signals (implemented as buffer chains)
    wire path_a, path_b;
    wire mux_a, mux_b;

    // Switch routing based on challenge bit (creates different path combos per challenge)
    assign mux_a = challenge_bit ? pulse_in : path_a;
    assign mux_b = challenge_bit ? path_b   : pulse_in;

    // Delay chains (each buffer adds tiny, process-variation-dependent delay)
    buf (path_a, mux_a);
    buf (path_b, mux_b);

    // Arbiter: a simple SR-latch-like race detector
    // First path to transition sets the output
    always @(posedge clk or posedge rst) begin
        if (rst)
            puf_bit <= 1'b0;
        else
            puf_bit <= (path_a && !path_b) ? 1'b1 :
                       (path_b && !path_a) ? 1'b0 : puf_bit;
    end
endmodule
