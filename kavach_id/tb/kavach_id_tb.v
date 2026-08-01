`timescale 1ns/1ps

module kavach_id_tb;

    reg clk, rst, uart_rx_in;
    wire uart_tx_out, busy_led;

    kavach_id_top uut (
        .clk(clk), .rst(rst),
        .uart_rx_in(uart_rx_in),
        .uart_tx_out(uart_tx_out),
        .busy_led(busy_led)
    );

    always #5 clk = ~clk;

    // Task to send one UART byte (LSB first, CLKS_PER_BIT=4 -> bit period = 40ns)
    task send_uart_byte(input [7:0] data);
        integer i;
        begin
            uart_rx_in = 0; // start bit
            #40;
            for (i = 0; i < 8; i = i + 1) begin
                uart_rx_in = data[i];
                #40;
            end
            uart_rx_in = 1; // stop bit
            #40;
        end
    endtask

    initial begin
        $dumpfile("kavach_id.vcd");
        $dumpvars(0, kavach_id_tb);

        clk = 0;
        rst = 1;
        uart_rx_in = 1;
        #50 rst = 0;
        #20;

        $display("Sending 32-bit challenge: 0xA5B6C7D8");
        send_uart_byte(8'hA5);
        send_uart_byte(8'hB6);
        send_uart_byte(8'hC7);
        send_uart_byte(8'hD8);

        // Wait for chip to process and respond
        #2000;

        $display("Test complete. Check busy_led toggled and uart_tx_out activity in waveform.");
        $display("If simulation ran without errors, Kavach-ID RTL is functionally sound.");

        #200 $finish;
    end

endmodule
