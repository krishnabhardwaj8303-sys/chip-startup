// Simple UART Receiver
module uart_rx #(
    parameter CLKS_PER_BIT = 4  // Simplified for simulation speed
)(
    input  wire       clk,
    input  wire       rst,
    input  wire       rx_in,
    output reg  [7:0] data_out,
    output reg         data_valid
);
    localparam IDLE = 0, START = 1, DATA = 2, STOP = 3;
    reg [1:0] state;
    reg [3:0] clk_count;
    reg [2:0] bit_index;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state <= IDLE;
            data_valid <= 0;
            clk_count <= 0;
            bit_index <= 0;
            data_out <= 0;
        end else begin
            data_valid <= 0;
            case (state)
                IDLE: begin
                    if (rx_in == 0) begin
                        state <= START;
                        clk_count <= 0;
                    end
                end
                START: begin
                    if (clk_count == CLKS_PER_BIT/2) begin
                        state <= DATA;
                        clk_count <= 0;
                        bit_index <= 0;
                    end else
                        clk_count <= clk_count + 1;
                end
                DATA: begin
                    if (clk_count < CLKS_PER_BIT - 1)
                        clk_count <= clk_count + 1;
                    else begin
                        clk_count <= 0;
                        data_out[bit_index] <= rx_in;
                        if (bit_index < 7)
                            bit_index <= bit_index + 1;
                        else
                            state <= STOP;
                    end
                end
                STOP: begin
                    if (clk_count < CLKS_PER_BIT - 1)
                        clk_count <= clk_count + 1;
                    else begin
                        data_valid <= 1;
                        state <= IDLE;
                    end
                end
            endcase
        end
    end
endmodule
