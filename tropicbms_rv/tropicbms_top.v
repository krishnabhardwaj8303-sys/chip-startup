module tropicbms_top(
    input  wire        clk,
    input  wire        rst,
    input  wire        adc_start,
    input  wire [4:0]  channel_sel,
    input  wire [11:0] current_sense,
    input  wire        current_valid,
    input  wire [11:0] temp_sensor_1,
    input  wire [11:0] temp_sensor_2,
    input  wire [11:0] temp_sensor_3,
    output wire [11:0] voltage_data,
    output wire        data_valid,
    output wire [7:0]  soc_percent,
    output wire        trip_signal,
    output wire        warning_signal,
    output wire [1:0]  fault_sensor
);

    adc_controller ADC (
        .clk(clk), .rst(rst),
        .start(adc_start),
        .channel_sel(channel_sel),
        .voltage_data(voltage_data),
        .data_valid(data_valid),
        .active_channel()
    );

    coulomb_counter COULOMB (
        .clk(clk), .rst(rst),
        .current_sense(current_sense),
        .current_valid(current_valid),
        .accumulated_charge(),
        .soc_percent(soc_percent)
    );

    // Hardware-only safety trip — 
    // firmware se independent!
    thermal_trip THERMAL (
        .clk(clk), .rst(rst),
        .temp_sensor_1(temp_sensor_1),
        .temp_sensor_2(temp_sensor_2),
        .temp_sensor_3(temp_sensor_3),
        .trip_signal(trip_signal),
        .warning_signal(warning_signal),
        .fault_sensor(fault_sensor)
    );

endmodule
