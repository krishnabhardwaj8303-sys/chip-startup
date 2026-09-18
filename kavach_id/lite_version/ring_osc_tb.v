module ring_osc_tb;

    reg  enable;
    wire clk_out;

    ring_oscillator #(.HALF_PERIOD(1)) DUT (
        .enable(enable),
        .clk_out(clk_out)
    );

    integer edge_count;

    always @(posedge clk_out) begin
        edge_count = edge_count + 1;
        $display("[t=%0t] rising edge #%0d", $time, edge_count);
    end

    initial begin
        enable = 0;
        edge_count = 0;

        $display("=== TEST 1: disabled - clk_out must stay flat ===");
        #50;
        $display("After 50 time units disabled: clk_out=%0b edge_count=%0d (expect 0)", clk_out, edge_count);
        if (edge_count == 0)
            $display("PASS: no oscillation while disabled");
        else
            $display("FAIL");

        $display("=== TEST 2: enabled - clk_out must oscillate ===");
        enable = 1;
        #50;
        $display("After 50 time units enabled: edge_count=%0d (expect >= 10, continuous oscillation)", edge_count);
        if (edge_count >= 10)
            $display("PASS: oscillation observed when enabled");
        else
            $display("FAIL");

        $display("=== TEST 3: disable again - oscillation must stop ===");
        enable = 0;
        edge_count = 0;
        #50;
        $display("After disabling again: edge_count=%0d (expect 0)", edge_count);
        if (edge_count == 0)
            $display("PASS: oscillation correctly stops when disabled");
        else
            $display("FAIL");

        $finish;
    end
endmodule
