module i2c_master(
    input  wire       clk,
    input  wire       rst,
    input  wire       start,
    input  wire [6:0] addr,
    input  wire [7:0] data,
    input  wire       rw,
    output reg        sda_out,
    output reg        sda_en,
    output reg        scl,
    output reg        done,
    output reg        ack
);
    parameter IDLE     = 4'd0;
    parameter START    = 4'd1;
    parameter ADDR     = 4'd2;
    parameter ACK1     = 4'd3;
    parameter DATA     = 4'd4;
    parameter ACK2     = 4'd5;
    parameter STOP     = 4'd6;
    parameter FINISH   = 4'd7;

    reg [3:0] state;
    reg [3:0] bit_cnt;
    reg [7:0] shift_reg;
    reg       clk_div;
    reg [3:0] clk_cnt;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state    <= IDLE;
            scl      <= 1;
            sda_out  <= 1;
            sda_en   <= 0;
            done     <= 0;
            ack      <= 0;
            clk_div  <= 0;
            clk_cnt  <= 0;
            bit_cnt  <= 0;
            shift_reg<= 0;
        end
        else begin
            clk_cnt <= clk_cnt + 1;
            if (clk_cnt == 4'd7) begin
                clk_div <= ~clk_div;
                clk_cnt <= 0;
            end

            case (state)
                IDLE: begin
                    scl     <= 1;
                    sda_out <= 1;
                    sda_en  <= 1;
                    done    <= 0;
                    if (start) begin
                        state    <= START;
                        shift_reg<= {addr, rw};
                        bit_cnt  <= 7;
                    end
                end

                START: begin
                    sda_out <= 0;
                    scl     <= 1;
                    if (clk_div) begin
                        scl   <= 0;
                        state <= ADDR;
                    end
                end

                ADDR: begin
                    sda_out <= shift_reg[7];
                    scl     <= clk_div;
                    if (clk_div && clk_cnt == 0) begin
                        if (bit_cnt == 0) begin
                            state   <= ACK1;
                            bit_cnt <= 7;
                        end else begin
                            shift_reg <= {shift_reg[6:0], 1'b0};
                            bit_cnt   <= bit_cnt - 1;
                        end
                    end
                end

                ACK1: begin
                    sda_en  <= 0;
                    scl     <= clk_div;
                    if (clk_div && clk_cnt == 0) begin
                        ack       <= 1;
                        shift_reg <= data;
                        state     <= DATA;
                        sda_en    <= 1;
                    end
                end

                DATA: begin
                    sda_out <= shift_reg[7];
                    scl     <= clk_div;
                    if (clk_div && clk_cnt == 0) begin
                        if (bit_cnt == 0) begin
                            state   <= ACK2;
                            bit_cnt <= 7;
                        end else begin
                            shift_reg <= {shift_reg[6:0], 1'b0};
                            bit_cnt   <= bit_cnt - 1;
                        end
                    end
                end

                ACK2: begin
                    sda_en <= 0;
                    scl    <= clk_div;
                    if (clk_div && clk_cnt == 0) begin
                        state  <= STOP;
                        sda_en <= 1;
                    end
                end

                STOP: begin
                    sda_out <= 0;
                    scl     <= 1;
                    if (clk_div) begin
                        sda_out <= 1;
                        state   <= FINISH;
                    end
                end

                FINISH: begin
                    done  <= 1;
                    state <= IDLE;
                end
            endcase
        end
    end
endmodule
