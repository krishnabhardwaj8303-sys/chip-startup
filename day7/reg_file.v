module reg_file(
    input  wire        clk,
    input  wire        rst,
    input  wire        wr_en,
    input  wire [2:0]  wr_addr,
    input  wire [7:0]  wr_data,
    input  wire [2:0]  rd_addr1,
    input  wire [2:0]  rd_addr2,
    output wire [7:0]  rd_data1,
    output wire [7:0]  rd_data2
);
    // 8 registers, har ek 8-bit
    reg [7:0] registers [0:7];
    integer i;

    // Write operation
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            for (i=0; i<8; i=i+1)
                registers[i] <= 8'b0;
        end
        else if (wr_en) begin
            registers[wr_addr] <= wr_data;
        end
    end

    // Read operation
    assign rd_data1 = registers[rd_addr1];
    assign rd_data2 = registers[rd_addr2];

endmodule
