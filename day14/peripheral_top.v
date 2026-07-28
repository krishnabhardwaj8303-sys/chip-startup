module peripheral_top(
    input  wire        clk,
    input  wire        rst,
    // UART
    input  wire        uart_start,
    input  wire [7:0]  uart_tx_data,
    output wire        uart_tx_line,
    output wire        uart_tx_busy,
    input  wire        uart_rx_line,
    output wire [7:0]  uart_rx_data,
    output wire        uart_rx_valid,
    // SPI
    input  wire        spi_start,
    input  wire [7:0]  spi_mosi_data,
    output wire        spi_sclk,
    output wire        spi_cs_n,
    output wire        spi_mosi,
    input  wire        spi_miso,
    output wire [7:0]  spi_miso_data,
    output wire        spi_done,
    // I2C
    input  wire        i2c_start,
    input  wire [6:0]  i2c_addr,
    input  wire [7:0]  i2c_data,
    output wire        i2c_scl,
    output wire        i2c_sda,
    output wire        i2c_done,
    // PWM
    input  wire [7:0]  pwm_duty,
    input  wire [7:0]  pwm_period,
    output wire        pwm_out,
    // Interrupts
    input  wire        tamper_irq,
    input  wire        timer_irq,
    output wire        irq_out,
    output wire [3:0]  irq_id,
    output wire        keys_erase
);
    // UART TX
    uart_tx UART_TX (
        .clk(clk), .rst(rst),
        .start(uart_start),
        .data(uart_tx_data),
        .tx(uart_tx_line),
        .busy(uart_tx_busy)
    );

    // UART RX
    uart_rx UART_RX (
        .clk(clk), .rst(rst),
        .rx(uart_rx_line),
        .data(uart_rx_data),
        .valid(uart_rx_valid)
    );

    // SPI Master
    spi_master SPI (
        .clk(clk), .rst(rst),
        .start(spi_start),
        .mosi_data(spi_mosi_data),
        .sclk(spi_sclk),
        .cs_n(spi_cs_n),
        .mosi(spi_mosi),
        .miso(spi_miso),
        .miso_data(spi_miso_data),
        .done(spi_done)
    );

    // I2C Master
    wire i2c_sda_out, i2c_sda_en;
    i2c_master I2C (
        .clk(clk), .rst(rst),
        .start(i2c_start),
        .addr(i2c_addr),
        .data(i2c_data),
        .rw(1'b0),
        .sda_out(i2c_sda_out),
        .sda_en(i2c_sda_en),
        .scl(i2c_scl),
        .done(i2c_done),
        .ack()
    );
    assign i2c_sda = i2c_sda_en ? i2c_sda_out : 1'bz;

    // PWM
    pwm PWM (
        .clk(clk), .rst(rst),
        .duty(pwm_duty),
        .period(pwm_period),
        .pwm_out(pwm_out),
        .active()
    );

    // Interrupt Controller
    interrupt_ctrl IRQ (
        .clk(clk), .rst(rst),
        .tamper_irq(tamper_irq),
        .timer_irq(timer_irq),
        .uart_irq(uart_rx_valid),
        .spi_irq(spi_done),
        .irq_mask(4'b0000),
        .irq_ack(1'b0),
        .irq_out(irq_out),
        .irq_id(irq_id),
        .keys_erase(keys_erase)
    );

endmodule
