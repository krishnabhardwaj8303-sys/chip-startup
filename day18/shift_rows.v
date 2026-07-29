module shift_rows(
    input  wire [127:0] in,
    output wire [127:0] out
);
    // AES state = 4x4 bytes matrix
    // Row 0: no shift
    // Row 1: shift left 1
    // Row 2: shift left 2
    // Row 3: shift left 3

    assign out[127:120] = in[127:120]; // Row0 B0
    assign out[119:112] = in[119:112]; // Row0 B1
    assign out[111:104] = in[111:104]; // Row0 B2
    assign out[103: 96] = in[103: 96]; // Row0 B3

    assign out[95:88]   = in[87:80];   // Row1 shift 1
    assign out[87:80]   = in[79:72];
    assign out[79:72]   = in[71:64];
    assign out[71:64]   = in[95:88];

    assign out[63:56]   = in[47:40];   // Row2 shift 2
    assign out[55:48]   = in[39:32];
    assign out[47:40]   = in[63:56];
    assign out[39:32]   = in[55:48];

    assign out[31:24]   = in[16:8];    // Row3 shift 3
    assign out[23:16]   = in[7:0];
    assign out[15:8]    = in[31:24];
    assign out[7:0]     = in[23:16];

endmodule
