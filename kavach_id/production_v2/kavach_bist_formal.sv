module kavach_bist_formal(
    input wire clk,
    input wire rst,
    input wire start_bist,
    input wire [31:0] test_response
);
    wire bist_pass, bist_fail, bist_done;

    kavach_bist dut (
        .clk(clk), .rst(rst),
        .start_bist(start_bist),
        .bist_pass(bist_pass),
        .bist_fail(bist_fail),
        .bist_done(bist_done),
        .test_response(test_response)
    );

    // Force the very first cycle to be a real reset, so the FSM starts
    // from a known-good state rather than an arbitrary (never-reset)
    // one. Without this, the solver can pick an unconstrained initial
    // register value for `state`/bist_done/bist_pass/bist_fail and
    // "prove" a false counterexample that has no real hardware meaning
    // - the exact class of harness gap already seen in offline_formal.sv.
    initial assume (rst);

    always @(posedge clk) begin
        if (!rst)
            assert (!(bist_pass && bist_fail));
    end

    always @(posedge clk) begin
        if (!rst)
            assert (!bist_done || bist_pass || bist_fail);
    end

    always @(posedge clk) cover(bist_pass);
    always @(posedge clk) cover(bist_fail);
endmodule
