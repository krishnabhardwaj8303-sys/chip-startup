// Array of 32 Arbiter PUF cells
// Takes a 32-bit challenge, produces a 32-bit response
//
// UPDATED for arbiter_puf_cell.v's behavioral randomness proxy (see
// that file's header for the full history of why the original cell
// always output 0, and why 3 successive mixing-function attempts
// (v1-v3) still failed before landing on v4's nonlinear avalanche mix).
//
// Each of the 32 cells gets a distinct compile-time CELL_SEED (proxy
// for fixed per-location manufacturing variation). CHIP_SEED is a
// single array-level parameter, threaded down to every cell, that
// varies per "chip instance" in simulation/testbenches - this is what
// makes two different puf_array instantiations (or the same
// instantiation re-parameterized) produce different responses to the
// same challenge, standing in for real chip-to-chip silicon variation.
//
// SCOPE NOTE (see arbiter_puf_cell.v for full detail): CHIP_SEED being
// an RTL parameter means it is NOT a source of real per-chip hardware
// uniqueness on its own - every physical chip from the same mask set
// would get the same value unless something makes CHIP_SEED vary per
// physical die (outside RTL's ability to guarantee). This is a
// simulation/testing proxy, not a production uniqueness mechanism.
module puf_array #(
    parameter [31:0] CHIP_SEED = 32'h00000000
) (
    input  wire        clk,
    input  wire        rst,
    input  wire         pulse_in,
    input  wire [31:0]  challenge,
    output wire [31:0]  response
);
    genvar i;
    generate
        for (i = 0; i < 32; i = i + 1) begin : puf_cells
            arbiter_puf_cell #(
                // Distinct per-cell seed: a fixed, arbitrary-looking
                // constant derived from the cell index, spread out via
                // multiplication (mod 2^32) so adjacent cells don't
                // get trivially related seeds.
                .CELL_SEED(32'h9E3779B9 * (i + 1) + 32'hC001C0DE)
            ) u_cell (
                .clk(clk),
                .rst(rst),
                .challenge_bit(challenge[i]),
                .pulse_in(pulse_in),
                .chip_seed(CHIP_SEED),
                .puf_bit(response[i])
            );
        end
    endgenerate
endmodule
