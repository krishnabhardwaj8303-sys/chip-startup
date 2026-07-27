module traffic_light_tb;

    reg  clk, rst;
    wire red, yellow, green;

    traffic_light uut (
        .clk(clk),
        .rst(rst),
        .red(red),
        .yellow(yellow),
        .green(green)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("traffic.vcd");
        $dumpvars(0, traffic_light_tb);

        rst = 1; #20;
        rst = 0;

        // Red check
        #10;
        if (red == 1)
            $display("✓ RED light ON — PASS");
        else
            $display("✗ RED light FAIL");

        // Green tak wait karo
        #80;
        if (green == 1)
            $display("✓ GREEN light ON — PASS");
        else
            $display("✗ GREEN light FAIL");

        // Yellow tak wait karo
        #80;
        if (yellow == 1)
            $display("✓ YELLOW light ON — PASS");
        else
            $display("✗ YELLOW light FAIL");

        $display("Day 2 Complete! FSM working!");
        #100;
        $finish;
    end

endmodule
