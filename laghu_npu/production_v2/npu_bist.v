module npu_bist(
    input  wire         clk,
    input  wire         rst,
    input  wire         start_bist,
    output reg          bist_pass,
    output reg          bist_fail,
    output reg          bist_done,
    // Test hooks — pe_array se known values check karte hain
    input  wire signed [31:0] test_mac_result  // Known weight x activation result
);
    // Known-Answer Test: 
    // Weight=5, Activation=3 -> Expected MAC = 15
    // Yeh chip power-up pe khud verify karta hai ki 
    // multiply-accumulate hardware sahi kaam kar raha hai
    parameter EXPECTED_MAC = 32'sd15;

    parameter IDLE       = 2'd0;
    parameter CHECK_MAC  = 2'd1;
    parameter DONE_PASS  = 2'd2;
    parameter DONE_FAIL  = 2'd3;

    reg [1:0] state;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state     <= IDLE;
            bist_pass <= 0;
            bist_fail <= 0;
            bist_done <= 0;
        end
        else begin
            case (state)
                IDLE: begin
                    bist_done <= 0;
                    bist_pass <= 0;
                    bist_fail <= 0;
                    if (start_bist)
                        state <= CHECK_MAC;
                end

                CHECK_MAC: begin
                    if (test_mac_result == EXPECTED_MAC)
                        state <= DONE_PASS;
                    else
                        state <= DONE_FAIL; // PE array faulty — silicon defect!
                end

                DONE_PASS: begin
                    bist_pass <= 1;
                    bist_done <= 1;
                    state     <= IDLE;
                end

                DONE_FAIL: begin
                    bist_fail <= 1;
                    bist_done <= 1;
                    state     <= IDLE;
                end
            endcase
        end
    end
endmodule
