module spi_master(
    input  wire       clk,
    input  wire       rst,
    input  wire       start,
    input  wire [7:0] mosi_data,
    output reg        sclk,
    output reg        cs_n,
    output reg        mosi,
    input  wire       miso,
    output reg  [7:0] miso_data,
    output reg        done
);
    parameter IDLE     = 2'd0;
    parameter TRANSFER = 2'd1;
    parameter FINISH   = 2'd2;

    reg [1:0] state;
    reg [2:0] bit_cnt;
    reg [7:0] shift_out;
    reg [7:0] shift_in;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state     <= IDLE;
            sclk      <= 0;
            cs_n      <= 1;
            mosi      <= 0;
            miso_data <= 0;
            done      <= 0;
            bit_cnt   <= 7;
            shift_out <= 0;
            shift_in  <= 0;
        end
        else begin
            case (state)
                IDLE: begin
                    sclk <= 0;
                    cs_n <= 1;
                    done <= 0;
                    if (start) begin
                        shift_out <= mosi_data;
                        bit_cnt   <= 7;
                        cs_n      <= 0;
                        state     <= TRANSFER;
                    end
                end

                TRANSFER: begin
                    sclk <= ~sclk;
                    if (!sclk) begin
                        // Rising edge — data sample
                        mosi <= shift_out[bit_cnt];
                        shift_in <= {shift_in[6:0], miso};
                    end else begin
                        // Falling edge — next bit
                        if (bit_cnt == 0) begin
                            state <= FINISH;
                        end else
                            bit_cnt <= bit_cnt - 1;
                    end
                end

                FINISH: begin
                    cs_n      <= 1;
                    sclk      <= 0;
                    miso_data <= shift_in;
                    done      <= 1;
                    state     <= IDLE;
                end
            endcase
        end
    end
endmodule
