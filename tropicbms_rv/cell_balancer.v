module cell_balancer(
    input  wire        clk,
    input  wire        rst,
    input  wire [11:0] cell_voltage [0:23], // Sabhi 24 cells ki voltage
    output reg  [23:0] balance_enable        // Har cell ke liye balance switch
);
    // Simple averaging-based balancing:
    // Jo cell average se zyada charged hai, 
    // uska balance resistor enable karo
    reg [15:0] avg_voltage;
    reg [15:0] sum;
    integer i;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            balance_enable <= 24'b0;
            avg_voltage    <= 0;
        end
        else begin
            // Average calculate karo
            sum = 0;
            for (i = 0; i < 24; i = i + 1)
                sum = sum + cell_voltage[i];
            avg_voltage <= sum / 24;

            // Har cell check karo average se
            for (i = 0; i < 24; i = i + 1) begin
                if (cell_voltage[i] > avg_voltage + 12'd10)
                    balance_enable[i] <= 1;
                else
                    balance_enable[i] <= 0;
            end
        end
    end
endmodule
