module safety_watchdog(
    input  wire        clk,
    input  wire        rst,
    input  wire        fsm_heartbeat,  // Safety FSM periodically pulses this
    output reg          watchdog_fault, // FSM has hung - force safe state!
    output reg  [15:0]  timeout_count
);
    // BMS ka safety FSM khud bhi hang ho sakta hai (software bug, 
    // glitch). Agar yeh hota hai, watchdog isko detect karke 
    // chip ko FORCE SAFE STATE (disconnect) mein le jaata hai — 
    // bina kisi CPU intervention ke.
    parameter TIMEOUT_LIMIT = 16'd1000;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            timeout_count  <= 0;
            watchdog_fault <= 0;
        end
        else if (fsm_heartbeat) begin
            timeout_count  <= 0;
            watchdog_fault <= 0;
        end
        else if (timeout_count == TIMEOUT_LIMIT) begin
            watchdog_fault <= 1; // Force safe state!
        end
        else begin
            timeout_count <= timeout_count + 1;
        end
    end
endmodule
