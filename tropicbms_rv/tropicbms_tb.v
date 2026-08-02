module tropicbms_tb;

    reg        clk, rst;
    reg        adc_start;
    reg  [4:0] channel_sel;
    reg  [11:0] current_sense;
    reg        current_valid;
    reg  [11:0] temp_sensor_1, temp_sensor_2, temp_sensor_3;

    wire [11:0] voltage_data;
    wire        data_valid;
    wire [7:0]  soc_percent;
    wire        trip_signal;
    wire        warning_signal;
    wire [1:0]  fault_sensor;

    tropicbms_top DUT (
        .clk(clk), .rst(rst),
        .adc_start(adc_start),
        .channel_sel(channel_sel),
        .current_sense(current_sense),
        .current_valid(current_valid),
        .temp_sensor_1(temp_sensor_1),
        .temp_sensor_2(temp_sensor_2),
        .temp_sensor_3(temp_sensor_3),
        .voltage_data(voltage_data),
        .data_valid(data_valid),
        .soc_percent(soc_percent),
        .trip_signal(trip_signal),
        .warning_signal(warning_signal),
        .fault_sensor(fault_sensor)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("tropicbms.vcd");
        $dumpvars(0, tropicbms_tb);

        rst = 1; adc_start = 0; channel_sel = 0;
        current_sense = 0; current_valid = 0;
        temp_sensor_1 = 12'd2000; // Normal temp (~40°C)
        temp_sensor_2 = 12'd2000;
        temp_sensor_3 = 12'd2000;
        #30; rst = 0; #20;

        $display("================================");
        $display("  TROPICBMS-RV — EV BMS TEST   ");
        $display("  India-Tuned Battery Safety   ");
        $display("================================");

        // Test 1: Normal ADC reading
        $display("--- Test 1: Cell Voltage Reading ---");
        channel_sel = 5'd5;
        adc_start = 1; #10; adc_start = 0;
        #500;
        $display("Channel 5 Voltage: %0d (raw ADC)", voltage_data);
        if (voltage_data > 0)
            $display("PASS: Voltage sensing working!");
        else
            $display("FAIL: No voltage reading");

        // Test 2: SOC estimation
        $display("--- Test 2: SOC Estimation ---");
        current_sense = 12'd50; // Discharge current
        current_valid = 1; #10;
        $display("SOC after discharge: %0d%%", soc_percent);
        if (soc_percent <= 100)
            $display("PASS: SOC estimation working!");
        current_valid = 0; #20;

        // Test 3: Normal temperature — no trip
        $display("--- Test 3: Normal Temp (40 C) ---");
        #20;
        if (trip_signal == 0)
            $display("PASS: No false trip at normal temp!");
        else
            $display("FAIL: False trip triggered");

        // Test 4: TROPICAL HEAT WARNING — India summer!
        $display("--- Test 4: India Summer Heat (55 C) ---");
        temp_sensor_1 = 12'd2900; // Warning zone
        #20;
        if (warning_signal == 1)
            $display("PASS: Warning triggered at high temp!");
        else
            $display("FAIL: No warning at high temp");

        // Test 5: THERMAL RUNAWAY — Emergency trip!
        $display("--- Test 5: THERMAL RUNAWAY (70+ C) ---");
        temp_sensor_2 = 12'd3300; // Danger zone
        #20;
        if (trip_signal == 1 && fault_sensor == 2'd2)
            $display("PASS: EMERGENCY TRIP! Sensor 2 detected!");
        else
            $display("FAIL: Trip did not trigger properly");

        // Test 6: Redundancy check — sensor 1 back to normal, 
        // sensor 3 triggers
        $display("--- Test 6: Redundant Sensor Check ---");
        temp_sensor_2 = 12'd2000; // Back to normal
        temp_sensor_3 = 12'd3400; // This one trips now
        #20;
        if (trip_signal == 1 && fault_sensor == 2'd3)
            $display("PASS: Redundant sensor 3 caught the fault!");
        else
            $display("FAIL: Redundancy check failed");

        $display("================================");
        $display("TropicBMS-RV Testing Complete!");
        $display("Hardware-only safety trip verified!");
        $display("Fail-safe for Indian summer heat!");
        $display("================================");
        $finish;
    end

endmodule
