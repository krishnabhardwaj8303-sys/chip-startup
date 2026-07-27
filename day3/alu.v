module alu(
    input  wire [3:0] a,
    input  wire [3:0] b,
    input  wire [2:0] op,
    output reg  [4:0] result,
    output reg        zero
);

    // Operations
    parameter ADD = 3'b000;
    parameter SUB = 3'b001;
    parameter AND = 3'b010;
    parameter OR  = 3'b011;
    parameter XOR = 3'b100;
    parameter NOT = 3'b101;
    parameter SHL = 3'b110;
    parameter SHR = 3'b111;

    always @(*) begin
        case (op)
            ADD: result = a + b;
            SUB: result = a - b;
            AND: result = a & b;
            OR:  result = a | b;
            XOR: result = a ^ b;
            NOT: result = ~a;
            SHL: result = a << 1;
            SHR: result = a >> 1;
            default: result = 0;
        endcase
        zero = (result == 0) ? 1 : 0;
    end

endmodule
