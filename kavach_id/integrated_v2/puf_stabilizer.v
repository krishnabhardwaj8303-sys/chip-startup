module puf_stabilizer(
    input  wire        clk,
    input  wire        rst,
    input  wire        start,
    input  wire [31:0] raw_response_1,  // Same challenge, sample 1
    input  wire [31:0] raw_response_2,  // Same challenge, sample 2
    input  wire [31:0] raw_response_3,  // Same challenge, sample 3
    output reg  [31:0] stable_response,
    output reg  [31:0] unstable_bit_mask, // Kaunse bits noisy hain
    output reg          stable_done,
    output reg  [5:0]   unstable_bit_count
);
    // Real PUF chips (jaise SRAM PUF) ka sabse bada 
    // production problem: temperature/voltage/aging ke 
    // saath same challenge ka response THODA change ho 
    // sakta hai — 1-5% bits "flip" ho sakte hain.
    //
    // Bina stabilization ke: authentication randomly 
    // fail hoga — genuine user bhi reject ho sakta hai!
    //
    // Solution: 3 samples lo, majority vote karo har bit pe

    integer i;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            stable_response    <= 0;
            unstable_bit_mask  <= 0;
            stable_done        <= 0;
            unstable_bit_count <= 0;
        end
        else if (start) begin
            unstable_bit_count <= 0;
            for (i = 0; i < 32; i = i + 1) begin
                // Majority vote: kam se kam 2/3 samples 
                // agree karne chahiye
                stable_response[i] <= 
                    (raw_response_1[i] & raw_response_2[i]) |
                    (raw_response_2[i] & raw_response_3[i]) |
                    (raw_response_1[i] & raw_response_3[i]);

                // Flag karo agar 3 samples mein disagreement hai
                unstable_bit_mask[i] <= 
                    (raw_response_1[i] != raw_response_2[i]) |
                    (raw_response_2[i] != raw_response_3[i]);

                if ((raw_response_1[i] != raw_response_2[i]) |
                    (raw_response_2[i] != raw_response_3[i]))
                    unstable_bit_count <= unstable_bit_count + 1;
            end
            stable_done <= 1;
        end
        else begin
            stable_done <= 0;
        end
    end
endmodule
