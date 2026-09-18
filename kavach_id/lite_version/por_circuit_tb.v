module por_circuit_tb;

    reg  clk;
    wire por_reset;

    por_circuit #(.POR_CYCLES(8)) DUT (
        .clk(clk),
        .por_reset(por_reset)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    integer i;

    initial begin
        $display("=== TEST 1: por_reset must be asserted immediately at power-up ===");
        $display("At t=0, por_reset=%0b (expect 1)", por_reset);
        if (por_reset == 1'b1)
            $display("PASS: reset asserted at power-up with no external trigger");
        else
            $display("FAIL");

        $display("=== TEST 2: por_reset must stay asserted for POR_CYCLES clock edges ===");
        for (i = 0; i < 7; i = i + 1) begin
            @(posedge clk);
            if (por_reset != 1'b1) begin
                $display("FAIL: por_reset released too early, at cycle %0d", i+1);
            end
        end
        $display("After 7 clock edges, por_reset=%0b (expect still 1)", por_reset);
        if (por_reset == 1'b1)
            $display("PASS: reset held for full duration");
        else
            $display("FAIL");

        $display("=== TEST 3: por_reset must release after POR_CYCLES ===");
        repeat (5) @(posedge clk);
        $display("After additional cycles, por_reset=%0b (expect 0)", por_reset);
        if (por_reset == 1'b0)
            $display("PASS: reset correctly released");
        else
            $display("FAIL");

        $display("=== TEST 4: por_reset must NEVER re-assert on its own (one-shot) ===");
        repeat (20) @(posedge clk);
        $display("After 20 more cycles, por_reset=%0b (expect still 0)", por_reset);
        if (por_reset == 1'b0)
            $display("PASS: reset stays released, no spurious re-trigger");
        else
            $display("FAIL");

        $finish;
    end
endmodule
