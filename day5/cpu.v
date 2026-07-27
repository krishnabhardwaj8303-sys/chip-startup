module cpu(
    input  wire        clk,
    input  wire        rst,
    input  wire [7:0]  instruction,
    output wire [7:0]  result
);

    // Instruction decode
    wire [1:0] opcode  = instruction[7:6];
    wire [2:0] reg_a   = instruction[5:3];
    wire [2:0] reg_b   = instruction[2:0];

    // Register file signals
    wire [7:0] data_a, data_b;
    reg  [7:0] wr_data;
    reg        wr_en;
    reg  [2:0] wr_addr;

    // ALU signals
    wire [4:0] alu_out;
    reg  [2:0] alu_op;

    // Register File
    reg_file RF (
        .clk(clk), .rst(rst),
        .wr_en(wr_en),
        .wr_addr(wr_addr),
        .wr_data(wr_data),
        .rd_addr1(reg_a),
        .rd_addr2(reg_b),
        .rd_data1(data_a),
        .rd_data2(data_b)
    );

    // ALU — sirf 4-bit use karo
    alu ALU (
        .a(data_a[3:0]),
        .b(data_b[3:0]),
        .op(alu_op),
        .result(alu_out),
        .zero()
    );

    // Instruction decode logic
    always @(*) begin
        case (opcode)
            2'b00: alu_op = 3'b000; // ADD
            2'b01: alu_op = 3'b001; // SUB
            2'b10: alu_op = 3'b010; // AND
            2'b11: alu_op = 3'b011; // OR
        endcase
        wr_en   = 1;
        wr_addr = reg_a;
        wr_data = {3'b0, alu_out};
    end

    assign result = {3'b0, alu_out};

endmodule
