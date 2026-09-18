module ring_osc_tb2;

    reg  enable;
    wire clk_out;

    ring_oscillator #(.HALF_PERIOD(1)) DUT (
        .enable(enable),
        .clk_out(clk_out)
    );

    initial begin
        $display("[t=%0t] clk_out=%0b enable=%0b", $time, clk_out, enable);
    end

    always @(clk_out) begin
        $display("[t=%0t] clk_out CHANGED to %0b", $time, clk_out);
    end

    initial begin
        enable = 0;
        #10;
        $display("=== Enabling at t=10 ===");
        enable = 1;
        #30;
        $display("=== Done observing at t=40 ===");
        $finish;
    end
endmodule
