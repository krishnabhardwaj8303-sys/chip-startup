module spi_slave(
    input  wire       clk,
    input  wire       rst,
    input  wire       sclk,
    input  wire       cs_n,
    input  wire       mosi,
    output reg        miso,
    output reg  [7:0] rx_data,
    output reg        valid
);
    reg [2:0] bit_cnt;
    reg [7:0] shift_reg;
    reg       sclk_prev;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            bit_cnt   <= 7;
            shift_reg <= 0;
            rx_data   <= 0;
            valid     <= 0;
            miso      <= 0;
            sclk_prev <= 0;
        end
        else begin
            valid     <= 0;
            sclk_prev <= sclk;

            if (!cs_n) begin
                // Rising edge detect
                if (sclk && !sclk_prev) begin
                    shift_reg <= {shift_reg[6:0], mosi};
                    miso      <= shift_reg[7];
                    if (bit_cnt == 0) begin
                        rx_data <= {shift_reg[6:0], mosi};
                        valid   <= 1;
                        bit_cnt <= 7;
                    end else
                        bit_cnt <= bit_cnt - 1;
                end
            end else begin
                bit_cnt <= 7;
            end
        end
    end
endmodule
