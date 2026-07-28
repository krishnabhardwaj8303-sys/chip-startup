module interrupt_ctrl(
    input  wire        clk,
    input  wire        rst,
    // Interrupt sources
    input  wire        tamper_irq,
    input  wire        timer_irq,
    input  wire        uart_irq,
    input  wire        spi_irq,
    // CPU interface
    input  wire [3:0]  irq_mask,
    input  wire        irq_ack,
    // Outputs
    output reg         irq_out,
    output reg  [3:0]  irq_id,
    output reg         keys_erase
);
    parameter IDLE    = 2'd0;
    parameter PENDING = 2'd1;
    parameter SERVING = 2'd2;

    reg [1:0] state;
    reg [3:0] irq_reg;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state      <= IDLE;
            irq_out    <= 0;
            irq_id     <= 0;
            keys_erase <= 0;
            irq_reg    <= 0;
        end
        else begin
            // Latch interrupts
            irq_reg[0] <= tamper_irq;
            irq_reg[1] <= timer_irq;
            irq_reg[2] <= uart_irq;
            irq_reg[3] <= spi_irq;

            case (state)
                IDLE: begin
                    irq_out    <= 0;
                    keys_erase <= 0;

                    // Priority: tamper > timer > uart > spi
                    if (irq_reg[0] & ~irq_mask[0]) begin
                        irq_id  <= 4'd1;
                        irq_out <= 1;
                        // TAMPER — keys erase karo!
                        keys_erase <= 1;
                        state   <= SERVING;
                    end
                    else if (irq_reg[1] & ~irq_mask[1]) begin
                        irq_id  <= 4'd2;
                        irq_out <= 1;
                        state   <= SERVING;
                    end
                    else if (irq_reg[2] & ~irq_mask[2]) begin
                        irq_id  <= 4'd3;
                        irq_out <= 1;
                        state   <= SERVING;
                    end
                    else if (irq_reg[3] & ~irq_mask[3]) begin
                        irq_id  <= 4'd4;
                        irq_out <= 1;
                        state   <= SERVING;
                    end
                end

                SERVING: begin
                    if (irq_ack) begin
                        irq_out    <= 0;
                        keys_erase <= 0;
                        state      <= IDLE;
                    end
                end
            endcase
        end
    end
endmodule
