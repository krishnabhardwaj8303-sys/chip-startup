module trng(
    input  wire        clk,
    input  wire        rst,
    input  wire        enable,
    output reg  [31:0]  random_out,
    output reg          random_valid,
    output reg          self_test_pass
);
    // Dedicated entropy source, distinct from PUF (per proposal).
    // Real silicon: 2 free-running ring oscillators, jitter 
    // difference XOR se entropy nikalti hai. Simulation mein 
    // 2 independent LFSRs se approximate karte hain.

    reg [31:0] osc1, osc2;
    reg [31:0] shift_out;
    reg [4:0]  bit_count;
    reg        vn_bit1;
    reg        vn_bit1_valid;
    reg [15:0] ones_count;
    reg [15:0] sample_count;
    reg        raw_bit;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            osc1           <= 32'hACE1_2345;
            osc2           <= 32'h1234_BEEF;
            shift_out      <= 32'h0;
            bit_count      <= 5'd0;
            random_out     <= 32'h0;
            random_valid   <= 1'b0;
            vn_bit1        <= 1'b0;
            vn_bit1_valid  <= 1'b0;
            ones_count     <= 16'd0;
            sample_count   <= 16'd0;
            self_test_pass <= 1'b0;
        end
        else begin
            random_valid <= 1'b0; // Default: clear every cycle (pulse)

            if (enable) begin
                // Two independent LFSRs — different tap positions 
                // simulate different oscillator frequencies
                osc1 <= {osc1[30:0], osc1[31] ^ osc1[21] ^ osc1[1] ^ osc1[0]};
                osc2 <= {osc2[30:0], osc2[31] ^ osc2[17]};

                raw_bit = osc1[0] ^ osc2[0];

                // Von Neumann de-biasing
                if (!vn_bit1_valid) begin
                    vn_bit1       <= raw_bit;
                    vn_bit1_valid <= 1'b1;
                end
                else begin
                    vn_bit1_valid <= 1'b0;
                    if (vn_bit1 != raw_bit) begin
                        shift_out    <= {shift_out[30:0], vn_bit1};
                        bit_count    <= bit_count + 1'b1;
                        ones_count   <= ones_count + vn_bit1;
                        sample_count <= sample_count + 1'b1;

                        if (bit_count == 5'd31) begin
                            random_out   <= {shift_out[30:0], vn_bit1};
                            random_valid <= 1'b1;
                            bit_count    <= 5'd0;
                        end
                    end
                end

                if (sample_count >= 16'd1000) begin
                    self_test_pass <= (ones_count > 16'd450) && 
                                       (ones_count < 16'd550);
                end
            end
        end
    end
endmodule
