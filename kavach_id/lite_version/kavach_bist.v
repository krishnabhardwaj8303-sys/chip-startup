module kavach_bist(
    input  wire        clk,
    input  wire        rst,
    input  wire        start_bist,
    output reg          bist_pass,
    output reg          bist_fail,
    output reg          bist_done,
    // Known challenge -> known expected response (factory calibrated)
    input  wire [31:0] test_response
);
    // Factory-time: chip ek fixed challenge ke saath test 
    // kiya jaata hai, aur expected response record hota hai.
    // Power-up pe chip khud verify karta hai ki PUF array 
    // degrade toh nahi hua (aging, damage check)
    parameter EXPECTED_TEST_RESPONSE = 32'hCAFEBABE;

    parameter IDLE      = 2'd0;
    parameter CHECKING  = 2'd1;
    parameter DONE_PASS = 2'd2;
    parameter DONE_FAIL = 2'd3;

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
                        state <= CHECKING;
                end
                CHECKING: begin
                    if (test_response == EXPECTED_TEST_RESPONSE)
                        state <= DONE_PASS;
                    else
                        state <= DONE_FAIL; // PUF degraded/damaged!
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
