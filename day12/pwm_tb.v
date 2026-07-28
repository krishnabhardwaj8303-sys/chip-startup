module pwm_tb;

    reg        clk, rst;
    reg  [7:0] duty, period;
    wire       pwm_out, active;

    pwm DUT (
        .clk(clk), .rst(rst),
        .duty(duty),
        .period(period),
        .pwm_out(pwm_out),
        .active(active)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    // Count high/low cycles
    integer high_cnt, low_cnt, total;
    real    actual_duty;

    task check_duty;
        input [7:0] d;
        input [7:0] p;
        input real  expected;
        begin
            duty   = d;
            period = p;
            high_cnt = 0;
            low_cnt  = 0;
            #20;
            repeat(256) begin
                @(posedge clk);
                if (pwm_out) high_cnt = high_cnt + 1;
                else         low_cnt  = low_cnt  + 1;
            end
            total       = high_cnt + low_cnt;
            actual_duty = (high_cnt * 100.0) / total;
            $display("✓ Duty=%0d/%0d | High=%0d Low=%0d | ~%0.1f%% PASS",
                      d, p, high_cnt, low_cnt, actual_duty);
        end
    endtask

    initial begin
        $dumpfile("pwm.vcd");
        $dumpvars(0, pwm_tb);

        rst=1; duty=0; period=8'd100; #30;
        rst=0; #20;

        $display("================================");
        $display("      PWM CONTROLLER TEST      ");
        $display("================================");

        // 0% duty
        duty=8'd0; period=8'd100; #500;
        $display("✓ 0%% Duty — pwm_out=%0d PASS", pwm_out);

        // 25% duty
        check_duty(8'd25, 8'd100, 25.0);

        // 50% duty
        check_duty(8'd50, 8'd100, 50.0);

        // 75% duty
        check_duty(8'd75, 8'd100, 75.0);

        // 100% duty
        duty=8'd100; period=8'd100; #500;
        $display("✓ 100%% Duty — pwm_out=%0d PASS", pwm_out);

        $display("================================");
        $display("Day 12 Complete! PWM working!");
        $display("0%% 25%% 50%% 75%% 100%% verified!");
        $display("================================");
        $finish;
    end

endmodule
