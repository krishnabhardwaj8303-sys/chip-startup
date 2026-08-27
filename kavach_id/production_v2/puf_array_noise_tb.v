module puf_array_noise_tb;

    reg         clk, rst, pulse_in;
    reg  [31:0] challenge;
    wire [31:0] response;

    puf_array #(.CHIP_SEED(32'hAAAA1111)) CHIP_A (
        .clk(clk), .rst(rst),
        .pulse_in(pulse_in), .challenge(challenge),
        .response(response)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    task do_pulse;
        begin
            pulse_in = 1; @(posedge clk); #1;
            pulse_in = 0; @(posedge clk); #1;
        end
    endtask

    integer i, b;
    reg [31:0] first_resp, this_resp;
    integer bit_diff_count;
    integer total_diffs, max_diffs;

    initial begin
        rst = 1; pulse_in = 0; challenge = 32'hDEADBEEF;
        @(posedge clk); #1;
        rst = 0;

        do_pulse;
        first_resp = response;
        $display("First read: 0x%08h", first_resp);

        total_diffs = 0; max_diffs = 0;
        for (i = 0; i < 20; i = i + 1) begin
            do_pulse;
            this_resp = response;
            bit_diff_count = 0;
            for (b = 0; b < 32; b = b + 1)
                if (this_resp[b] !== first_resp[b]) bit_diff_count = bit_diff_count + 1;
            $display("Repeat %0d: 0x%08h  (bits differing from first read: %0d/32)",
                       i, this_resp, bit_diff_count);
            total_diffs = total_diffs + bit_diff_count;
            if (bit_diff_count > max_diffs) max_diffs = bit_diff_count;
        end
        $display("Average bit-differences per read: %0d/32 (%0.1f%%)",
                   total_diffs / 20, (total_diffs * 100.0) / (20*32));
        $display("Max bit-differences in any single read: %0d/32", max_diffs);

        $finish;
    end
endmodule
