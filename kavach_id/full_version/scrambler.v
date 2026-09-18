// Lightweight scrambler: XOR + bit-rotation based obfuscation
// Combines raw PUF response with challenge to prevent direct PUF leakage
module scrambler (
    input  wire [31:0] challenge,
    input  wire [31:0] raw_response,
    output wire [31:0] scrambled_response
);
    wire [31:0] xored;
    wire [31:0] rotated;

    assign xored   = raw_response ^ challenge;
    // Rotate left by 7 bits (simple diffusion)
    assign rotated = {xored[24:0], xored[31:25]};

    assign scrambled_response = rotated ^ {challenge[15:0], challenge[31:16]};
endmodule
