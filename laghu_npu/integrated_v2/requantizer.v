module requantizer(
    input  wire signed [31:0] acc_in,    // 32-bit accumulator result
    input  wire        [4:0]  shift_amt, // Requantization shift (scale factor)
    output reg  signed [7:0]  quant_out, // Back to INT8 for next layer
    output reg                overflow_flag,
    output reg                underflow_flag
);
    // Real NPU chips mein: har layer ke baad accumulator 
    // (32-bit) ko wapas INT8 mein convert karna padta hai 
    // taaki next layer efficiently chal sake.
    // 
    // Bina saturation ke: agar value INT8 range se bahar 
    // jaaye (-128 to 127), toh silently wraparound ho jaata 
    // hai — matlab GALAT AI output aa sakta hai bina 
    // kisi warning ke. Yeh production chip mein CRITICAL bug hai.

    reg signed [31:0] shifted_val;

    always @(*) begin
        shifted_val = acc_in >>> shift_amt; // Arithmetic right shift

        overflow_flag  = 0;
        underflow_flag = 0;

        if (shifted_val > 32'sd127) begin
            quant_out      = 8'sd127;   // Saturate to max INT8
            overflow_flag  = 1;         // Flag karo — silent nahi hone denge
        end
        else if (shifted_val < -32'sd128) begin
            quant_out      = -8'sd128;  // Saturate to min INT8
            underflow_flag = 1;
        end
        else begin
            quant_out = shifted_val[7:0];
        end
    end
endmodule
