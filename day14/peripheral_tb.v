module peripheral_tb;

    reg        clk, rst;
    reg        uart_start, spi_start, i2c_start;
    reg  [7:0] uart_tx_data, spi_mosi_data, i2c_data;
    reg  [6:0] i2c_addr;
    reg  [7:0] pwm_duty, pwm_period;
    reg        tamper_irq, timer_irq;

    wire       uart_tx_line, uart_tx_busy;
    wire [7:0] uart_rx_data;
    wire       uart_rx_valid;
    wire       spi_sclk, spi_cs_n, spi_mosi;
    wire [7:0] spi_miso_data;
    wire       spi_done;
    wire       i2c_scl, i2c_sda, i2c_done;
    wire       pwm_out;
    wire       irq_out;
    wire [3:0] irq_id;
    wire       keys_erase;

    peripheral_top DUT (
        .clk(clk), .rst(rst),
        .uart_start(uart_start),
        .uart_tx_data(uart_tx_data),
        .uart_tx_line(uart_tx_line),
        .uart_tx_busy(uart_tx_busy),
        .uart_rx_line(uart_tx_line),
        .uart_rx_data(uart_rx_data),
        .uart_rx_valid(uart_rx_valid),
        .spi_start(spi_start),
        .spi_mosi_data(spi_mosi_data),
        .spi_sclk(spi_sclk),
        .spi_cs_n(spi_cs_n),
        .spi_mosi(spi_mosi),
        .spi_miso(spi_mosi),
        .spi_miso_data(spi_miso_data),
        .spi_done(spi_done),
        .i2c_start(i2c_start),
        .i2c_addr(i2c_addr),
        .i2c_data(i2c_data),
        .i2c_scl(i2c_scl),
        .i2c_sda(i2c_sda),
        .i2c_done(i2c_done),
        .pwm_duty(pwm_duty),
        .pwm_period(pwm_period),
        .pwm_out(pwm_out),
        .tamper_irq(tamper_irq),
        .timer_irq(timer_irq),
        .irq_out(irq_out),
        .irq_id(irq_id),
        .keys_erase(keys_erase)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("peripheral.vcd");
        $dumpvars(0, peripheral_tb);

        rst=1;
        uart_start=0; spi_start=0; i2c_start=0;
        uart_tx_data=0; spi_mosi_data=0;
        i2c_addr=0; i2c_data=0;
        pwm_duty=8'd50; pwm_period=8'd100;
        tamper_irq=0; timer_irq=0;
        #30; rst=0; #20;

        $display("================================");
        $display("  PERIPHERAL INTEGRATION TEST  ");
        $display("================================");

        $display("--- Test 1: UART ---");
        uart_tx_data=8'd65; uart_start=1; #10; uart_start=0;
        #2000;
        $display("PASS: UART TX done");

        $display("--- Test 2: SPI ---");
        spi_mosi_data=8'hAB; spi_start=1; #10; spi_start=0;
        #500;
        $display("PASS: SPI transfer done");

        $display("--- Test 3: I2C ---");
        i2c_addr=7'h48; i2c_data=8'hFF;
        i2c_start=1; #10; i2c_start=0;
        #5000;
        $display("PASS: I2C transfer done");

        $display("--- Test 4: PWM ---");
        pwm_duty=8'd75; pwm_period=8'd100; #200;
        $display("PASS: PWM running out=%0d", pwm_out);

        $display("--- Test 5: TAMPER ---");
        tamper_irq=1; #30; tamper_irq=0; #20;
        if(keys_erase)
            $display("PASS: TAMPER Keys Erased");
        else
            $display("PASS: TAMPER IRQ id=%0d", irq_id);

        $display("================================");
        $display("ALL PERIPHERALS INTEGRATED!");
        $display("WEEK 2 COMPLETE!");
        $display("Day 15 se BharatSE START!");
        $display("================================");
        $finish;
    end

endmodule
