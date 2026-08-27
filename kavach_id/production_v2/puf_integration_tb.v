module puf_integration_tb;

    reg         clk, rst;
    reg  [31:0] challenge;
    reg         pulse_in;
    wire [31:0] puf_response;

    puf_array #(.CHIP_SEED(32'hAAAA1111)) PUF (
        .clk(clk), .rst(rst),
        .pulse_in(pulse_in), .challenge(challenge),
        .response(puf_response)
    );

    reg  [31:0] sample_1, sample_2, sample_3;
    reg         stab_start;
    wire [31:0] stable_response;
    wire [31:0] unstable_bit_mask;
    wire        stable_done;
    wire [5:0]  unstable_bit_count;

    puf_stabilizer STAB (
        .clk(clk), .rst(rst),
        .start(stab_start),
        .raw_response_1(sample_1),
        .raw_response_2(sample_2),
        .raw_response_3(sample_3),
        .stable_response(stable_response),
        .unstable_bit_mask(unstable_bit_mask),
        .stable_done(stable_done),
        .unstable_bit_count(unstable_bit_count)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    task do_pulse;
        begin
            pulse_in = 1; @(posedge clk); #1;
            pulse_in = 0; @(posedge clk); #1;
        end
    endtask

    integer trial, mismatch_count;
    reg [31:0] majority_ref;

    initial begin
        rst = 1; pulse_in = 0; challenge = 0; stab_start = 0;
        sample_1 = 0; sample_2 = 0; sample_3 = 0;
        @(posedge clk); #1;
        rst = 0;

        $display("--- Full pipeline: PUF resample x3 -> stabilizer majority vote ---");
        mismatch_count = 0;

        for (trial = 0; trial < 10; trial = trial + 1) begin
            challenge = 32'hDEADBEEF + trial; // slightly different challenge each trial

            do_pulse; sample_1 = puf_response;
            do_pulse; sample_2 = puf_response;
            do_pulse; sample_3 = puf_response;

            stab_start = 1;
            @(posedge clk); #1;
            stab_start = 0;
            wait (stable_done == 1);
            #1;

            $display("Trial %0d: challenge=0x%08h  s1=0x%08h s2=0x%08h s3=0x%08h -> stable=0x%08h  unstable_bits=%0d",
                       trial, challenge, sample_1, sample_2, sample_3, stable_response, unstable_bit_count);

            // Sanity: stable_response should equal the majority of the 3
            // samples on every bit - verify this independently in the TB.
            majority_ref = (sample_1 & sample_2) | (sample_2 & sample_3) | (sample_1 & sample_3);
            if (stable_response !== majority_ref) begin
                $display("  MISMATCH: stable_response does not equal independently-computed majority vote!");
                mismatch_count = mismatch_count + 1;
            end
        end

        if (mismatch_count == 0)
            $display("PASS: stable_response matched the independently-computed majority vote on all 10 trials!");
        else
            $display("FAIL: %0d/10 trials had a majority-vote mismatch", mismatch_count);

        $display("--- Repeatability check: SAME challenge across trials, does stabilizer output stay consistent? ---");
        begin : repeat_check
            reg [31:0] first_stable;
            integer stable_mismatches;
            challenge = 32'hCAFED00D;
            stable_mismatches = 0;

            do_pulse; sample_1 = puf_response;
            do_pulse; sample_2 = puf_response;
            do_pulse; sample_3 = puf_response;
            stab_start = 1; @(posedge clk); #1; stab_start = 0;
            wait (stable_done == 1); #1;
            first_stable = stable_response;
            $display("Reference stable_response for 0xCAFED00D: 0x%08h (unstable_bits=%0d)", first_stable, unstable_bit_count);

            for (trial = 0; trial < 5; trial = trial + 1) begin
                do_pulse; sample_1 = puf_response;
                do_pulse; sample_2 = puf_response;
                do_pulse; sample_3 = puf_response;
                stab_start = 1; @(posedge clk); #1; stab_start = 0;
                wait (stable_done == 1); #1;
                $display("  Repeat %0d: stable=0x%08h  unstable_bits=%0d  %s",
                           trial, stable_response, unstable_bit_count,
                           (stable_response === first_stable) ? "MATCH" : "DIFFERS");
                if (stable_response !== first_stable) stable_mismatches = stable_mismatches + 1;
            end
            $display("Stabilized-response mismatches across 5 repeats of the SAME challenge: %0d/5", stable_mismatches);
            if (stable_mismatches == 0)
                $display("PASS: stabilizer fully corrected the raw PUF noise for this challenge across all repeats!");
            else
                $display("NOTE: %0d/5 repeats still differed after stabilization - majority vote didn't fully suppress noise on this particular challenge (worth investigating if this is common)", stable_mismatches);
        end

        $finish;
    end
endmodule
