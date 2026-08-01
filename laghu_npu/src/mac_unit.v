// Single Multiply-Accumulate unit
// Takes 8-bit weight and 8-bit activation, multiplies, accumulates into 32-bit sum
module mac_unit (
    input  wire        clk,
    input  wire        rst,
    input  wire        enable,
    input  wire signed [7:0]  weight,
    input  wire signed [7:0]  activation,
    input  wire        clear_acc,
    output reg  signed [31:0] acc_out
);
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            acc_out <= 32'sd0;
        end else if (clear_acc) begin
            acc_out <= 32'sd0;
        end else if (enable) begin
            acc_out <= acc_out + (weight * activation);
        end
    end
endmodule
