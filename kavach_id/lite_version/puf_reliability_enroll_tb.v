module puf_reliability_enroll_tb;

    reg         clk, rst, enroll_start, stable_sample_valid;
    reg  [31:0] stable_sample;
    wire        enroll_busy, enroll_done, mask_locked;
    wire [31:0] reliability_mask;

    puf_reliability_enroll #(.ENROLL_ROUNDS(4'd8)) DUT (
        .clk(clk), .rst(rst),
        .enroll_start(enroll_start),
        .stable_sample_valid(stable_sample_valid),
        .stable_sample(stable_sample),
        .enroll_busy(enroll_busy),
        .enroll_done(enroll_done),
        .reliability_mask(reliability_mask),
        .mask_locked(mask_locked)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    task feed_round(input [31:0] sample);
        begin
            stable_sample = sample;
            stable_sample_valid = 1;
            @(posedge clk); #1;
            stable_sample_valid = 0;
            @(posedge clk); #1;
        end
    endtask

    initial begin
        rst = 1; enroll_start = 0; stable_sample_valid = 0; stable_sample = 0;
        @(posedge clk); #1;
        rst = 0;

        $display("--- Test 1: 8 rounds, bits 1 and 17 flip, rest stable (mirrors real puf_bitcheck_tb.v findings) ---");
        enroll_start = 1;
        @(posedge clk); #1;
        enroll_start = 0;

        feed_round(32'h48ACBBA5); // bit1=0, bit17=0
        feed_round(32'h48AEBBA7); // bit1=1, bit17=1
        feed_round(32'h48ACBBA7); // bit1=1, bit17=0
        feed_round(32'h48AEBBA5); // bit1=0, bit17=1
        feed_round(32'h48ACBBA5);
        feed_round(32'h48AEBBA7);
        feed_round(32'h48ACBBA7);
        feed_round(32'h48AEBBA5);

        wait (enroll_done == 1);
        #1;
        $display("reliability_mask=0x%08h  mask_locked=%0d", reliability_mask, mask_locked);
        if (reliability_mask[1] == 1 && reliability_mask[17] == 1)
            $display("PASS: bits 1 and 17 correctly flagged unreliable!");
        else
            $display("FAIL: expected bits 1,17 flagged, got mask=0x%08h", reliability_mask);

        begin : count_check
            integer set_bits, b;
            set_bits = 0;
            for (b = 0; b < 32; b = b + 1)
                if (reliability_mask[b]) set_bits = set_bits + 1;
            $display("Total bits flagged unreliable: %0d (expect exactly 2)", set_bits);
            if (set_bits == 2)
                $display("PASS: exactly the 2 known-noisy bits flagged, no false positives!");
            else
                $display("FAIL: expected exactly 2 flagged bits");
        end

        if (mask_locked == 1)
            $display("PASS: mask_locked correctly set after enrollment!");
        else
            $display("FAIL: mask_locked not set");

        $display("--- Test 2: re-enrollment attempt after lock must be ignored ---");
        enroll_start = 1;
        @(posedge clk); #1;
        enroll_start = 0;
        repeat (5) @(posedge clk);
        if (enroll_busy == 0)
            $display("PASS: locked module ignored the re-enrollment request (enroll_busy never asserted)!");
        else
            $display("FAIL: SECURITY BUG - re-enrollment started on an already-locked mask");

        $display("--- Test 3: reset allows re-enrollment (fresh chip / test-rig reuse) ---");
        rst = 1; #10; rst = 0; #10;
        if (mask_locked == 0 && reliability_mask == 32'h0)
            $display("PASS: reset correctly cleared mask and lock!");
        else
            $display("FAIL: reset did not clear enrollment state");

        $finish;
    end
endmodule
