// 4x4 array of MAC units - each PE has its own weight
module pe_array (
    input  wire clk,
    input  wire rst,
    input  wire enable,
    input  wire clear_acc,
    input  wire signed [7:0] w00, w01, w02, w03,
    input  wire signed [7:0] w10, w11, w12, w13,
    input  wire signed [7:0] w20, w21, w22, w23,
    input  wire signed [7:0] w30, w31, w32, w33,
    input  wire signed [7:0] act0, act1, act2, act3,
    output wire signed [31:0] r00, r01, r02, r03,
    output wire signed [31:0] r10, r11, r12, r13,
    output wire signed [31:0] r20, r21, r22, r23,
    output wire signed [31:0] r30, r31, r32, r33
);
    mac_unit u00 (clk, rst, enable, w00, act0, clear_acc, r00);
    mac_unit u01 (clk, rst, enable, w01, act1, clear_acc, r01);
    mac_unit u02 (clk, rst, enable, w02, act2, clear_acc, r02);
    mac_unit u03 (clk, rst, enable, w03, act3, clear_acc, r03);

    mac_unit u10 (clk, rst, enable, w10, act0, clear_acc, r10);
    mac_unit u11 (clk, rst, enable, w11, act1, clear_acc, r11);
    mac_unit u12 (clk, rst, enable, w12, act2, clear_acc, r12);
    mac_unit u13 (clk, rst, enable, w13, act3, clear_acc, r13);

    mac_unit u20 (clk, rst, enable, w20, act0, clear_acc, r20);
    mac_unit u21 (clk, rst, enable, w21, act1, clear_acc, r21);
    mac_unit u22 (clk, rst, enable, w22, act2, clear_acc, r22);
    mac_unit u23 (clk, rst, enable, w23, act3, clear_acc, r23);

    mac_unit u30 (clk, rst, enable, w30, act0, clear_acc, r30);
    mac_unit u31 (clk, rst, enable, w31, act1, clear_acc, r31);
    mac_unit u32 (clk, rst, enable, w32, act2, clear_acc, r32);
    mac_unit u33 (clk, rst, enable, w33, act3, clear_acc, r33);
endmodule
