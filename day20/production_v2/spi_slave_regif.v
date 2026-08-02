module spi_slave_regif(
    input  wire        clk,
    input  wire        rst,
    // SPI physical pins
    input  wire        sclk,
    input  wire        cs_n,
    input  wire        mosi,
    output reg         miso,
    // Register interface (internal)
    output reg         reg_write,
    output reg         reg_read,
    output reg  [7:0]  reg_addr,
    output reg  [31:0] reg_wdata,
    input  wire [31:0] reg_rdata,
    input  wire        reg_ready
);
    // SPI protocol format:
    // Byte 0: Command (0x01=write, 0x02=read)
    // Byte 1: Register address
    // Byte 2-5: Data (32-bit, write only)

    parameter IDLE     = 3'd0;
    parameter CMD      = 3'd1;
    parameter ADDR     = 3'd2;
    parameter DATA     = 3'd3;
    parameter EXECUTE  = 3'd4;

    reg [2:0]  state;
    reg [2:0]  bit_cnt;
    reg [1:0]  byte_cnt;
    reg [7:0]  cmd_byte;
    reg [7:0]  shift_reg;
    reg        sclk_prev;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state     <= IDLE;
            bit_cnt   <= 0;
            byte_cnt  <= 0;
            reg_write <= 0;
            reg_read  <= 0;
            reg_addr  <= 0;
            reg_wdata <= 0;
            miso      <= 0;
            sclk_prev <= 0;
        end
        else begin
            sclk_prev <= sclk;
            reg_write <= 0;
            reg_read  <= 0;

            if (!cs_n) begin
                // Rising edge of SCLK — sample data
                if (sclk && !sclk_prev) begin
                    shift_reg <= {shift_reg[6:0], mosi};
                    bit_cnt   <= bit_cnt + 1;

                    if (bit_cnt == 3'd7) begin
                        // Ek pura byte mila
                        case (state)
                            IDLE: begin
                                cmd_byte <= {shift_reg[6:0], mosi};
                                state    <= ADDR;
                            end
                            ADDR: begin
                                reg_addr <= {shift_reg[6:0], mosi};
                                if (cmd_byte == 8'h01)
                                    state <= DATA; // Write — data chahiye
                                else begin
                                    state    <= EXECUTE; // Read — turant execute
                                    reg_read <= 1;
                                end
                            end
                            DATA: begin
                                // 4 bytes collect karo (32-bit data)
                                reg_wdata <= {reg_wdata[23:0], 
                                              shift_reg[6:0], mosi};
                                byte_cnt <= byte_cnt + 1;
                                if (byte_cnt == 2'd3) begin
                                    state     <= EXECUTE;
                                    reg_write <= 1;
                                end
                            end
                        endcase
                        bit_cnt <= 0;
                    end
                end
            end
            else begin
                // CS deactivate — reset state for next transaction
                state    <= IDLE;
                bit_cnt  <= 0;
                byte_cnt <= 0;
            end
        end
    end
endmodule
