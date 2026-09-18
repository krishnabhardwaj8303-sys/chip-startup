module offline_verify_counter(
    input  wire        clk,
    input  wire        rst,
    input  wire         verify_request,     // Har baar authentication attempt
    input  wire         sync_complete,      // Server se successfully sync hua
    output reg  [7:0]   offline_budget,     // Kitni verifications bachi hain
    output reg           verify_allowed,     // Is verification ko proceed karo
    output reg           sync_required,      // MUST connect online now
    output reg  [15:0]   total_offline_uses  // Lifetime counter (audit trail)
);
    // Proposal ka gap: "backend verification server" pe 
    // dependency, jo rural/low-connectivity markets mein 
    // (exactly jahan counterfeit seed/pesticide sabse bada 
    // problem hai) chip ko useless bana deta hai.
    //
    // Yeh module ek "offline budget" maintain karta hai — 
    // chip khud N baar tak verify kar sake bina server ke, 
    // phir mandatory sync maange. Har offline use counter 
    // decrement karta hai; server sync par budget reset hota hai.

    parameter INITIAL_BUDGET = 8'd50;   // Factory-provisioned offline uses
    parameter LOW_BUDGET_WARNING = 8'd5; // Warn user before budget runs out

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            offline_budget      <= INITIAL_BUDGET;
            verify_allowed       <= 0;
            sync_required         <= 0;
            total_offline_uses  <= 0;
        end
        else begin
            verify_allowed <= 0; // Default: pulse per request

            if (sync_complete) begin
                // Server se connect hua — budget refresh, 
                // sync requirement clear
                offline_budget <= INITIAL_BUDGET;
                sync_required   <= 0;
            end
            else if (verify_request) begin
                if (offline_budget > 0) begin
                    // Budget available — offline verification allow karo
                    verify_allowed      <= 1;
                    offline_budget       <= offline_budget - 1;
                    total_offline_uses  <= total_offline_uses + 1;

                    // Budget khatam hone ke kagaar pe hai — sync required
                    // set karo TURANT jab yeh last use ho
                    if (offline_budget == 8'd1)
                        sync_required <= 1;
                end
                else begin
                    // Budget khatam — verification BLOCK karo, 
                    // mandatory sync maango
                    verify_allowed <= 0;
                    sync_required   <= 1;
                end
            end
        end
    end
endmodule
