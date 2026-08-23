// UART-to-Register Bridge
// FIX (interface hardening): kavach_id_top.v previously exposed its
// internal parallel register bus (reg_write, reg_read, reg_addr[7:0],
// reg_wdata[31:0], reg_rdata[31:0], reg_ready - ~50 pins) directly as
// TOP-LEVEL CHIP PINS, alongside a separate UART. No real reader
// device or phone can wire to a ~50-pin parallel bus; this made the
// chip physically un-connectable to any realistic host in a deployed
// product. This bridge moves the register bus fully INSIDE the chip:
// externally, only clk/rst/uart_rx/uart_tx are exposed. A host talks
// to the chip purely over UART, using a fixed 6-byte frame:
//   [CMD (1B)] [ADDR (1B)] [DATA (4B, MSB-first)]
//   CMD=0x01: WRITE  -> write DATA to register ADDR
//   CMD=0x02: READ   -> read register ADDR, reply with 4 bytes (MSB-first)
module uart_to_reg_bridge (
    input  wire        clk,
    input  wire        rst,

    // UART physical side (external pins)
    input  wire        uart_rx_in,
    output wire        uart_tx_out,

    // Internal register-bus side (drives kavach_register_map internally)
    output reg          reg_write,
    output reg          reg_read,
    output reg  [7:0]   reg_addr,
    output reg  [31:0]  reg_wdata,
    input  wire [31:0]  reg_rdata,
    input  wire         reg_ready
);
    // ── UART RX: byte receiver ──
    wire [7:0] rx_byte;
    wire       rx_valid;

    uart_rx #(.CLKS_PER_BIT(4)) RXB (
        .clk(clk), .rst(rst),
        .rx_in(uart_rx_in),
        .data_out(rx_byte),
        .data_valid(rx_valid)
    );

    // ── UART TX: byte transmitter ──
    reg        tx_start;
    reg [7:0]  tx_data;
    wire       tx_busy;

    uart_tx #(.CLKS_PER_BIT(4)) TXB (
        .clk(clk), .rst(rst),
        .tx_start(tx_start),
        .data_in(tx_data),
        .tx_out(uart_tx_out),
        .tx_busy(tx_busy)
    );

    // ── Frame assembly FSM ──
    localparam RX_CMD   = 3'd0,
               RX_ADDR  = 3'd1,
               RX_D3    = 3'd2,
               RX_D2    = 3'd3,
               RX_D1    = 3'd4,
               RX_D0    = 3'd5,
               DO_WRITE = 3'd6,
               DO_READ  = 3'd7;

    reg [2:0]  state;
    reg [7:0]  cmd_reg;
    reg [7:0]  addr_reg;
    reg [31:0] data_reg;

    localparam TX_IDLE = 2'd0, TX_B1 = 2'd1, TX_B2 = 2'd2, TX_B3 = 2'd3;
    reg [1:0]  tx_state;
    reg [31:0] tx_shift;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state      <= RX_CMD;
            cmd_reg    <= 0;
            addr_reg   <= 0;
            data_reg   <= 0;
            reg_write  <= 0;
            reg_read   <= 0;
            reg_addr   <= 0;
            reg_wdata  <= 0;
            tx_start   <= 0;
            tx_data    <= 0;
            tx_state   <= TX_IDLE;
            tx_shift   <= 0;
        end
        else begin
            reg_write <= 0; // pulse
            reg_read  <= 0; // pulse
            tx_start  <= 0; // pulse

            case (state)
                RX_CMD:  if (rx_valid) begin cmd_reg  <= rx_byte; state <= RX_ADDR; end
                RX_ADDR: if (rx_valid) begin addr_reg <= rx_byte; state <= RX_D3;   end
                RX_D3:   if (rx_valid) begin data_reg[31:24] <= rx_byte; state <= RX_D2; end
                RX_D2:   if (rx_valid) begin data_reg[23:16] <= rx_byte; state <= RX_D1; end
                RX_D1:   if (rx_valid) begin data_reg[15:8]  <= rx_byte; state <= RX_D0; end
                RX_D0: if (rx_valid) begin
                    data_reg[7:0] <= rx_byte;
                    if (cmd_reg == 8'h01) state <= DO_WRITE;
                    else if (cmd_reg == 8'h02) state <= DO_READ;
                    else state <= RX_CMD; // unknown command: drop frame
                end

                DO_WRITE: begin
                    reg_addr  <= addr_reg;
                    reg_wdata <= data_reg;
                    reg_write <= 1'b1;
                    state     <= RX_CMD;
                end

                DO_READ: begin
                    reg_addr <= addr_reg;
                    reg_read <= 1'b1;
                    state    <= RX_CMD; // reg_rdata sampled combinationally below into tx_shift
                    tx_shift <= reg_rdata; // NOTE: valid the cycle after reg_read pulses, see testbench
                    if (tx_state == TX_IDLE) begin
                        tx_data  <= reg_rdata[31:24];
                        tx_start <= 1'b1;
                        tx_state <= TX_B1;
                    end
                end
                default: state <= RX_CMD;
            endcase

            // Response byte sequencer (independent of RX FSM above)
            case (tx_state)
                TX_B1: if (!tx_busy && !tx_start) begin
                    tx_data  <= tx_shift[23:16];
                    tx_start <= 1'b1;
                    tx_state <= TX_B2;
                end
                TX_B2: if (!tx_busy && !tx_start) begin
                    tx_data  <= tx_shift[15:8];
                    tx_start <= 1'b1;
                    tx_state <= TX_B3;
                end
                TX_B3: if (!tx_busy && !tx_start) begin
                    tx_data  <= tx_shift[7:0];
                    tx_start <= 1'b1;
                    tx_state <= TX_IDLE;
                end
                default: ;
            endcase
        end
    end
endmodule
