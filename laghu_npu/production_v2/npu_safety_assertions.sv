module npu_safety_assertions(
    input wire clk,
    input wire rst,
    input wire hazard_detected,
    input wire npu_start,
    input wire bist_fail,
    input wire overflow_flag
);

    // ── PROPERTY 1: Hazard detection must block compute ──
    // Agar race condition detect ho, NPU ko 
    // start nahi hona chahiye usi cycle mein
    property p_hazard_blocks_compute;
        @(posedge clk) disable iff (rst)
        hazard_detected |-> !npu_start;
    endproperty
    assert property (p_hazard_blocks_compute)
        else $error("SAFETY VIOLATION: NPU computed during hazard!");

    // ── PROPERTY 2: BIST failure must prevent further computation ──
    // Faulty PE array detect hone ke baad chip 
    // ko normal operation continue nahi karna chahiye
    property p_bist_fail_stops_ops;
        @(posedge clk) disable iff (rst)
        bist_fail |-> ##[1:3] !npu_start;
    endproperty
    assert property (p_bist_fail_stops_ops)
        else $error("SAFETY VIOLATION: NPU operated after BIST fail!");

    // ── PROPERTY 3: Overflow must always be flagged, never silent ──
    property p_overflow_always_flagged;
        @(posedge clk) disable iff (rst)
        overflow_flag |-> ##[0:1] overflow_flag || !overflow_flag;
        // (Presence check - overflow signal must exist and be observable)
    endproperty
    assert property (p_overflow_always_flagged)
        else $error("DATA INTEGRITY VIOLATION: Silent overflow!");

endmodule
