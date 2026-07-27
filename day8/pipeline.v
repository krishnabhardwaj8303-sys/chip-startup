module pipeline(
    input  wire        clk,
    input  wire        rst,
    output reg  [7:0]  result,
    output reg  [2:0]  pc_out
);

    // ─── STAGE 1: FETCH ───
    reg [2:0] if_pc;
    reg [7:0] if_instruction;

    // Instruction Memory
    reg [7:0] imem [0:7];
    initial begin
        imem[0] = 8'b00_000_001; // ADD R0+R1
        imem[1] = 8'b00_010_011; // ADD R2+R3
        imem[2] = 8'b01_000_010; // SUB R0-R2
        imem[3] = 8'b10_001_011; // AND R1&R3
        imem[4] = 8'b11_000_001; // OR  R0|R1
        imem[5] = 8'b00_100_101; // ADD R4+R5
        imem[6] = 8'b01_110_111; // SUB R6-R7
        imem[7] = 8'b10_000_001; // AND R0&R1
    end

    // PC counter
    always @(posedge clk or posedge rst) begin
        if (rst) if_pc <= 0;
        else if (if_pc == 7) if_pc <= 0;
        else if_pc <= if_pc + 1;
    end

    always @(*) if_instruction = imem[if_pc];

    // ─── IF/ID PIPELINE REGISTER ───
    reg [7:0] id_instruction;
    reg [2:0] id_pc;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            id_instruction <= 0;
            id_pc <= 0;
        end else begin
            id_instruction <= if_instruction;
            id_pc <= if_pc;
        end
    end

    // ─── STAGE 2: DECODE ───
    wire [1:0] id_opcode = id_instruction[7:6];
    wire [2:0] id_reg_a  = id_instruction[5:3];
    wire [2:0] id_reg_b  = id_instruction[2:0];

    wire [7:0] id_data_a, id_data_b;

    reg_file RF (
        .clk(clk), .rst(rst),
        .wr_en(1'b1),
        .wr_addr(id_reg_a),
        .wr_data(result),
        .rd_addr1(id_reg_a),
        .rd_addr2(id_reg_b),
        .rd_data1(id_data_a),
        .rd_data2(id_data_b)
    );

    // ─── ID/EX PIPELINE REGISTER ───
    reg [1:0] ex_opcode;
    reg [7:0] ex_data_a, ex_data_b;
    reg [2:0] ex_pc;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            ex_opcode <= 0;
            ex_data_a <= 0;
            ex_data_b <= 0;
            ex_pc     <= 0;
        end else begin
            ex_opcode <= id_opcode;
            ex_data_a <= id_data_a;
            ex_data_b <= id_data_b;
            ex_pc     <= id_pc;
        end
    end

    // ─── STAGE 3: EXECUTE ───
    wire [4:0] alu_out;
    reg  [2:0] alu_op;

    always @(*) begin
        case (ex_opcode)
            2'b00: alu_op = 3'b000; // ADD
            2'b01: alu_op = 3'b001; // SUB
            2'b10: alu_op = 3'b010; // AND
            2'b11: alu_op = 3'b011; // OR
        endcase
    end

    alu ALU (
        .a(ex_data_a[3:0]),
        .b(ex_data_b[3:0]),
        .op(alu_op),
        .result(alu_out),
        .zero()
    );

    // ─── WRITEBACK ───
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            result <= 0;
            pc_out <= 0;
        end else begin
            result <= {3'b0, alu_out};
            pc_out <= ex_pc;
        end
    end

endmodule
