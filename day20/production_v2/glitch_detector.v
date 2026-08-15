module glitch_detector(
    input  wire        clk,
    input  wire        rst,
    input  wire        clk_monitor,
    input  wire [7:0]  voltage_level,
    output reg         glitch_detected,   // Registered — status/reporting ke liye
    output reg  [1:0]  glitch_type,
    output wire         glitch_now         // Combinational — turant interlock ke liye
);
    parameter VOLTAGE_MIN = 8'd180;
    parameter VOLTAGE_MAX = 8'd220;
    reg clk_monitor_prev;
    reg [3:0] clk_edge_counter;
    reg [3:0] main_edge_counter;

    // FIX: Combinational glitch flag — same-cycle detection,
    // isse koi 1-cycle race condition nahi hoti safety interlocks mein
    assign glitch_now = (voltage_level < VOLTAGE_MIN) ||
                         (voltage_level > VOLTAGE_MAX);

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            glitch_detected   <= 0;
            glitch_type       <= 0;
            clk_monitor_prev  <= 0;
            clk_edge_counter  <= 0;
            main_edge_counter <= 0;
        end
        else begin
            main_edge_counter <= main_edge_counter + 1;
            clk_monitor_prev  <= clk_monitor;
            if (glitch_now) begin
                glitch_detected <= 1;
                glitch_type     <= 2'b10;
            end
            else begin
                glitch_detected <= 0;
                glitch_type     <= 2'b00;
            end
        end
    end
endmodule
