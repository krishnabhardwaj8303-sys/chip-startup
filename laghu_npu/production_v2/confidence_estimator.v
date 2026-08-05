module confidence_estimator(
    input  wire        clk,
    input  wire        rst,
    input  wire         sample_valid,
    input  wire signed [7:0] a_in0, a_in1, a_in2, a_in3,  // Row activations
    output reg           low_confidence,     // Flag: input looks corrupted
    output reg  [2:0]    saturated_count,    // How many channels saturated
    output reg           dust_fog_signature  // Specific pattern match
);
    // Generic accelerators just compute — they never ask "is my 
    // input trustworthy?" This module detects a signature common 
    // to dust/fog/glare corruption: multiple simultaneous extreme 
    // saturation values (-128 or +127) across input channels, 
    // which is statistically rare in clean natural images but 
    // common when a camera sensor is partially blinded.

    parameter SATURATION_HIGH = 8'sd127;
    parameter SATURATION_LOW  = -8'sd128;
    parameter CONFIDENCE_THRESHOLD = 3'd2; // 2+ saturated channels = suspicious

    wire sat0, sat1, sat2, sat3;

    assign sat0 = (a_in0 == SATURATION_HIGH) || (a_in0 == SATURATION_LOW);
    assign sat1 = (a_in1 == SATURATION_HIGH) || (a_in1 == SATURATION_LOW);
    assign sat2 = (a_in2 == SATURATION_HIGH) || (a_in2 == SATURATION_LOW);
    assign sat3 = (a_in3 == SATURATION_HIGH) || (a_in3 == SATURATION_LOW);

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            low_confidence     <= 0;
            saturated_count    <= 0;
            dust_fog_signature <= 0;
        end
        else if (sample_valid) begin
            saturated_count <= sat0 + sat1 + sat2 + sat3;

            if ((sat0 + sat1 + sat2 + sat3) >= CONFIDENCE_THRESHOLD) begin
                low_confidence     <= 1;
                dust_fog_signature <= 1;
            end
            else begin
                low_confidence     <= 0;
                dust_fog_signature <= 0;
            end
        end
    end
endmodule
