module pwm(
    input  wire        clk,
    input  wire        rst,
    input  wire [7:0]  duty,
    input  wire [7:0]  period,
    output reg         pwm_out,
    output reg         active
);
    reg [7:0] counter;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            counter <= 0;
            pwm_out <= 0;
            active  <= 0;
        end
        else begin
            if (counter >= period) begin
                counter <= 0;
            end else begin
                counter <= counter + 1;
            end

            if (duty == 0) begin
                pwm_out <= 0;
                active  <= 0;
            end
            else if (duty >= period) begin
                pwm_out <= 1;
                active  <= 1;
            end
            else begin
                pwm_out <= (counter < duty) ? 1 : 0;
                active  <= 1;
            end
        end
    end
endmodule
