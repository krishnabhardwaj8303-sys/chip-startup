module confidence_estimator_tb;

    reg         clk, rst, sample_valid;
    reg  signed [7:0] a0, a1, a2, a3;
    wire         low_confidence, dust_fog_signature;
    wire [2:0]   saturated_count;

    confidence_estimator DUT (
        .clk(clk), .rst(rst),
        .sample_valid(sample_valid),
        .a_in0(a0), .a_in1(a1), .a_in2(a2), .a_in3(a3),
        .low_confidence(low_confidence),
        .saturated_count(saturated_count),
        .dust_fog_signature(dust_fog_signature)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("confidence.vcd");
        $dumpvars(0, confidence_estimator_tb);

        rst = 1; sample_valid = 0; a0=0; a1=0; a2=0; a3=0;
        #20; rst = 0; #10;

        $display("================================");
        $display("  LAGHU-NPU CONFIDENCE ESTIMATOR");
        $display("  Unique: Dust/Fog robustness    ");
        $display("================================");

        // ── TEST 1: Clean image data — normal varied values ──
        $display("--- Test 1: Clean Image (Normal Crop Row Data) ---");
        a0 = 8'sd45; a1 = 8'sd52; a2 = 8'sd38; a3 = 8'sd60;
        sample_valid = 1; #10; sample_valid = 0; #10;
        $display("Values: %0d %0d %0d %0d | Saturated=%0d | LowConf=%0d",
                  a0, a1, a2, a3, saturated_count, low_confidence);
        if (low_confidence == 0)
            $display("PASS: Clean data correctly shows HIGH confidence!");
        else
            $display("FAIL: False low-confidence on clean data");

        // ── TEST 2: One channel saturated (normal — bright sky pixel) ──
        $display("--- Test 2: One Saturated Channel (Normal Bright Spot) ---");
        a0 = 8'sd127; a1 = 8'sd50; a2 = 8'sd40; a3 = 8'sd35;
        sample_valid = 1; #10; sample_valid = 0; #10;
        $display("Values: %0d %0d %0d %0d | Saturated=%0d | LowConf=%0d",
                  a0, a1, a2, a3, saturated_count, low_confidence);
        if (low_confidence == 0)
            $display("PASS: Single saturation (normal bright object) not flagged!");
        else
            $display("FAIL: Over-sensitive - false alarm on normal bright pixel");

        // ── TEST 3: DUST/FOG SIGNATURE — multiple simultaneous saturation ──
        $display("--- Test 3: Dust Storm Signature (Multi-Channel Saturation!) ---");
        a0 = 8'sd127; a1 = 8'sd127; a2 = -8'sd128; a3 = 8'sd40;
        sample_valid = 1; #10; sample_valid = 0; #10;
        $display("Values: %0d %0d %0d %0d | Saturated=%0d | LowConf=%0d",
                  a0, a1, a2, a3, saturated_count, low_confidence);
        if (low_confidence == 1 && dust_fog_signature == 1)
            $display("PASS: Dust/fog corruption pattern correctly detected!");
        else
            $display("FAIL: Missed the corruption signature - CRITICAL!");

        // ── TEST 4: Fog signature — all channels near saturation ──
        $display("--- Test 4: Heavy Fog (Near-Uniform High Values) ---");
        a0 = 8'sd127; a1 = -8'sd128; a2 = 8'sd127; a3 = -8'sd128;
        sample_valid = 1; #10; sample_valid = 0; #10;
        $display("Values: %0d %0d %0d %0d | Saturated=%0d | LowConf=%0d",
                  a0, a1, a2, a3, saturated_count, low_confidence);
        if (low_confidence == 1)
            $display("PASS: Complete sensor blinding correctly flagged!");
        else
            $display("FAIL: Total corruption missed!");

        $display("================================");
        $display("Confidence Estimator Complete!");
        $display("NPU now flags unreliable input,");
        $display("instead of silent wrong predictions!");
        $display("================================");
        $finish;
    end
endmodule
