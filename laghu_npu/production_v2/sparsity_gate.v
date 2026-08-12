module sparsity_gate(
    input  wire         clk,
    input  wire         rst,
    input  wire signed [7:0] w00, w01, w02, w03,
    input  wire signed [7:0] w10, w11, w12, w13,
    input  wire signed [7:0] w20, w21, w22, w23,
    input  wire signed [7:0] w30, w31, w32, w33,
    output reg  [15:0]  pe_clock_enable,
    output reg  [4:0]   zero_weight_count,
    output reg  [7:0]   power_saved_percent
);
    wire [15:0] zero_detect;

    assign zero_detect[0]  = (w00 == 8'sd0);
    assign zero_detect[1]  = (w01 == 8'sd0);
    assign zero_detect[2]  = (w02 == 8'sd0);
    assign zero_detect[3]  = (w03 == 8'sd0);
    assign zero_detect[4]  = (w10 == 8'sd0);
    assign zero_detect[5]  = (w11 == 8'sd0);
    assign zero_detect[6]  = (w12 == 8'sd0);
    assign zero_detect[7]  = (w13 == 8'sd0);
    assign zero_detect[8]  = (w20 == 8'sd0);
    assign zero_detect[9]  = (w21 == 8'sd0);
    assign zero_detect[10] = (w22 == 8'sd0);
    assign zero_detect[11] = (w23 == 8'sd0);
    assign zero_detect[12] = (w30 == 8'sd0);
    assign zero_detect[13] = (w31 == 8'sd0);
    assign zero_detect[14] = (w32 == 8'sd0);
    assign zero_detect[15] = (w33 == 8'sd0);

    // Combinational count -- avoids one-cycle-stale power calc
    wire [4:0] zero_count_comb;
    assign zero_count_comb = zero_detect[0]  + zero_detect[1]  + 
                              zero_detect[2]  + zero_detect[3]  +
                              zero_detect[4]  + zero_detect[5]  + 
                              zero_detect[6]  + zero_detect[7]  +
                              zero_detect[8]  + zero_detect[9]  + 
                              zero_detect[10] + zero_detect[11] +
                              zero_detect[12] + zero_detect[13] + 
                              zero_detect[14] + zero_detect[15];

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            pe_clock_enable     <= 16'hFFFF;
            zero_weight_count   <= 0;
            power_saved_percent <= 0;
        end
        else begin
            pe_clock_enable      <= ~zero_detect;
            zero_weight_count    <= zero_count_comb;
            power_saved_percent  <= (zero_count_comb * 100) / 16;
        end
    end
endmodule
