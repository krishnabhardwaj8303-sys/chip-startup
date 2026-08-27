// Arbiter PUF Cell — behavioral randomness proxy
//
// FIX v4: v1/v2/v3 all failed for the SAME underlying reason, which
// wasn't identified until this version: every operation used so far
// (XOR, shift, rotate, concatenation) is LINEAR over GF(2). For any
// GF(2)-linear function f, f(seed XOR challenge_bit) = f(seed) XOR
// f(challenge_bit_as_a_unit_vector) - meaning challenge_bit's effect
// on the mixed output is ALWAYS a fixed, seed-INDEPENDENT XOR delta,
// no matter what constants or rotate amounts are chosen. This is why
// v1 gave 20/20 "always flips" and v3 gave 20/20 "never flips" -
// these weren't coincidences or constant-choice mistakes, they were
// the inevitable consequence of composing only linear operations.
// Diagnosed by testing (arbiter_puf_cell_diag2_tb.v across v1/v2/v3),
// not derived in advance - each prior version looked plausible until
// the sweep test exposed the deterministic pattern.
//
// FIX: introduces multiplication mod 2^32 (Murmur3-style avalanche
// finalizer: XOR-shift, multiply by odd constant, XOR-shift, multiply
// by a second odd constant, XOR-shift). Multiplication mod 2^32 is
// NOT linear over GF(2), so it breaks the fixed-delta property above -
// challenge_bit's effect on the final mixed value now genuinely
// depends on the rest of the seed, not just on challenge_bit alone.
// Re-verified empirically (not just re-derived on paper, given how
// wrong the earlier hand-analysis turned out to be) with the same
// diagnostic sweeps used to catch v1-v3's bugs.
//
// SCOPE NOTE (unchanged from v1-v3, still applies): real PUF entropy
// comes from TRANSISTOR-LEVEL physical delay variation that RTL/
// gate-level simulation cannot model at all - this is inherent to
// what a PUF is, not a bug specific to this project (see this repo's
// own SPICE-level Monte Carlo work on this exact cell for the real
// physical characterization). This fix is a BEHAVIORAL PROXY for
// simulation/testing purposes only. It does NOT deliver real per-chip
// hardware uniqueness - CELL_SEED is a compile-time RTL parameter, so
// every physical chip built from the same mask set would still get
// the identical value unless CHIP_SEED is somehow made to vary per
// die (a genuine production PUF must NOT depend on any baked-in RTL
// constant for its uniqueness - that defeats the entire point). True
// per-chip uniqueness can only be established via real fabrication +
// post-silicon characterization.
module arbiter_puf_cell #(
    parameter [31:0] CELL_SEED = 32'h00000000
) (
    input  wire        clk,
    input  wire        rst,
    input  wire        challenge_bit,
    input  wire        pulse_in,
    input  wire [31:0] chip_seed,
    output reg          puf_bit
);

    localparam IS_NEAR_TIE = (CELL_SEED[3:0] == 4'h0);

    reg [7:0] sample_count;
    reg       pulse_prev;
    wire      pulse_rise = pulse_in & ~pulse_prev;

    // Murmur3-style avalanche finalizer - nonlinear over GF(2) due to
    // multiplication mod 2^32, unlike pure XOR/shift/rotate.
    function [31:0] avalanche;
        input [31:0] x;
        reg   [31:0] h;
        begin
            h = x;
            h = h ^ (h >> 16);
            h = h * 32'h85ebca6b;
            h = h ^ (h >> 13);
            h = h * 32'hc2b2ae35;
            h = h ^ (h >> 16);
            avalanche = h;
        end
    endfunction

    wire [31:0] combined_seed = chip_seed ^ CELL_SEED ^
                                 {31'b0, challenge_bit} ^ {24'h0, noise_in};
    wire [7:0]  noise_in      = IS_NEAR_TIE ? sample_count : 8'h00;

    // Two DIFFERENT salts before the (nonlinear) avalanche mix, so
    // delay_a/delay_b are independently-derived rather than a
    // swappable pair, AND the nonlinearity means challenge_bit's
    // effect is seed-dependent rather than a fixed delta.
    wire [31:0] delay_a = avalanche(combined_seed ^ 32'h811C9DC5);
    wire [31:0] delay_b = avalanche(combined_seed ^ 32'h1000193F);

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            puf_bit      <= 1'b0;
            sample_count <= 8'h00;
            pulse_prev   <= 1'b0;
        end
        else begin
            pulse_prev <= pulse_in;
            if (pulse_in)
                puf_bit <= (delay_a > delay_b) ? 1'b1 : 1'b0;
            if (pulse_rise)
                sample_count <= sample_count + 8'h1;
        end
    end
endmodule
