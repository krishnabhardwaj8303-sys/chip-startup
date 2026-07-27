module cpu_v2(
    input  wire clk,
    input  wire rst,
    output wire [7:0] result,
    output wire [2:0] pc_out
);
    wire [7:0] instruction;
    wire [1:0] opcode  = instruction[7:6];
    wire [2:0] reg_a   = instruction[5:3];
    wire [2:0] reg_b   = instruction[2:0];

    wire [7:0] data_a, data_b;
    wire [4:0] alu_out;
    reg  [2:0] alu_op;

    // Program Counter
    pc PC (
        .clk(clk), .rst(rst),
        .halt(1'b0),
        .pc_out(pc_out)
    );

    // Instruction Memory
    imem IMEM (
        .addr(pc_out),
        .instruction(instruction)
    );

    // Register File
    reg_file RF (
        .clk(clk), .rst(rst),
        .wr_en(1'b1),
        .wr_addr(reg_a),
        .wr_data({3'b0, alu_out}),
        .rd_addr1(reg_a),
        .rd_addr2(reg_b),
        .rd_data1(data_a),
        .rd_data2(data_b)
    );

    // ALU
    alu ALU (
        .a(data_a[3:0]),
        .b(data_b[3:0]),
        .op(alu_op),
        .result(alu_out),
        .zero()
    );

    always @(*) begin
        case (opcode)
            2'b00: alu_op = 3'b000; // ADD
            2'b01: alu_op = 3'b001; // SUB
            2'b10: alu_op = 3'b010; // AND
            2'b11: alu_op = 3'b011; // OR
        endcase
    end

    assign result = {3'b0, alu_out};

endmodule
