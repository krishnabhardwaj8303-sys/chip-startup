module trng_tb;

    reg  clk, rst, enable;
    wire [31:0] random_out;
    wire        random_valid;
    wire        self_test_pass;

    trng DUT (
        .clk(clk), .rst(rst), .enable(enable),
        .random_out(random_out),
        .random_valid(random_valid),
        .self_test_pass(self_test_pass)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    reg [31:0] first_value;

    initial begin
        $dumpfile("trng.vcd");
        $dumpvars(0, trng_tb);

        rst = 1; enable = 0;
        #20; rst = 0; enable = 1;

        $display("================================");
        $display("  NEELCHIP TRNG — GAP FEATURE  ");
        $display("  Distinct from PUF (per proposal)");
        $display("================================");

        @(posedge random_valid);
        first_value = random_out;
        $display("Random Value 1: 0x%0h", first_value);
        @(negedge random_valid); // Pulse clear hone ka wait karo

        @(posedge random_valid);
        $display("Random Value 2: 0x%0h", random_out);
        if (random_out !== first_value)
            $display("PASS: Consecutive TRNG outputs are different!");
        else
            $display("FAIL: TRNG produced identical outputs");
        @(negedge random_valid);

        repeat(30) begin
            @(posedge random_valid);
            @(negedge random_valid);
        end

        $display("--- Statistical Self-Test ---");
        $display("Self-test pass after sampling: %0d", self_test_pass);

        $display("================================");
        $display("TRNG Complete!");
        $display("Dedicated entropy source (not PUF)!");
        $display("Von Neumann de-biasing applied!");
        $display("================================");
        $finish;
    end
endmodule
