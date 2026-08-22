module arbiter_puf_cell (
    input  wire clk,
    input  wire rst,
    input  wire challenge_bit,
    input  wire pulse_in,
    output reg  puf_bit
);
    wire raw_a, raw_b;
    wire path_a, path_b;

    buf (raw_a, pulse_in);
    buf (raw_b, pulse_in);

    assign path_a = challenge_bit ? raw_b : raw_a;
    assign path_b = challenge_bit ? raw_a : raw_b;

    always @(posedge clk or posedge rst) begin
        if (rst)
            puf_bit <= 1'b0;
        else
            puf_bit <= (path_a && !path_b) ? 1'b1 :
                       (path_b && !path_a) ? 1'b0 : puf_bit;
    end
endmodule
