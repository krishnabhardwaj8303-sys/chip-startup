// On-Chip Ring Oscillator — behavioral digital model
// Real silicon ring oscillators are an ODD number of inverters
// connected in a feedback loop; the propagation delay through each
// inverter (a function of process, voltage, temperature) sets the
// oscillation period, with no external crystal required.
//
// SCOPE NOTE: this is a BEHAVIORAL/DIGITAL abstraction, not a real
// analog ring oscillator. Verilog gate/wire delays are not physically
// meaningful pre-synthesis. Real silicon ring-oscillator frequency
// (and its process/voltage/temperature variation) can only be
// characterized post-fabrication; a physical ring-oscillator macro
// (odd-stage inverter chain in the target PDK) must replace this
// model at the physical-implementation stage.
//
// ENGINEERING NOTE: an earlier version of this module used a
// self-triggering "always @(clk_out or enable) #1 clk_out = ~clk_out"
// idiom, intended to model free-running oscillation independent of
// any host clock. Testing found this pattern oscillates only ONCE in
// Icarus Verilog (toggles from 0 to 1, then never re-triggers) rather
// than continuously - a known reliability issue with self-referencing
// delayed always-blocks in some simulators. Replaced with the
// standard, reliable "initial ... forever #delay" clock-generation
// idiom used throughout the rest of this codebase (see uart_tx.v/
// uart_rx.v's own clock-relative timing for the same general pattern).
module ring_oscillator #(
    parameter HALF_PERIOD = 1  // simulation-friendly half-period;
                                 // real silicon frequency is process-
                                 // dependent, only characterizable post-fab
)(
    input  wire enable,
    output reg  clk_out
);
    initial clk_out = 1'b0;

    always begin
        if (enable) begin
            #HALF_PERIOD;
            clk_out = ~clk_out;
        end
        else begin
            clk_out = 1'b0;
            @(posedge enable); // block until re-enabled, avoids busy-looping
        end
    end
endmodule
