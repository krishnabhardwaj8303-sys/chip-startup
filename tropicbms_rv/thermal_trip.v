module thermal_trip(
    input  wire        clk,
    input  wire        rst,
    input  wire [11:0] temp_sensor_1,  // NTC sensor 1
    input  wire [11:0] temp_sensor_2,  // NTC sensor 2 (redundant)
    input  wire [11:0] temp_sensor_3,  // NTC sensor 3 (redundant)
    output reg         trip_signal,    // Emergency disconnect signal
    output reg         warning_signal, // Early warning
    output reg  [1:0]  fault_sensor    // Which sensor triggered
);
    // Indian tropical climate ke liye thresholds
    parameter WARNING_TEMP = 12'd2800;  // ~55°C scaled
    parameter TRIP_TEMP     = 12'd3200;  // ~70°C scaled (thermal runaway zone)

    // Yeh FSM firmware se independent hai — 
    // agar CPU hang ho jaaye tab bhi yeh 
    // hardware-only trip karega
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            trip_signal    <= 0;
            warning_signal <= 0;
            fault_sensor   <= 0;
        end
        else begin
            // Redundant triple-sensor check — 
            // koi bhi ek sensor threshold cross 
            // kare toh trip karo (fail-safe design)
            if (temp_sensor_1 >= TRIP_TEMP) begin
                trip_signal  <= 1;
                fault_sensor <= 2'd1;
            end
            else if (temp_sensor_2 >= TRIP_TEMP) begin
                trip_signal  <= 1;
                fault_sensor <= 2'd2;
            end
            else if (temp_sensor_3 >= TRIP_TEMP) begin
                trip_signal  <= 1;
                fault_sensor <= 2'd3;
            end
            else begin
                trip_signal <= 0;
            end

            // Early warning — abhi trip nahi, 
            // lekin alert bhejo
            if (temp_sensor_1 >= WARNING_TEMP ||
                temp_sensor_2 >= WARNING_TEMP ||
                temp_sensor_3 >= WARNING_TEMP)
                warning_signal <= 1;
            else
                warning_signal <= 0;
        end
    end
endmodule
