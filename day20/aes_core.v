module aes_core(
    input  wire [127:0] plaintext,
    input  wire [127:0] key,
    output wire [127:0] ciphertext
);
    // Round keys
    wire [127:0] rk0,rk1,rk2,rk3,rk4,rk5;
    wire [127:0] rk6,rk7,rk8,rk9,rk10;

    key_schedule KS (
        .key(key),
        .rk0(rk0),   .rk1(rk1),
        .rk2(rk2),   .rk3(rk3),
        .rk4(rk4),   .rk5(rk5),
        .rk6(rk6),   .rk7(rk7),
        .rk8(rk8),   .rk9(rk9),
        .rk10(rk10)
    );

    // Initial AddRoundKey
    wire [127:0] s0;
    add_round_key ARK0 (
        .state(plaintext),
        .round_key(rk0),
        .out(s0)
    );

    // Rounds 1-9
    wire [127:0] s1,s2,s3,s4,s5,s6,s7,s8,s9;

    aes_round R1  (.state(s0), .round_key(rk1),  .out(s1));
    aes_round R2  (.state(s1), .round_key(rk2),  .out(s2));
    aes_round R3  (.state(s2), .round_key(rk3),  .out(s3));
    aes_round R4  (.state(s3), .round_key(rk4),  .out(s4));
    aes_round R5  (.state(s4), .round_key(rk5),  .out(s5));
    aes_round R6  (.state(s5), .round_key(rk6),  .out(s6));
    aes_round R7  (.state(s6), .round_key(rk7),  .out(s7));
    aes_round R8  (.state(s7), .round_key(rk8),  .out(s8));
    aes_round R9  (.state(s8), .round_key(rk9),  .out(s9));

    // Final Round (no MixColumns)
    aes_final_round R10 (
        .state(s9),
        .round_key(rk10),
        .out(ciphertext)
    );

endmodule
