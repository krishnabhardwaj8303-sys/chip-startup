module can_lite_tb;

    reg         clk, rst;
    reg  [7:0]  soc_percent;
    reg  [11:0] voted_temp;
    reg          trip_signal, sensor_fault;
    reg          broadcast_trigger, emergency_trip;
    wire         can_tx, can_frame_valid;
    wire [10:0]  can_id_out;
    wire [63:0]  can_payload_out;

    can_lite_controller DUT (
        .clk(clk), .rst(rst),
        .soc_percent(soc_percent),
        .voted_temp(voted_temp),
        .trip_signal(trip_signal),
        .sensor_fault(sensor_fault),
        .broadcast_trigger(broadcast_trigger),
        .can_tx(can_tx),
        .can_frame_valid(can_frame_valid),
        .can_id_out(can_id_out),
        .can_payload_out(can_payload_out),
        .emergency_trip(emergency_trip)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("can_lite.vcd");
        $dumpvars(0, can_lite_tb);

        rst = 1; soc_percent = 0; voted_temp = 0;
        trip_signal = 0; sensor_fault = 0;
        broadcast_trigger = 0; emergency_trip = 0;
        #20; rst = 0; #10;

        $display("================================");
        $display("  TROPICBMS CAN-LITE INTERFACE ");
        $display("  Vehicle bus communication link");
        $display("================================");

        // ── TEST 1: Normal periodic status broadcast ──
        $display("--- Test 1: Normal Status Broadcast ---");
        soc_percent = 8'd85; voted_temp = 12'd2800;
        trip_signal = 0; sensor_fault = 0;
        broadcast_trigger = 1; #10; broadcast_trigger = 0; #10;

        wait(can_frame_valid);
        $display("CAN ID: 0x%0h (should be low-priority status ID)", 
                  can_id_out);
        $display("Payload: 0x%0h", can_payload_out);
        if (can_id_out == 11'h100 && can_payload_out[7:0] == 8'd85)
            $display("PASS: Normal status frame built correctly with SOC!");
        else
            $display("FAIL: Status frame incorrect");
        #20;

        // ── TEST 2: Emergency trip gets HIGHEST priority ID ──
        $display("--- Test 2: Emergency Trip - Highest Priority ---");
        rst = 1; #10; rst = 0; #10;
        trip_signal = 1;
        emergency_trip = 1; #10; emergency_trip = 0; #10;

        wait(can_frame_valid);
        $display("CAN ID: 0x%0h (should be 0x001 - highest priority)", 
                  can_id_out);
        if (can_id_out == 11'h001)
            $display("PASS: Emergency frame uses highest-priority CAN ID!");
        else
            $display("FAIL: Emergency did not get priority ID");

        // ── TEST 3: Emergency jumps ahead of pending normal broadcast ──
        $display("--- Test 3: Emergency Preempts Normal Broadcast ---");
        rst = 1; #10; rst = 0; #10;
        broadcast_trigger = 1; // Normal broadcast requested
        emergency_trip = 1;    // But emergency happens same cycle!
        #10; broadcast_trigger = 0; emergency_trip = 0; #10;

        wait(can_frame_valid);
        if (can_id_out == 11'h001)
            $display("PASS: Emergency correctly preempted normal status!");
        else
            $display("FAIL: Normal broadcast sent instead of emergency!");

        $display("================================");
        $display("CAN-Lite Interface Complete!");
        $display("BMS can now talk to vehicle bus!");
        $display("Emergency frames get bus priority!");
        $display("================================");
        $finish;
    end
endmodule
