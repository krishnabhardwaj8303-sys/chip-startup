module safety_assertions(
    input wire clk,
    input wire rst,
    input wire bist_fail,
    input wire bist_done,
    input wire wdt_timeout,
    input wire glitch_detected,
    input wire aes_start_o,
    input wire trip_signal      // From thermal_trip (BMS reuse example)
);

    // ── PROPERTY 1: BIST failure must ALWAYS be visible in status ──
    // Agar chip faulty hai, uska pata turant chalna chahiye — 
    // kabhi bhi silent fail nahi hona chahiye
    property p_bist_fail_visible;
        @(posedge clk) disable iff (rst)
        bist_fail |-> ##[0:2] bist_done;
    endproperty
    assert property (p_bist_fail_visible)
        else $error("SAFETY VIOLATION: BIST fail not flagged as done!");

    // ── PROPERTY 2: Watchdog timeout must be sticky ──
    // Ek baar CPU hang detect ho jaaye, signal clear 
    // nahi hona chahiye jab tak explicit reset na aaye
    property p_watchdog_sticky;
        @(posedge clk) 
        wdt_timeout |-> ##1 (wdt_timeout || rst);
    endproperty
    assert property (p_watchdog_sticky)
        else $error("SAFETY VIOLATION: Watchdog timeout cleared without reset!");

    // ── PROPERTY 3: Glitch detection must block AES operation ──
    // Agar attack detect ho raha hai, chip ko crypto 
    // operation START nahi karna chahiye
    property p_glitch_blocks_aes;
        @(posedge clk) disable iff (rst)
        glitch_detected |-> !aes_start_o;
    endproperty
    assert property (p_glitch_blocks_aes)
        else $error("SECURITY VIOLATION: AES started during glitch attack!");

endmodule
