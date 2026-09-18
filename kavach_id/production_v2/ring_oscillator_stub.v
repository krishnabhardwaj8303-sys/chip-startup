module ring_oscillator #(
    parameter HALF_PERIOD = 1
)(
    input  wire enable,
    output reg  clk_out
);
    reg [3:0] div_cnt;
    always @(posedge enable or negedge enable) begin
        if (!enable) begin
            clk_out <= 1'b0;
            div_cnt <= 4'b0;
        end else begin
            div_cnt <= div_cnt + 1;
            clk_out <= div_cnt[0];
        end
    end
endmodule
