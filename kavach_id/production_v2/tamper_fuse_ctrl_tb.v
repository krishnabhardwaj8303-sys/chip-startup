`timescale 1ns/1ps

module tamper_fuse_ctrl_tb;

    reg clk;
    reg rst_n;
    reg continuity_loop_ok;
    wire tamper_fuse_tripped;
    wire auth_block;

    integer pass_count = 0;
    integer fail_count = 0;

    tamper_fuse_ctrl #(.DEBOUNCE_CYCLES(4)) dut (
        .clk               (clk),
        .rst_n             (rst_n),
        .continuity_loop_ok(continuity_loop_ok),
        .tamper_fuse_tripped(tamper_fuse_tripped),
        .auth_block        (auth_block)
    );

    always #5 clk = ~clk;

    task check(input cond, input [639:0] msg);
        begin
            if (cond) begin
                pass_count = pass_count + 1;
                $display("  PASS: %0s", msg);
            end else begin
                fail_count = fail_count + 1;
                $display("  FAIL: %0s", msg);
            end
        end
    endtask

    initial begin
        clk = 0;
        rst_n = 0;
        continuity_loop_ok = 1'b1;
        #12 rst_n = 1;

        $display("Test 1: normal operation, loop intact -> fuse must stay clear");
        repeat (20) @(posedge clk);
        check(tamper_fuse_tripped == 1'b0, "fuse clear during normal operation");
        check(auth_block == 1'b0, "auth_block low during normal operation");

        $display("Test 2: brief glitch (2 cycles, under debounce=4) -> must NOT trip");
        continuity_loop_ok = 1'b0;
        repeat (2) @(posedge clk);
        continuity_loop_ok = 1'b1;
        repeat (10) @(posedge clk);
        check(tamper_fuse_tripped == 1'b0, "short glitch correctly ignored (debounce works)");

        $display("Test 3: sustained break (real desoldering) -> fuse must trip");
        continuity_loop_ok = 1'b0;
        repeat (8) @(posedge clk);
        check(tamper_fuse_tripped == 1'b1, "fuse tripped after sustained continuity break");
        check(auth_block == 1'b1, "auth_block asserted once fuse tripped");

        $display("Test 4: attacker re-solders chip (loop restored) -> fuse must STAY tripped");
        continuity_loop_ok = 1'b1;
        repeat (20) @(posedge clk);
        check(tamper_fuse_tripped == 1'b1, "fuse remains tripped after continuity restored (sticky)");
        check(auth_block == 1'b1, "auth_block remains asserted after continuity restored");

        $display("Test 5: attacker pulses reset, hoping to clear the fuse -> must STILL stay tripped");
        rst_n = 0;
        repeat (5) @(posedge clk);
        rst_n = 1;
        repeat (10) @(posedge clk);
        check(tamper_fuse_tripped == 1'b1, "fuse survives reset attempt (models non-volatile antifuse)");
        check(auth_block == 1'b1, "auth_block still asserted after reset attempt");

        $display("");
        $display("=================================================");
        $display(" RESULT: %0d PASS, %0d FAIL", pass_count, fail_count);
        $display("=================================================");
        if (fail_count == 0)
            $display(" tamper_fuse_ctrl.v: ALL TESTS PASSED");
        else
            $display(" tamper_fuse_ctrl.v: TESTS FAILED -- DO NOT INTEGRATE");

        $finish;
    end

endmodule
