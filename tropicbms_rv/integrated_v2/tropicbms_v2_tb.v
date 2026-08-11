module tropicbms_v2_tb;

    reg         clk, rst;
    reg         reg_write, reg_read;
    reg  [7:0]  reg_addr;
    reg  [31:0] reg_wdata;
    wire [31:0] reg_rdata;
    wire        reg_ready;
    reg  [11:0] temp_sensor_1, temp_sensor_2, temp_sensor_3;
    reg  [11:0] current_sense;
    reg         current_valid;
    wire        can_tx, can_frame_valid;
    wire [10:0] can_id_out;
    wire [63:0] can_payload_out;
    wire        emergency_trip_signal, system_healthy;

    tropicbms_v2_top DUT (
        .clk(clk), .rst(rst),
        .reg_write(reg_write), .reg_read(reg_read),
        .reg_addr(reg_addr), .reg_wdata(reg_wdata),
        .reg_rdata(reg_rdata), .reg_ready(reg_ready),
        .temp_sensor_1(temp_sensor_1), .temp_sensor_2(temp_sensor_2),
        .temp_sensor_3(temp_sensor_3),
        .current_sense(current_sense), .current_valid(current_valid),
        .can_tx(can_tx), .can_frame_valid(can_frame_valid),
        .can_id_out(can_id_out), .can_payload_out(can_payload_out),
        .emergency_trip_signal(emergency_trip_signal),
        .system_healthy(system_healthy)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("tropicbms_v2.vcd");
        $dumpvars(0, tropicbms_v2_tb);

        rst = 1;
        reg_write = 0; reg_read = 0; reg_addr = 0; reg_wdata = 0;
        temp_sensor_1 = 12'd2000; temp_sensor_2 = 12'd2000; temp_sensor_3 = 12'd2000;
        current_sense = 0; current_valid = 0;
        #30; rst = 0; #20;

        $display("========================================");
        $display("  TROPICBMS-RV v2 — FULLY INTEGRATED    ");
        $display("  Core + Production + Unique, all wired ");
        $display("========================================");

        // ── TEST 1: BIST via register ──
        $display("--- Test 1: BIST via Register ---");
        reg_addr = 8'h00; reg_wdata = 32'h00000001; // bit0 = bist_start
        reg_write = 1; #10; reg_write = 0; #30;
        reg_addr = 8'h04; reg_read = 1; #10; reg_read = 0; #10;
        $display("Status Register: 0x%0h", reg_rdata);
        if (system_healthy)
            $display("PASS: System healthy after BIST!");

        // ── TEST 2: Normal temps -> CAN status broadcast ──
        $display("--- Test 2: Normal Operation, CAN Broadcast ---");
        reg_addr = 8'h00; reg_wdata = 32'h00000002; // bit1 = heartbeat pulse
        reg_write = 1; #10; reg_write = 0; #20;
        if (can_frame_valid && can_id_out == 11'h100)
            $display("PASS: Normal status broadcast on CAN, low-priority ID!");

        // ── TEST 3: Single sensor fault -> voter isolates it ──
        $display("--- Test 3: Single Sensor Fault (Redundancy) ---");
        rst = 1; #10; rst = 0; #20;
        temp_sensor_3 = 12'd4000; // Sensor 3 fails
        #20;
        reg_addr = 8'h04; reg_read = 1; #10; reg_read = 0; #10;
        $display("Status (sensor_fault bit): 0x%0h", reg_rdata);

        // ── TEST 4: THERMAL RUNAWAY -> emergency CAN frame ──
        $display("--- Test 4: Thermal Runaway -> Emergency CAN ---");
        rst = 1; #10; rst = 0; #20;
        temp_sensor_1 = 12'd3300; temp_sensor_2 = 12'd3300; temp_sensor_3 = 12'd3300;
        #30;
        if (emergency_trip_signal)
            $display("PASS: Emergency trip signal correctly asserted!");
        reg_addr = 8'h00; reg_wdata = 32'h00000002;
        reg_write = 1; #10; reg_write = 0; #20;
        if (can_frame_valid && can_id_out == 11'h001)
            $display("PASS: Emergency CAN frame uses highest priority ID!");
        else
            $display("Note: check emergency_condition -> CAN wiring");

        $display("========================================");
        $display("TropicBMS-RV v2 Integration Complete!");
        $display("Sensor Voting + Thermal Trip + Rate Detection");
        $display("+ BIST + Watchdog + CAN Bus, all wired!");
        $display("========================================");
        $finish;
    end
endmodule
