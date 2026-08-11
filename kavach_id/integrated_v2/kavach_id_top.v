// Kavach-ID: PUF-based Anti-Counterfeit Authentication Chip
// Protocol: Host sends 4-byte (32-bit) challenge over UART ->
//           Chip computes PUF response, scrambles it ->
//           Chip sends back 4-byte (32-bit) scrambled response over UART
module kavach_id_top (
    input  wire clk,
    input  wire rst,
    input  wire uart_rx_in,
    output wire uart_tx_out,
    output wire busy_led
);

    // ---------------- UART RX ----------------
    wire [7:0] rx_data;
    wire       rx_valid;

    uart_rx #(.CLKS_PER_BIT(4)) u_rx (
        .clk(clk), .rst(rst),
        .rx_in(uart_rx_in),
        .data_out(rx_data),
        .data_valid(rx_valid)
    );

    // ---------------- Challenge Assembly (4 bytes -> 32 bits) ----------------
    reg [31:0] challenge_reg;
    reg [1:0]  byte_count;
    reg        challenge_ready;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            challenge_reg   <= 32'd0;
            byte_count      <= 2'd0;
            challenge_ready <= 1'b0;
        end else begin
            challenge_ready <= 1'b0;
            if (rx_valid) begin
                challenge_reg <= {challenge_reg[23:0], rx_data};
                if (byte_count == 2'd3) begin
                    byte_count      <= 2'd0;
                    challenge_ready <= 1'b1;
                end else begin
                    byte_count <= byte_count + 1'b1;
                end
            end
        end
    end

    // ---------------- Control FSM ----------------
    localparam IDLE       = 3'd0;
    localparam PULSE_PUF  = 3'd1;
    localparam CAPTURE    = 3'd2;
    localparam SCRAMBLE   = 3'd3;
    localparam SEND_B0    = 3'd4;
    localparam SEND_B1    = 3'd5;
    localparam SEND_B2    = 3'd6;
    localparam SEND_B3    = 3'd7;

    reg [2:0] state;
    reg       pulse_in;
    reg [31:0] latched_challenge;
    reg [31:0] response_reg;
    reg        tx_start;
    reg [7:0]  tx_data;

    wire [31:0] puf_raw_response;
    wire [31:0] puf_scrambled;
    wire        tx_busy;

    puf_array u_puf (
        .clk(clk), .rst(rst),
        .pulse_in(pulse_in),
        .challenge(latched_challenge),
        .response(puf_raw_response)
    );

    scrambler u_scrambler (
        .challenge(latched_challenge),
        .raw_response(puf_raw_response),
        .scrambled_response(puf_scrambled)
    );

    uart_tx #(.CLKS_PER_BIT(4)) u_tx (
        .clk(clk), .rst(rst),
        .tx_start(tx_start),
        .data_in(tx_data),
        .tx_out(uart_tx_out),
        .tx_busy(tx_busy)
    );

    assign busy_led = (state != IDLE);

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state             <= IDLE;
            pulse_in          <= 1'b0;
            latched_challenge <= 32'd0;
            response_reg      <= 32'd0;
            tx_start          <= 1'b0;
        end else begin
            tx_start <= 1'b0;
            case (state)
                IDLE: begin
                    pulse_in <= 1'b0;
                    if (challenge_ready) begin
                        latched_challenge <= challenge_reg;
                        state <= PULSE_PUF;
                    end
                end
                PULSE_PUF: begin
                    pulse_in <= 1'b1;   // Trigger the PUF race
                    state    <= CAPTURE;
                end
                CAPTURE: begin
                    pulse_in <= 1'b0;
                    state    <= SCRAMBLE;
                end
                SCRAMBLE: begin
                    response_reg <= puf_scrambled;
                    state        <= SEND_B0;
                end
                SEND_B0: begin
                    if (!tx_busy) begin
                        tx_data  <= response_reg[31:24];
                        tx_start <= 1'b1;
                        state    <= SEND_B1;
                    end
                end
                SEND_B1: begin
                    if (!tx_busy && !tx_start) begin
                        tx_data  <= response_reg[23:16];
                        tx_start <= 1'b1;
                        state    <= SEND_B2;
                    end
                end
                SEND_B2: begin
                    if (!tx_busy && !tx_start) begin
                        tx_data  <= response_reg[15:8];
                        tx_start <= 1'b1;
                        state    <= SEND_B3;
                    end
                end
                SEND_B3: begin
                    if (!tx_busy && !tx_start) begin
                        tx_data  <= response_reg[7:0];
                        tx_start <= 1'b1;
                        state    <= IDLE;
                    end
                end
                default: state <= IDLE;
            endcase
        end
    end

endmodule
