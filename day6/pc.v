module pc(
    input  wire       clk,
    input  wire       rst,
    input  wire       halt,
    output reg  [2:0] pc_out
);
    always @(posedge clk or posedge rst) begin
        if (rst)
            pc_out <= 3'd0;
        else if (!halt) begin
            if (pc_out == 3'd7)
                pc_out <= 3'd0;  // Wapas start pe
            else
                pc_out <= pc_out + 1;
        end
    end
endmodule
