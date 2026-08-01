// Laghu-NPU Top Module
module laghu_npu_top (
    input  wire        clk,
    input  wire        rst,
    input  wire        start,
    output reg          done,
    input  wire        load_weights,
    input  wire [1:0]  weight_row_idx,
    input  wire signed [7:0] w_in0, w_in1, w_in2, w_in3,
    input  wire        load_activations,
    input  wire signed [7:0] a_in0, a_in1, a_in2, a_in3,
    output wire signed [31:0] out0, out1, out2, out3
);

    reg signed [7:0] w [0:3][0:3];
    reg signed [7:0] act0, act1, act2, act3;

    localparam IDLE    = 2'b00;
    localparam COMPUTE = 2'b01;
    localparam DONE_ST = 2'b10;

    reg [1:0] state;
    reg mac_enable;
    reg clear_acc;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            w[0][0] <= 0; w[0][1] <= 0; w[0][2] <= 0; w[0][3] <= 0;
            w[1][0] <= 0; w[1][1] <= 0; w[1][2] <= 0; w[1][3] <= 0;
            w[2][0] <= 0; w[2][1] <= 0; w[2][2] <= 0; w[2][3] <= 0;
            w[3][0] <= 0; w[3][1] <= 0; w[3][2] <= 0; w[3][3] <= 0;
        end else if (load_weights) begin
            w[weight_row_idx][0] <= w_in0;
            w[weight_row_idx][1] <= w_in1;
            w[weight_row_idx][2] <= w_in2;
            w[weight_row_idx][3] <= w_in3;
        end
    end

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            act0 <= 0; act1 <= 0; act2 <= 0; act3 <= 0;
        end else if (load_activations) begin
            act0 <= a_in0;
            act1 <= a_in1;
            act2 <= a_in2;
            act3 <= a_in3;
        end
    end

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state      <= IDLE;
            mac_enable <= 1'b0;
            clear_acc  <= 1'b0;
            done       <= 1'b0;
        end else begin
            case (state)
                IDLE: begin
                    done <= 1'b0;
                    if (start) begin
                        clear_acc  <= 1'b1;
                        state      <= COMPUTE;
                    end
                end
                COMPUTE: begin
                    clear_acc  <= 1'b0;
                    mac_enable <= 1'b1;
                    state      <= DONE_ST;
                end
                DONE_ST: begin
                    mac_enable <= 1'b0;
                    done       <= 1'b1;
                    state      <= IDLE;
                end
                default: state <= IDLE;
            endcase
        end
    end

    wire signed [31:0] r00, r01, r02, r03;
    wire signed [31:0] r10, r11, r12, r13;
    wire signed [31:0] r20, r21, r22, r23;
    wire signed [31:0] r30, r31, r32, r33;

    pe_array u_pe_array (
        .clk(clk), .rst(rst), .enable(mac_enable), .clear_acc(clear_acc),
        .w00(w[0][0]), .w01(w[0][1]), .w02(w[0][2]), .w03(w[0][3]),
        .w10(w[1][0]), .w11(w[1][1]), .w12(w[1][2]), .w13(w[1][3]),
        .w20(w[2][0]), .w21(w[2][1]), .w22(w[2][2]), .w23(w[2][3]),
        .w30(w[3][0]), .w31(w[3][1]), .w32(w[3][2]), .w33(w[3][3]),
        .act0(act0), .act1(act1), .act2(act2), .act3(act3),
        .r00(r00), .r01(r01), .r02(r02), .r03(r03),
        .r10(r10), .r11(r11), .r12(r12), .r13(r13),
        .r20(r20), .r21(r21), .r22(r22), .r23(r23),
        .r30(r30), .r31(r31), .r32(r32), .r33(r33)
    );

    // Row-wise sum (dot product = sum of 4 products per row)
    wire signed [31:0] row0_sum, row1_sum, row2_sum, row3_sum;
    assign row0_sum = r00 + r01 + r02 + r03;
    assign row1_sum = r10 + r11 + r12 + r13;
    assign row2_sum = r20 + r21 + r22 + r23;
    assign row3_sum = r30 + r31 + r32 + r33;

    relu u_relu0 (.data_in(row0_sum), .data_out(out0));
    relu u_relu1 (.data_in(row1_sum), .data_out(out1));
    relu u_relu2 (.data_in(row2_sum), .data_out(out2));
    relu u_relu3 (.data_in(row3_sum), .data_out(out3));

endmodule
