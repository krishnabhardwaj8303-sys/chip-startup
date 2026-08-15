module safety_assertions(
    input wire clk,
    input wire rst,
    input wire bist_fail,
    input wire bist_done,
    input wire wdt_timeout,
    input wire glitch_detected,
    input wire aes_start_o,
    input wire trip_signal
);

    // PROPERTY 3: Glitch detection must block AES operation
    always @(posedge clk) begin
        if (!rst) begin
            assert (!(glitch_detected && aes_start_o));
        end
    end

    // PROPERTY 2: Watchdog timeout must be sticky
    always @(posedge clk) begin
        if ($past(wdt_timeout) && !$past(rst) && !rst) begin
            assert (wdt_timeout);
        end
    end

    // PROPERTY 1: BIST failure must be visible as done (same cycle)
    always @(posedge clk) begin
        if (!rst) begin
            assert (!bist_fail || bist_done);
        end
    end

endmodule
