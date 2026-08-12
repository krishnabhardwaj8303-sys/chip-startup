module soh_tracker(
    input  wire        clk,
    input  wire        rst,
    input  wire [7:0]  soc_percent,
    input  wire         soc_valid,
    output reg  [15:0]  cycle_count,
    output reg  [7:0]   soh_percent,
    output reg           replacement_warning
);
    // Simplified linear degradation model: lose 1% SOH 
    // every CYCLES_PER_PERCENT full cycles. At 20 cycles/%, 
    // 500 cycles => ~25% loss => SOH settles around 75%, 
    // a realistic mid-life EV battery figure.
    parameter CYCLES_PER_PERCENT   = 16'd20;
    parameter SOH_WARNING_THRESHOLD = 8'd80;
    parameter HIGH_WATER = 8'd90;
    parameter LOW_WATER  = 8'd20;

    parameter WAIT_HIGH = 2'd0;
    parameter SEEN_HIGH = 2'd1;
    parameter SEEN_LOW  = 2'd2;

    reg [1:0] cycle_state;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            cycle_count         <= 0;
            soh_percent           <= 100;
            replacement_warning   <= 0;
            cycle_state           <= WAIT_HIGH;
        end
        else if (soc_valid) begin
            case (cycle_state)
                WAIT_HIGH: begin
                    if (soc_percent >= HIGH_WATER)
                        cycle_state <= SEEN_HIGH;
                end
                SEEN_HIGH: begin
                    if (soc_percent <= LOW_WATER)
                        cycle_state <= SEEN_LOW;
                end
                SEEN_LOW: begin
                    if (soc_percent >= HIGH_WATER) begin
                        cycle_count <= cycle_count + 1;
                        // Recompute SOH directly from new cycle count
                        if ((100 - ((cycle_count + 1) / CYCLES_PER_PERCENT)) > 0)
                            soh_percent <= 100 - ((cycle_count + 1) / CYCLES_PER_PERCENT);
                        else
                            soh_percent <= 0;
                        cycle_state <= SEEN_HIGH;
                    end
                end
            endcase

            if (soh_percent <= SOH_WARNING_THRESHOLD)
                replacement_warning <= 1;
            else
                replacement_warning <= 0;
        end
    end
endmodule
