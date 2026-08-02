module glitch_detector(
    input  wire        clk,
    input  wire        rst,
    input  wire        clk_monitor,   // Doosri clock domain se monitor
    input  wire [7:0]  voltage_level, // Simulated voltage sensor
    output reg         glitch_detected,
    output reg  [1:0]  glitch_type    // 1=clock, 2=voltage, 3=both
);
    // Attackers glitch attacks karte hain — 
    // clock ya voltage mein achanak spike/drop 
    // karke chip ko galat instruction execute 
    // karwane ke liye (fault injection attack).
    // Yeh security-critical detection hai.

    parameter VOLTAGE_MIN = 8'd180; // Normal operating range
    parameter VOLTAGE_MAX = 8'd220;

    reg clk_monitor_prev;
    reg [3:0] clk_edge_counter;
    reg [3:0] main_edge_counter;

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

            // Voltage check — agar range se bahar 
            // jaaye toh attack ho sakta hai
            if (voltage_level < VOLTAGE_MIN || 
                voltage_level > VOLTAGE_MAX) begin
                glitch_detected <= 1;
                glitch_type     <= 2'b10; // Voltage glitch
            end
            else begin
                glitch_detected <= 0;
                glitch_type     <= 2'b00;
            end
        end
    end
endmodule
