module bms_register_map(
    input  wire        clk,
    input  wire        rst,
    input  wire        reg_write,
    input  wire        reg_read,
    input  wire [7:0]  reg_addr,
    input  wire [31:0] reg_wdata,
    output reg  [31:0] reg_rdata,
    output reg          reg_ready,

    input  wire         bist_pass_i,
    input  wire         bist_fail_i,
    input  wire         watchdog_fault_i,
    input  wire         sensor_fault_i,
    input  wire         trip_signal_i,
    input  wire [7:0]   soc_percent_i,
    input  wire [11:0]  voted_temp_i,

    output reg          bist_start_o,
    output reg          fsm_heartbeat_o
);
    // 0x00: CONTROL - bit0=bist_start, bit1=fsm_heartbeat
    // 0x04: STATUS - bit0=bist_pass, bit1=bist_fail, bit2=watchdog_fault,
    //                bit3=sensor_fault, bit4=trip_signal
    // 0x08: SOC (read) - state of charge %
    // 0x0C: TEMP (read) - voted temperature value
    // 0xFC: CHIP_ID (read)

    parameter ADDR_CONTROL = 8'h00;
    parameter ADDR_STATUS  = 8'h04;
    parameter ADDR_SOC     = 8'h08;
    parameter ADDR_TEMP    = 8'h0C;
    parameter ADDR_CHIP_ID = 8'hFC;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            reg_rdata        <= 0;
            reg_ready        <= 0;
            bist_start_o     <= 0;
            fsm_heartbeat_o  <= 0;
        end
        else begin
            reg_ready       <= 0;
            bist_start_o    <= 0;
            fsm_heartbeat_o <= 0;

            if (reg_write) begin
                reg_ready <= 1;
                case (reg_addr)
                    ADDR_CONTROL: begin
                        bist_start_o    <= reg_wdata[0];
                        fsm_heartbeat_o <= reg_wdata[1];
                    end
                    default: ;
                endcase
            end

            if (reg_read) begin
                reg_ready <= 1;
                case (reg_addr)
                    ADDR_STATUS: reg_rdata <= {27'b0,
                                    trip_signal_i,
                                    sensor_fault_i,
                                    watchdog_fault_i,
                                    bist_fail_i,
                                    bist_pass_i};
                    ADDR_SOC:     reg_rdata <= {24'b0, soc_percent_i};
                    ADDR_TEMP:    reg_rdata <= {20'b0, voted_temp_i};
                    ADDR_CHIP_ID: reg_rdata <= 32'h544D5342; // "TMSB" hex
                    default:      reg_rdata <= 32'h0;
                endcase
            end
        end
    end
endmodule
