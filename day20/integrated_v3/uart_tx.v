module uart_tx(
    input  wire       clk,
    input  wire       rst,
    input  wire       start,
    input  wire [7:0] data,
    output reg        tx,
    output reg        busy
);
    // 50MHz clock, 9600 baud
    parameter CLKS_PER_BIT = 16;

    parameter IDLE  = 3'd0;
    parameter START = 3'd1;
    parameter DATA  = 3'd2;
    parameter STOP  = 3'd3;
    parameter DONE  = 3'd4;

    reg [2:0]  state;
    reg [7:0]  clk_count;
    reg [2:0]  bit_index;
    reg [7:0]  tx_data;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state     <= IDLE;
            tx        <= 1;
            busy      <= 0;
            clk_count <= 0;
            bit_index <= 0;
        end
        else begin
            case (state)
                IDLE: begin
                    tx   <= 1;
                    busy <= 0;
                    if (start) begin
                        tx_data   <= data;
                        state     <= START;
                        clk_count <= 0;
                        busy      <= 1;
                    end
                end

                START: begin
                    tx <= 0; // Start bit
                    if (clk_count == CLKS_PER_BIT-1) begin
                        clk_count <= 0;
                        bit_index <= 0;
                        state     <= DATA;
                    end else
                        clk_count <= clk_count + 1;
                end

                DATA: begin
                    tx <= tx_data[bit_index];
                    if (clk_count == CLKS_PER_BIT-1) begin
                        clk_count <= 0;
                        if (bit_index == 7) begin
                            state <= STOP;
                        end else
                            bit_index <= bit_index + 1;
                    end else
                        clk_count <= clk_count + 1;
                end

                STOP: begin
                    tx <= 1; // Stop bit
                    if (clk_count == CLKS_PER_BIT-1) begin
                        state     <= DONE;
                        clk_count <= 0;
                    end else
                        clk_count <= clk_count + 1;
                end

                DONE: begin
                    busy  <= 0;
                    state <= IDLE;
                end
            endcase
        end
    end
endmodule
