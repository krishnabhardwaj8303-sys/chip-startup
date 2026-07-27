module imem(
    input  wire [2:0] addr,
    output reg  [7:0] instruction
);
    // 8 instructions ka program stored hai
    always @(*) begin
        case (addr)
            3'd0: instruction = 8'b00_000_001; // ADD R0+R1
            3'd1: instruction = 8'b00_010_011; // ADD R2+R3
            3'd2: instruction = 8'b01_000_010; // SUB R0-R2
            3'd3: instruction = 8'b10_001_011; // AND R1&R3
            3'd4: instruction = 8'b11_000_001; // OR  R0|R1
            3'd5: instruction = 8'b00_100_101; // ADD R4+R5
            3'd6: instruction = 8'b01_110_111; // SUB R6-R7
            3'd7: instruction = 8'b10_000_001; // AND R0&R1
            default: instruction = 8'b0;
        endcase
    end
endmodule
