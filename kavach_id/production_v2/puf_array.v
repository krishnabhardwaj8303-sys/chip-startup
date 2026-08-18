// Array of 32 Arbiter PUF cells
// Takes a 32-bit challenge, produces a 32-bit unique response
module puf_array (
    input  wire        clk,
    input  wire        rst,
    input  wire         pulse_in,
    input  wire [31:0]  challenge,
    output wire [31:0]  response
);
    genvar i;
    generate
        for (i = 0; i < 32; i = i + 1) begin : puf_cells
            arbiter_puf_cell u_cell (
                .clk(clk),
                .rst(rst),
                .challenge_bit(challenge[i]),
                .pulse_in(pulse_in),
                .puf_bit(response[i])
            );
        end
    endgenerate
endmodule
