module bms_safety_assertions(
    input wire clk,
    input wire rst,
    input wire watchdog_fault,
    input wire safe_state_forced,
    input wire trip_signal,
    input wire high_current_enable
);

    // ── PROPERTY 1: Watchdog fault MUST force safe state ──
    property p_watchdog_forces_safe;
        @(posedge clk) disable iff (rst)
        watchdog_fault |-> ##[0:2] safe_state_forced;
    endproperty
    assert property (p_watchdog_forces_safe)
        else $error("SAFETY VIOLATION: Watchdog fault did not force safe state!");

    // ── PROPERTY 2: Thermal trip must disable current path ──
    property p_trip_disables_current;
        @(posedge clk) disable iff (rst)
        trip_signal |-> !high_current_enable;
    endproperty
    assert property (p_trip_disables_current)
        else $error("SAFETY VIOLATION: Current path active during thermal trip!");

endmodule
