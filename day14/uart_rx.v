module uart_rx(
    input  wire       clk,
    input  wire       rst,
    input  wire       rx,
    output reg  [7:0] data,
    output reg        valid
);
    parameter CLKS_PER_BIT = 16;
    parameter HALF_BIT     = 8;

    parameter IDLE  = 3'd0;
    parameter START = 3'd1;
    parameter DATA  = 3'd2;
    parameter STOP  = 3'd3;

    reg [2:0] state;
    reg [7:0] clk_count;
    reg [2:0] bit_index;
    reg [7:0] rx_data;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state     <= IDLE;
            data      <= 0;
            valid     <= 0;
            clk_count <= 0;
            bit_index <= 0;
        end
        else begin
            valid <= 0;
            case (state)
                IDLE: begin
                    if (rx == 0) begin // Start bit detect
                        clk_count <= 0;
                        state     <= START;
                    end
                end

                START: begin
                    if (clk_count == HALF_BIT-1) begin
                        clk_count <= 0;
                        bit_index <= 0;
                        state     <= DATA;
                    end else
                        clk_count <= clk_count + 1;
                end

                DATA: begin
                    if (clk_count == CLKS_PER_BIT-1) begin
                        rx_data[bit_index] <= rx;
                        clk_count <= 0;
                        if (bit_index == 7)
                            state <= STOP;
                        else
                            bit_index <= bit_index + 1;
                    end else
                        clk_count <= clk_count + 1;
                end

                STOP: begin
                    if (clk_count == CLKS_PER_BIT-1) begin
                        data      <= rx_data;
                        valid     <= 1;
                        state     <= IDLE;
                        clk_count <= 0;
                    end else
                        clk_count <= clk_count + 1;
                end
            endcase
        end
    end
endmodule
