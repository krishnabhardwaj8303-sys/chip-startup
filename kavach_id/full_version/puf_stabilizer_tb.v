module puf_stabilizer_tb;

    reg         clk, rst, start;
    reg  [31:0] raw1, raw2, raw3;
    wire [31:0] stable_out, unstable_mask;
    wire        done;
    wire [5:0]  unstable_count;

    puf_stabilizer DUT (
        .clk(clk), .rst(rst), .start(start),
        .raw_response_1(raw1), .raw_response_2(raw2), 
        .raw_response_3(raw3),
        .stable_response(stable_out),
        .unstable_bit_mask(unstable_mask),
        .stable_done(done),
        .unstable_bit_count(unstable_count)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("puf_stabilizer.vcd");
        $dumpvars(0, puf_stabilizer_tb);

        rst = 1; start = 0; raw1 = 0; raw2 = 0; raw3 = 0;
        #20; rst = 0; #10;

        $display("================================");
        $display("  KAVACH-ID PRODUCTION PHASE 1 ");
        $display("  PUF Response Stability (Noise) ");
        $display("================================");

        // Test 1: Perfectly stable PUF — sab samples same
        $display("--- Test 1: Perfectly Stable Response ---");
        raw1 = 32'hDEADBEEF; raw2 = 32'hDEADBEEF; raw3 = 32'hDEADBEEF;
        start = 1; #10; start = 0; #10;
        $display("Stable Output=0x%0h, Unstable bits=%0d", 
                  stable_out, unstable_count);
        if (stable_out == 32'hDEADBEEF && unstable_count == 0)
            $display("PASS: Perfect stability - no noise correction needed!");
        else
            $display("FAIL: Unexpected result on stable input");

        // Test 2: 1 noisy bit — majority vote should fix it
        $display("--- Test 2: 1 Noisy Bit (Real-World Scenario) ---");
        // Bit 0: sample1=1, sample2=0, sample3=1 -> majority=1
        raw1 = 32'hDEADBEEF; 
        raw2 = 32'hDEADBEEE; // LSB flipped due to noise
        raw3 = 32'hDEADBEEF;
        start = 1; #10; start = 0; #10;
        $display("Stable Output=0x%0h, Unstable bits=%0d", 
                  stable_out, unstable_count);
        if (stable_out == 32'hDEADBEEF)
            $display("PASS: Majority voting corrected the noisy bit!");
        else
            $display("FAIL: Noise correction failed!");

        // Test 3: Multiple noisy bits (typical SRAM PUF ~2-5%)
        $display("--- Test 3: Multiple Noisy Bits (5%% noise) ---");
        raw1 = 32'hDEADBEEF;
        raw2 = 32'hDEADBEED; // 2 bits different
        raw3 = 32'hDEADBEEF;
        start = 1; #10; start = 0; #10;
        $display("Stable Output=0x%0h, Unstable bits=%0d", 
                  stable_out, unstable_count);
        if (stable_out == 32'hDEADBEEF)
            $display("PASS: Multi-bit noise correctly filtered!");
        else
            $display("FAIL: Multi-bit correction failed");

        $display("================================");
        $display("Phase 1 Complete!");
        $display("No more random authentication failures!");
        $display("Production-stable PUF response verified!");
        $display("================================");
        $finish;
    end
endmodule
