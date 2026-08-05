module thermal_rate_detector(
    input  wire        clk,
    input  wire        rst,
    input  wire         sample_tick,      // Periodic sample trigger (e.g. every 1 sec)
    input  wire [11:0]  current_temp,     // Voted temperature (from sensor_voter)
    output reg           rate_warning,     // Early warning — rapid rise detected!
    output reg  signed [12:0] temp_delta,  // Debug: actual rate (can be negative)
    output reg  [11:0]  temp_at_last_sample
);
    // Global chips only check absolute threshold. This detects 
    // the DANGEROUS PATTERN of rapid rise before the absolute 
    // threshold is even crossed — critical because thermal 
    // runaway is a runaway (accelerating) process, not a 
    // slow linear one. Catching it early = more time to 
    // safely disconnect before absolute danger zone.

    parameter RATE_WARNING_THRESHOLD = 13'sd200; 
    // ~5 degrees C worth of ADC counts per sample interval 
    // (scaled same as voltage_level in thermal_trip.v)

    reg [11:0] prev_temp;
    reg        first_sample;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            prev_temp           <= 0;
            first_sample        <= 1;
            rate_warning         <= 0;
            temp_delta            <= 0;
            temp_at_last_sample <= 0;
        end
        else if (sample_tick) begin
            if (first_sample) begin
                // First sample ka koi previous value nahi hai — 
                // baseline set karo, warning mat do
                prev_temp     <= current_temp;
                first_sample  <= 0;
                rate_warning  <= 0;
                temp_delta    <= 0;
            end
            else begin
                // Rate of change calculate karo (signed — 
                // cooling bhi possible hai, negative delta)
                temp_delta <= $signed({1'b0, current_temp}) - 
                              $signed({1'b0, prev_temp});

                if (($signed({1'b0, current_temp}) - 
                     $signed({1'b0, prev_temp})) >= 
                     $signed(RATE_WARNING_THRESHOLD)) begin
                    rate_warning <= 1; // RAPID RISE — early warning!
                end
                else begin
                    rate_warning <= 0;
                end

                prev_temp <= current_temp;
            end
            temp_at_last_sample <= current_temp;
        end
    end
endmodule
