module puf_array_tb;

    reg         clk, rst, pulse_in;
    reg  [31:0] challenge;
    wire [31:0] response_chipA, response_chipB;

    puf_array #(.CHIP_SEED(32'hAAAA1111)) CHIP_A (
        .clk(clk), .rst(rst),
        .pulse_in(pulse_in), .challenge(challenge),
        .response(response_chipA)
    );

    puf_array #(.CHIP_SEED(32'hBBBB2222)) CHIP_B (
        .clk(clk), .rst(rst),
        .pulse_in(pulse_in), .challenge(challenge),
        .response(response_chipB)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    task do_pulse;
        begin
            pulse_in = 1; @(posedge clk); #1;
            pulse_in = 0; @(posedge clk); #1;
        end
    endtask

    integer i;
    reg [31:0] test_challenges [0:7];
    reg [31:0] resp_a, resp_b;
    integer distinct_a, zero_a_count, distinct_b_count;
    reg [31:0] first_resp_a;

    initial begin
        rst = 1; pulse_in = 0; challenge = 0;
        @(posedge clk); #1;
        rst = 0;

        test_challenges[0] = 32'hDEADBEEF;
        test_challenges[1] = 32'h12345678;
        test_challenges[2] = 32'hFFFFFFFF;
        test_challenges[3] = 32'h00000000;
        test_challenges[4] = 32'hCAFEBABE;
        test_challenges[5] = 32'hA5A5A5A5;
        test_challenges[6] = 32'h5A5A5A5A;
        test_challenges[7] = 32'h13579BDF;

        $display("--- Test 1: response is NOT stuck at zero (the original bug) ---");
        zero_a_count = 0;
        for (i = 0; i < 8; i = i + 1) begin
            challenge = test_challenges[i];
            do_pulse;
            resp_a = response_chipA;
            $display("challenge=0x%08h -> chipA response=0x%08h", challenge, resp_a);
            if (resp_a == 32'h00000000) zero_a_count = zero_a_count + 1;
        end
        if (zero_a_count < 8)
            $display("PASS: not every challenge produced an all-zero response!");
        else
            $display("FAIL: STILL always zero - bug not fixed");

        $display("--- Test 2: chipA vs chipB - different CHIP_SEED gives different responses ---");
        distinct_b_count = 0;
        for (i = 0; i < 8; i = i + 1) begin
            challenge = test_challenges[i];
            do_pulse;
            resp_a = response_chipA;
            resp_b = response_chipB;
            $display("challenge=0x%08h -> chipA=0x%08h  chipB=0x%08h  %s",
                       challenge, resp_a, resp_b, (resp_a != resp_b) ? "DIFFERENT" : "same");
            if (resp_a != resp_b) distinct_b_count = distinct_b_count + 1;
        end
        $display("Distinct chipA/chipB responses: %0d out of 8", distinct_b_count);
        if (distinct_b_count > 0)
            $display("PASS: different CHIP_SEED produces different responses (chip uniqueness proxy works)!");
        else
            $display("FAIL: chipA and chipB always identical - CHIP_SEED not affecting output");

        $display("--- Test 3: chipA repeatability - same challenge, repeated reads ---");
        challenge = 32'hDEADBEEF;
        do_pulse;
        first_resp_a = response_chipA;
        distinct_a = 0;
        for (i = 0; i < 5; i = i + 1) begin
            do_pulse;
            if (response_chipA !== first_resp_a) distinct_a = distinct_a + 1;
        end
        $display("chipA response to repeated same challenge: first=0x%08h, differing repeats=%0d/5",
                   first_resp_a, distinct_a);
        // Some bits may be near-tie and flip occasionally - that's expected,
        // not a full-response mismatch every time.

        $display("--- Test 4: response varies across DIVERSE challenges (not just alternating 2 values) ---");
        begin : diversity
            reg [31:0] all_responses [0:7];
            integer all_same;
            all_same = 1;
            for (i = 0; i < 8; i = i + 1) begin
                challenge = test_challenges[i];
                do_pulse;
                all_responses[i] = response_chipA;
            end
            for (i = 1; i < 8; i = i + 1) begin
                if (all_responses[i] !== all_responses[0]) all_same = 0;
            end
            if (all_same == 0)
                $display("PASS: response varies across diverse challenges (not stuck at one constant value)!");
            else
                $display("FAIL: response identical across ALL diverse challenges");
        end

        $finish;
    end
endmodule
