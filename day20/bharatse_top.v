module bharatse_top(
    input  wire        clk,
    input  wire        rst,
    // External interface
    input  wire [127:0] plaintext,
    input  wire        encrypt_start,
    input  wire        tamper_detect,
    // UART output
    output wire        uart_tx,
    // Status
    output reg         encrypt_done,
    output reg         keys_erased,
    output reg  [127:0] ciphertext
);
    // ── PUF Key Generation ──
    wire [127:0] puf_key;
    wire         puf_key_ready;
    reg          puf_start;

    puf_key PUF (
        .clk(clk), .rst(rst),
        .start(puf_start),
        .device_key(puf_key),
        .key_ready(puf_key_ready)
    );

    // ── AES Core ──
    wire [127:0] aes_out;

    aes_core AES (
        .plaintext(plaintext),
        .key(puf_key),
        .ciphertext(aes_out)
    );

    // ── UART TX ──
    reg        uart_start;
    reg  [7:0] uart_data;
    wire       uart_busy;

    uart_tx UART (
        .clk(clk), .rst(rst),
        .start(uart_start),
        .data(uart_data),
        .tx(uart_tx),
        .busy(uart_busy)
    );

    // ── Interrupt Controller ──
    wire irq_out;
    wire [3:0] irq_id;
    wire hw_keys_erase;

    interrupt_ctrl IRQ (
        .clk(clk), .rst(rst),
        .tamper_irq(tamper_detect),
        .timer_irq(1'b0),
        .uart_irq(1'b0),
        .spi_irq(1'b0),
        .irq_mask(4'b0000),
        .irq_ack(1'b1),
        .irq_out(irq_out),
        .irq_id(irq_id),
        .keys_erase(hw_keys_erase)
    );

    // ── Main FSM ──
    parameter IDLE      = 3'd0;
    parameter GEN_KEY   = 3'd1;
    parameter WAIT_KEY  = 3'd2;
    parameter ENCRYPT   = 3'd3;
    parameter SEND_UART = 3'd4;
    parameter DONE      = 3'd5;
    parameter ERASED    = 3'd6;

    reg [2:0] state;
    reg [3:0] uart_byte_cnt;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state         <= IDLE;
            puf_start     <= 0;
            uart_start    <= 0;
            uart_data     <= 0;
            encrypt_done  <= 0;
            keys_erased   <= 0;
            ciphertext    <= 0;
            uart_byte_cnt <= 0;
        end
        else begin
            // Tamper = immediate key erase
            if (hw_keys_erase) begin
                ciphertext  <= 128'h0;
                keys_erased <= 1;
                state       <= ERASED;
            end
            else begin
                case (state)
                    IDLE: begin
                        encrypt_done <= 0;
                        if (encrypt_start) begin
                            puf_start <= 1;
                            state     <= GEN_KEY;
                        end
                    end

                    GEN_KEY: begin
                        puf_start <= 0;
                        state     <= WAIT_KEY;
                    end

                    WAIT_KEY: begin
                        if (puf_key_ready)
                            state <= ENCRYPT;
                    end

                    ENCRYPT: begin
                        ciphertext <= aes_out;
                        state      <= SEND_UART;
                        uart_byte_cnt <= 0;
                    end

                    SEND_UART: begin
                        if (!uart_busy) begin
                            // Send first byte of ciphertext
                            uart_data  <= ciphertext[127:120];
                            uart_start <= 1;
                            state      <= DONE;
                        end
                    end

                    DONE: begin
                        uart_start   <= 0;
                        encrypt_done <= 1;
                        state        <= IDLE;
                    end

                    ERASED: begin
                        keys_erased <= 1;
                    end
                endcase
            end
        end
    end
endmodule
