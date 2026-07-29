module aes_round(
    input  wire [127:0] state,
    input  wire [127:0] round_key,
    output wire [127:0] out
);
    wire [127:0] after_sub;
    wire [127:0] after_shift;
    wire [127:0] after_mix;

    sub_bytes   SB  (.in(state),       .out(after_sub));
    shift_rows  SR  (.in(after_sub),   .out(after_shift));
    mix_columns MC  (.in(after_shift), .out(after_mix));
    add_round_key ARK (.state(after_mix),
                       .round_key(round_key),
                       .out(out));
endmodule
