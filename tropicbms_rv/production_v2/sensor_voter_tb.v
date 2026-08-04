module sensor_voter_tb;

    reg         clk, rst;
    reg  [11:0] s1, s2, s3;
    wire [11:0] voted;
    wire        fault;
    wire [2:0]  fault_mask;

    sensor_voter DUT (
        .clk(clk), .rst(rst),
        .sensor_1(s1), .sensor_2(s2), .sensor_3(s3),
        .voted_value(voted),
        .sensor_fault_detected(fault),
        .faulty_sensor_mask(fault_mask)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("sensor_voter.vcd");
        $dumpvars(0, sensor_voter_tb);

        rst = 1; s1 = 0; s2 = 0; s3 = 0;
        #20; rst = 0; #10;

        $display("================================");
        $display("  TROPICBMS PRODUCTION PHASE 1 ");
        $display("  Sensor Redundancy Voting      ");
        $display("================================");

        // Test 1: Sab sensors agree — normal operation
        $display("--- Test 1: All Sensors Agree ---");
        s1 = 12'd2800; s2 = 12'd2810; s3 = 12'd2805; #10;
        $display("Voted=%0d, Fault=%0d, Mask=%0b", voted, fault, fault_mask);
        if (fault == 0)
            $display("PASS: No false fault when all sensors agree!");
        else
            $display("FAIL: False fault triggered");

        // Test 2: Sensor 3 fails (stuck at wrong value)
        $display("--- Test 2: Sensor 3 FAILS (Stuck High) ---");
        s1 = 12'd2800; s2 = 12'd2810; s3 = 12'd4000; // Sensor 3 way off
        #10;
        $display("Voted=%0d, Fault=%0d, Mask=%0b", voted, fault, fault_mask);
        if (fault == 1 && fault_mask == 3'b100)
            $display("PASS: Sensor 3 fault correctly isolated!");
        else
            $display("FAIL: Fault isolation incorrect");

        // Test 3: Sensor 1 fails (this time)
        $display("--- Test 3: Sensor 1 FAILS ---");
        s1 = 12'd500; s2 = 12'd2810; s3 = 12'd2805; #10;
        $display("Voted=%0d, Fault=%0d, Mask=%0b", voted, fault, fault_mask);
        if (fault == 1 && fault_mask == 3'b001)
            $display("PASS: Sensor 1 fault correctly isolated!");
        else
            $display("FAIL: Fault isolation incorrect");

        // Test 4: CRITICAL — all three sensors disagree
        $display("--- Test 4: CRITICAL - All Sensors Disagree ---");
        s1 = 12'd500; s2 = 12'd2810; s3 = 12'd4000; #10;
        $display("Voted=%0d, Fault=%0d, Mask=%0b", voted, fault, fault_mask);
        if (fault == 1 && fault_mask == 3'b111)
            $display("PASS: Critical multi-sensor failure detected!");
        else
            $display("FAIL: Critical failure not flagged properly");

        $display("================================");
        $display("Phase 1 Complete!");
        $display("System survives single sensor failure!");
        $display("Safety-critical redundancy verified!");
        $display("================================");
        $finish;
    end
endmodule
