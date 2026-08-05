module security_mode_ctrl(
    input  wire        clk,
    input  wire        rst,
    input  wire         security_mode,      // 0=LITE, 1=FULL
    input  wire [31:0]  transaction_value,  // Payment amount (paise)
    input  wire          auto_escalate_en,   // Auto-upgrade high-value txns
    output reg           effective_mode,     // Actual mode used this txn
    output reg           mode_escalated      // Flag: auto-upgraded to FULL
);
    // Unique feature: same silicon serves two market tiers.
    // A Rs 500 QR soundbox and a Rs 5000 premium POS terminal 
    // can use the SAME chip — the manufacturer just sets 
    // security_mode based on their product tier.
    //
    // Additionally: even in LITE-configured devices, if a 
    // single transaction crosses a value threshold (e.g. 
    // Rs 2000, matching UPI's own risk-tiering), the chip 
    // auto-escalates to FULL security for that transaction — 
    // giving cheap hardware high-security behavior exactly 
    // when it matters most.

    parameter HIGH_VALUE_THRESHOLD = 32'd200000; // Rs 2000 in paise

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            effective_mode  <= 0;
            mode_escalated  <= 0;
        end
        else begin
            if (security_mode == 1'b1) begin
                // Device is FULL-tier — always FULL, no escalation needed
                effective_mode <= 1'b1;
                mode_escalated <= 1'b0;
            end
            else if (auto_escalate_en && 
                     (transaction_value >= HIGH_VALUE_THRESHOLD)) begin
                // LITE-tier device, but high-value transaction — escalate!
                effective_mode <= 1'b1;
                mode_escalated <= 1'b1;
            end
            else begin
                // LITE-tier device, normal transaction — stay fast/cheap
                effective_mode <= 1'b0;
                mode_escalated <= 1'b0;
            end
        end
    end
endmodule
