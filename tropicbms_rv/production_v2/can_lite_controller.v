module can_lite_controller(
    input  wire        clk,
    input  wire        rst,
    // BMS data to broadcast on vehicle CAN bus
    input  wire [7:0]  soc_percent,
    input  wire [11:0] voted_temp,
    input  wire        trip_signal,
    input  wire        sensor_fault,
    input  wire        broadcast_trigger,   // Periodic tick (e.g. every 100ms)
    // Simplified CAN bus physical interface
    output reg          can_tx,
    output reg          can_frame_valid,
    output reg  [10:0]  can_id_out,          // 11-bit standard CAN ID
    output reg  [63:0]  can_payload_out,     // 8-byte CAN payload
    // Emergency frame — highest priority, bypasses normal queue
    input  wire         emergency_trip
);
    // Real BMS chips MUST talk to the rest of the vehicle: 
    // motor controller (needs to know if it should cut power), 
    // dashboard (needs SOC/temp for display), and charger 
    // (needs to know charge limits). This happens over CAN bus 
    // — the standard automotive communication protocol.
    //
    // This is a simplified CAN-lite framer: it builds 
    // standard-format CAN frames (ID + 8-byte payload) for 
    // BMS status broadcast. A full CAN controller would need 
    // bit-stuffing, CRC, arbitration — this models the frame 
    // construction and priority logic, which is the part 
    // relevant to BMS safety architecture.

    // CAN ID allocation (lower ID = higher bus priority — 
    // standard CAN arbitration rule)
    parameter ID_EMERGENCY_TRIP = 11'h001; // Highest priority!
    parameter ID_BMS_STATUS     = 11'h100; // Normal periodic status

    parameter IDLE      = 2'd0;
    parameter BUILD      = 2'd1;
    parameter TRANSMIT   = 2'd2;

    reg [1:0] state;
    reg       emergency_pending;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state             <= IDLE;
            can_tx            <= 1'b1; // CAN idle = recessive (high)
            can_frame_valid   <= 0;
            can_id_out        <= 0;
            can_payload_out   <= 0;
            emergency_pending <= 0;
        end
        else begin
            can_frame_valid <= 0;

            // Emergency trip latches immediately — highest 
            // priority, jumps queue ahead of periodic status
            if (emergency_trip)
                emergency_pending <= 1;

            case (state)
                IDLE: begin
                    if (emergency_pending) begin
                        state <= BUILD;
                    end
                    else if (broadcast_trigger) begin
                        state <= BUILD;
                    end
                end

                BUILD: begin
                    if (emergency_pending) begin
                        // CRITICAL FRAME: thermal trip, sent 
                        // with highest bus priority
                        can_id_out      <= ID_EMERGENCY_TRIP;
                        can_payload_out <= {56'h0, trip_signal, 
                                             7'b0}; // byte0: trip flag
                        emergency_pending <= 0;
                    end
                    else begin
                        // Normal periodic status frame
                        can_id_out <= ID_BMS_STATUS;
                        can_payload_out <= {
                            8'h0,                    // reserved
                            8'h0,                    // reserved  
                            4'h0, voted_temp,         // temp (12-bit)
                            6'h0, sensor_fault, trip_signal, // flags
                            soc_percent               // SOC %
                        };
                    end
                    state <= TRANSMIT;
                end

                TRANSMIT: begin
                    can_frame_valid <= 1;
                    can_tx          <= 1'b0; // Dominant bit = frame start
                    state           <= IDLE;
                end
            endcase
        end
    end
endmodule
