// Reset Synchronizer: async assert, synchronous de-assert.
// FIX (hardening item): raw external reset was fed directly into 17
// "posedge clk or posedge rst" always-blocks across the design. This
// is safe for reset ASSERTION (must react immediately, async is
// correct there) but unsafe for reset DE-ASSERTION - if rst releases
// too close to a clock edge, different flip-flops across the chip can
// sample the release on different cycles, leaving the chip in an
// inconsistent, undefined power-up state (a classic "reset recovery/
// removal" timing hazard that never shows up in RTL simulation, only
// on real silicon). This module lets rst_in assert the output
// immediately (async), but only releases it two clock cycles after
// rst_in goes low, guaranteeing every flop in the design sees release
// on the same, single clock edge.
module reset_sync (
    input  wire clk,
    input  wire rst_in,     // raw, possibly-asynchronous external reset
    output wire rst_out     // synchronized reset for internal use
);
    reg stage1, stage2;

    always @(posedge clk or posedge rst_in) begin
        if (rst_in) begin
            stage1 <= 1'b1;
            stage2 <= 1'b1;
        end
        else begin
            stage1 <= 1'b0;
            stage2 <= stage1;
        end
    end

    assign rst_out = stage2;
endmodule
