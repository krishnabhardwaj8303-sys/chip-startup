module adc_controller(
    input  wire        clk,
    input  wire        rst,
    input  wire        start,
    input  wire [4:0]  channel_sel,   // 24 channels tak
    output reg  [11:0] voltage_data,  // 12-bit ADC value
    output reg         data_valid,
    output reg  [4:0]  active_channel
);
    parameter IDLE    = 2'd0;
    parameter SAMPLE  = 2'd1;
    parameter CONVERT = 2'd2;
    parameter DONE    = 2'd3;

    reg [1:0]  state;
    reg [7:0]  sample_counter;

    // Simulated cell voltage — real chip mein 
    // yeh actual ADC hardware se aayega
    reg [11:0] simulated_voltage [0:23];
    integer i;

    initial begin
        // 24 cells ka simulated voltage 
        // (LFP battery: 2.8V-3.6V range, 
        // scaled to 12-bit ADC: 0-4095)
        for (i = 0; i < 24; i = i + 1) begin
            simulated_voltage[i] = 12'd2800 + (i * 15);
        end
    end

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state          <= IDLE;
            voltage_data   <= 0;
            data_valid     <= 0;
            active_channel <= 0;
            sample_counter <= 0;
        end
        else begin
            case (state)
                IDLE: begin
                    data_valid <= 0;
                    if (start) begin
                        active_channel <= channel_sel;
                        state          <= SAMPLE;
                        sample_counter <= 0;
                    end
                end

                SAMPLE: begin
                    // Sample-and-hold delay simulate karo
                    if (sample_counter == 8'd10) begin
                        state <= CONVERT;
                        sample_counter <= 0;
                    end else
                        sample_counter <= sample_counter + 1;
                end

                CONVERT: begin
                    // ADC conversion delay
                    if (sample_counter == 8'd20) begin
                        voltage_data <= simulated_voltage[active_channel];
                        state <= DONE;
                    end else
                        sample_counter <= sample_counter + 1;
                end

                DONE: begin
                    data_valid <= 1;
                    state      <= IDLE;
                end
            endcase
        end
    end
endmodule
