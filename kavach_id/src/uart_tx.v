// Simple UART Transmitter
module uart_tx #(
    parameter CLKS_PER_BIT = 4
)(
    input  wire       clk,
    input  wire       rst,
    input  wire       tx_start,
    input  wire [7:0] data_in,
    output reg         tx_out,
    output reg         tx_busy
);
    localparam IDLE = 0, START = 1, DATA = 2, STOP = 3;
    reg [1:0] state;
    reg [3:0] clk_count;
    reg [2:0] bit_index;
    reg [7:0] data_reg;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state <= IDLE;
            tx_out <= 1;
            tx_busy <= 0;
            clk_count <= 0;
            bit_index <= 0;
        end else begin
            case (state)
                IDLE: begin
                    tx_out <= 1;
                    if (tx_start) begin
                        data_reg <= data_in;
                        state <= START;
                        tx_busy <= 1;
                        clk_count <= 0;
                    end
                end
                START: begin
                    tx_out <= 0;
                    if (clk_count < CLKS_PER_BIT - 1)
                        clk_count <= clk_count + 1;
                    else begin
                        clk_count <= 0;
                        state <= DATA;
                        bit_index <= 0;
                    end
                end
                DATA: begin
                    tx_out <= data_reg[bit_index];
                    if (clk_count < CLKS_PER_BIT - 1)
                        clk_count <= clk_count + 1;
                    else begin
                        clk_count <= 0;
                        if (bit_index < 7)
                            bit_index <= bit_index + 1;
                        else
                            state <= STOP;
                    end
                end
                STOP: begin
                    tx_out <= 1;
                    if (clk_count < CLKS_PER_BIT - 1)
                        clk_count <= clk_count + 1;
                    else begin
                        tx_busy <= 0;
                        state <= IDLE;
                    end
                end
            endcase
        end
    end
endmodule
