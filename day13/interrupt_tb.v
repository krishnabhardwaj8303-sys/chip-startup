module interrupt_tb;

    reg        clk, rst;
    reg        tamper_irq, timer_irq;
    reg        uart_irq, spi_irq;
    reg  [3:0] irq_mask;
    reg        irq_ack;
    wire       irq_out;
    wire [3:0] irq_id;
    wire       keys_erase;

    interrupt_ctrl DUT (
        .clk(clk), .rst(rst),
        .tamper_irq(tamper_irq),
        .timer_irq(timer_irq),
        .uart_irq(uart_irq),
        .spi_irq(spi_irq),
        .irq_mask(irq_mask),
        .irq_ack(irq_ack),
        .irq_out(irq_out),
        .irq_id(irq_id),
        .keys_erase(keys_erase)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("interrupt.vcd");
        $dumpvars(0, interrupt_tb);

        rst=1;
        tamper_irq=0; timer_irq=0;
        uart_irq=0;   spi_irq=0;
        irq_mask=4'b0000;
        irq_ack=0;
        #30; rst=0; #20;

        $display("================================");
        $display("  INTERRUPT CONTROLLER TEST    ");
        $display("================================");

        // Test 1: Timer
        $display("--- Test 1: Timer IRQ ---");
        timer_irq=1; #30; timer_irq=0; #20;
        if(irq_out && irq_id==4'd2)
            $display("PASS: Timer IRQ ID=%0d", irq_id);
        else
            $display("FAIL: Timer IRQ");
        irq_ack=1; #10; irq_ack=0; #20;

        // Test 2: UART
        $display("--- Test 2: UART IRQ ---");
        uart_irq=1; #30; uart_irq=0; #20;
        if(irq_out && irq_id==4'd3)
            $display("PASS: UART IRQ ID=%0d", irq_id);
        else
            $display("FAIL: UART IRQ");
        irq_ack=1; #10; irq_ack=0; #20;

        // Test 3: TAMPER
        $display("--- Test 3: TAMPER IRQ ---");
        tamper_irq=1; #30; tamper_irq=0; #20;
        if(irq_out && keys_erase==1)
            $display("PASS: TAMPER Keys Erased ID=%0d", irq_id);
        else
            $display("FAIL: TAMPER IRQ");
        irq_ack=1; #10; irq_ack=0; #20;

        // Test 4: Priority
        $display("--- Test 4: Priority ---");
        timer_irq=1; tamper_irq=1; #30;
        timer_irq=0; tamper_irq=0; #20;
        if(irq_id==4'd1 && keys_erase==1)
            $display("PASS: Tamper wins priority");
        else
            $display("FAIL: Priority");
        irq_ack=1; #10; irq_ack=0; #20;

        $display("================================");
        $display("Day 13 Complete! IRQ working!");
        $display("================================");
        $finish;
    end

endmodule
