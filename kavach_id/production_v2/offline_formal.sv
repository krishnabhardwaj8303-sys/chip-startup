module offline_formal(
    input wire clk,
    input wire rst,
    input wire verify_request,
    input wire sync_complete
);
    wire [7:0]  offline_budget;
    wire         verify_allowed;
    wire         sync_required;
    wire [15:0]  total_offline_uses;

    offline_verify_counter dut (
        .clk(clk), .rst(rst),
        .verify_request(verify_request),
        .sync_complete(sync_complete),
        .offline_budget(offline_budget),
        .verify_allowed(verify_allowed),
        .sync_required(sync_required),
        .total_offline_uses(total_offline_uses)
    );

    initial assume (rst);

    // ── PROPERTY 1 (corrected): a grant must have been backed by a
    // non-zero budget AT THE TIME the decision was made. verify_allowed
    // and offline_budget are both registered from the SAME decision, so
    // comparing verify_allowed against the CURRENT (post-decrement)
    // offline_budget is a cycle-alignment mismatch - the last legitimate
    // use correctly shows budget=0 alongside allowed=1 in the same
    // observed cycle. The real invariant is against $past(offline_budget)
    // - the budget that existed BEFORE this decision.
    always @(posedge clk) begin
        if (!rst && $past(1'b1) && !$past(rst))
            assert (!verify_allowed || $past(offline_budget) > 8'd0);
    end

    // ── PROPERTY 2: budget can never exceed the factory-provisioned max ──
    always @(posedge clk) begin
        if (!rst)
            assert (offline_budget <= 8'd50);
    end

    always @(posedge clk) cover(verify_allowed);
    always @(posedge clk) cover(sync_required);
endmodule
