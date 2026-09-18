// Power-on-Reset (POR) Circuit — behavioral digital model
// Real silicon POR circuits use an RC (resistor-capacitor) delay: on
// power-up, the capacitor is uncharged, holding an internal node low
// (or high, depending on polarity) which drives reset asserted; as the
// capacitor charges through the resistor, the node crosses a threshold
// and reset releases - all without any external reset signal, purely
// from the act of power arriving.
//
// SCOPE NOTE: this is a BEHAVIORAL/DIGITAL abstraction. RC charge time
// is an analog, continuous-time phenomenon dependent on process
// variation, temperature, and supply ramp rate; it cannot be
// physically modeled in digital RTL. This module instead uses a
// counter clocked by the (already-generated) system clock to hold
// reset asserted for a fixed number of cycles after power-up,
// producing a deterministic, simulation-friendly equivalent. A real
// POR macro (an analog RC or bandgap-referenced circuit in the target
// PDK) must replace this model at the physical-implementation stage;
// it must also correctly handle the fact that on real silicon, no
// clock is guaranteed to be running before POR release (this model
// assumes clk is already toggling, which is a simplification suitable
// for post-power-good digital reset sequencing, not the very first
// instant of power arrival).
module por_circuit #(
    parameter POR_CYCLES = 8   // simulation-friendly hold duration;
                                 // real silicon RC delay is process/
                                 // temperature-dependent, characterized
                                 // post-fabrication
)(
    input  wire clk,
    output reg  por_reset   // 1 = held in reset, 0 = released
);
    reg [31:0] por_counter;

    // NOTE: intentionally has NO reset input of its own - this IS the
    // reset source. It free-runs from whatever state its registers
    // power up in; on real silicon, flip-flops have a defined power-up
    // state for exactly this reason (a POR cell's own initial state
    // must be guaranteed by construction, not by another reset signal).
    initial begin
        por_reset   = 1'b1;
        por_counter = 32'd0;
    end

    always @(posedge clk) begin
        if (por_counter < POR_CYCLES) begin
            por_counter <= por_counter + 1'b1;
            por_reset   <= 1'b1;
        end
        else begin
            por_reset <= 1'b0;
        end
    end
endmodule
