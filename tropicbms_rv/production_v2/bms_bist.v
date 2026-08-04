module bms_bist(
    input  wire        clk,
    input  wire        rst,
    input  wire        start_bist,
    output reg          bist_pass,
    output reg          bist_fail,
    output reg          bist_done,
    input  wire         voter_test_ok,   // Sensor voter known-answer test
    input  wire         thermal_test_ok  // Thermal trip known-answer test
);
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
                    if (voter_test_ok && thermal_test_ok)
                        state <= DONE_PASS;
                    else
                        state <= DONE_FAIL; // Safety circuit itself is faulty!
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
