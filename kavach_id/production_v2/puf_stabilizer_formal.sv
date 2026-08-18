module puf_stabilizer_formal(
    input wire clk,
    input wire rst,
    input wire start,
    input wire [31:0] raw_response_1,
    input wire [31:0] raw_response_2,
    input wire [31:0] raw_response_3
);
    wire [31:0] stable_response;
    wire [31:0] unstable_bit_mask;
    wire        stable_done;
    wire [5:0]  unstable_bit_count;

    puf_stabilizer dut (
        .clk(clk), .rst(rst), .start(start),
        .raw_response_1(raw_response_1),
        .raw_response_2(raw_response_2),
        .raw_response_3(raw_response_3),
        .stable_response(stable_response),
        .unstable_bit_mask(unstable_bit_mask),
        .stable_done(stable_done),
        .unstable_bit_count(unstable_bit_count)
    );

    initial assume (rst);

    // ── PROPERTY: majority vote is correct for EVERY bit position ──
    // $past() must be evaluated inside a clocked always block - moved
    // the whole majority computation inline into the assert itself
    // (rather than a continuous-assignment wire) to satisfy that
    // requirement.
    genvar i;
    generate
        for (i = 0; i < 32; i = i + 1) begin : bitcheck
            always @(posedge clk) begin
                if (!rst && $past(1'b1) && !$past(rst) && $past(start))
                    assert (stable_response[i] ==
                        (($past(raw_response_1[i]) & $past(raw_response_2[i])) |
                         ($past(raw_response_2[i]) & $past(raw_response_3[i])) |
                         ($past(raw_response_1[i]) & $past(raw_response_3[i]))));
            end
        end
    endgenerate

    // ── PROPERTY: perfect agreement -> zero unstable bits ──
    always @(posedge clk) begin
        if (!rst && $past(1'b1) && !$past(rst) && $past(start) &&
            $past(raw_response_1) == $past(raw_response_2) &&
            $past(raw_response_2) == $past(raw_response_3))
            assert (unstable_bit_count == 6'd0);
    end

    always @(posedge clk) cover(stable_done);
endmodule
