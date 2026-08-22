// Per-Chip Key Storage — write-once behavioral model
// FIX: previously, encrypted_channel.v's shared_key was hardcoded to
// 32'hDEADBEEF directly in kavach_id_top.v, with a comment stating
// "would come from PUF-derived secret" that was never implemented.
// Every chip built from this design would share the IDENTICAL key,
// making the encryption uniform and breakable across the entire
// product line (compromise one chip, compromise all of them).
//
// This module provides a factory-programmable, write-once key
// register: a programming interface writes the key exactly once
// (typically during manufacturing test/provisioning), after which
// key_locked permanently blocks any further writes until reset.
//
// SCOPE NOTE: this is a BEHAVIORAL model of one-time-programmability
// using an ordinary register + lock bit. It is NOT equivalent to a
// real OTP/e-fuse/anti-fuse hardware macro, which is a fab-specific
// hardened IP block provided by the PDK and physically cannot be
// rewritten even across power cycles (this RTL model's "lock" is only
// enforced while powered and not reset). Real tape-out will require
// integrating the SKY130 (or target process) OTP/e-fuse macro in
// place of this behavioral register at the physical-implementation
// stage.
module key_storage (
    input  wire        clk,
    input  wire        rst,
    input  wire        prog_enable,   // pulse: attempt to program key
    input  wire [31:0] prog_key_in,   // key value to program
    output reg  [31:0] chip_key,      // the (possibly still-unprogrammed) key
    output reg          key_locked     // 1 once programmed; blocks further writes
);
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            chip_key   <= 32'h0;
            key_locked <= 1'b0;
        end
        else begin
            if (prog_enable && !key_locked) begin
                chip_key   <= prog_key_in;
                key_locked <= 1'b1;
            end
        end
    end
endmodule
