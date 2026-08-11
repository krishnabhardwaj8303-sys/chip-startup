module coulomb_counter(
    input  wire        clk,
    input  wire        rst,
    input  wire [11:0] current_sense,  // Current sensor input (signed)
    input  wire        current_valid,
    output reg  [31:0] accumulated_charge,  // Total charge counter
    output reg  [7:0]  soc_percent          // State of Charge %
);
    parameter BATTERY_CAPACITY = 32'd100000; // Simulated full capacity

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            accumulated_charge <= BATTERY_CAPACITY; // Start full
            soc_percent        <= 8'd100;
        end
        else if (current_valid) begin
            // Coulomb counting: integrate current over time
            if (current_sense[11]) begin
                // Discharging (negative current, MSB=1)
                if (accumulated_charge > 0)
                    accumulated_charge <= accumulated_charge - {20'b0, current_sense[10:0]};
            end
            else begin
                // Charging
                if (accumulated_charge < BATTERY_CAPACITY)
                    accumulated_charge <= accumulated_charge + {20'b0, current_sense[10:0]};
            end

            // SOC percentage calculate karo
            soc_percent <= (accumulated_charge * 100) / BATTERY_CAPACITY;
        end
    end
endmodule
