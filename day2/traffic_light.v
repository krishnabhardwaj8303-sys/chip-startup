module traffic_light(
    input  wire clk,
    input  wire rst,
    output reg  red,
    output reg  yellow,
    output reg  green
);

    // States define karo
    parameter RED_STATE    = 2'b00;
    parameter GREEN_STATE  = 2'b01;
    parameter YELLOW_STATE = 2'b10;

    reg [1:0] state;
    reg [3:0] counter;

    // State transitions
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state   <= RED_STATE;
            counter <= 0;
        end
        else begin
            counter <= counter + 1;

            case (state)
                RED_STATE: begin
                    if (counter == 4'd7) begin
                        state   <= GREEN_STATE;
                        counter <= 0;
                    end
                end

                GREEN_STATE: begin
                    if (counter == 4'd7) begin
                        state   <= YELLOW_STATE;
                        counter <= 0;
                    end
                end

                YELLOW_STATE: begin
                    if (counter == 4'd3) begin
                        state   <= RED_STATE;
                        counter <= 0;
                    end
                end

                default: state <= RED_STATE;
            endcase
        end
    end

    // Output logic
    always @(*) begin
        red    = 0;
        yellow = 0;
        green  = 0;
        case (state)
            RED_STATE:    red    = 1;
            GREEN_STATE:  green  = 1;
            YELLOW_STATE: yellow = 1;
        endcase
    end

endmodule
