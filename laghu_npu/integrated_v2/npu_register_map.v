module npu_register_map(
    input  wire        clk,
    input  wire        rst,
    input  wire        reg_write,
    input  wire        reg_read,
    input  wire [7:0]  reg_addr,
    input  wire [31:0] reg_wdata,
    output reg  [31:0] reg_rdata,
    output reg          reg_ready,

    input  wire         npu_done_i,
    input  wire         bist_pass_i,
    input  wire         bist_fail_i,
    input  wire         hazard_detected_i,
    input  wire signed [31:0] out0_i,
    input  wire signed [31:0] out1_i,
    input  wire signed [31:0] out2_i,
    input  wire signed [31:0] out3_i,

    output reg          npu_start_o,
    output reg          bist_start_o,
    output reg          load_weights_o,
    output reg          load_activations_o,
    output reg  [1:0]   weight_row_idx_o,
    output reg  signed [7:0] w_in0_o,
    output reg  signed [7:0] w_in1_o,
    output reg  signed [7:0] w_in2_o,
    output reg  signed [7:0] w_in3_o,
    output reg  signed [7:0] a_in0_o,
    output reg  signed [7:0] a_in1_o,
    output reg  signed [7:0] a_in2_o,
    output reg  signed [7:0] a_in3_o
);
    parameter ADDR_CONTROL   = 8'h00;
    parameter ADDR_STATUS    = 8'h04;
    parameter ADDR_W_ROW_IDX = 8'h08;
    parameter ADDR_W_DATA    = 8'h0C;
    parameter ADDR_A_DATA    = 8'h10;
    parameter ADDR_OUT0      = 8'h14;
    parameter ADDR_OUT1      = 8'h18;
    parameter ADDR_OUT2      = 8'h1C;
    parameter ADDR_OUT3      = 8'h20;
    parameter ADDR_CHIP_ID   = 8'hFC;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            reg_rdata          <= 0;
            reg_ready          <= 0;
            npu_start_o        <= 0;
            bist_start_o       <= 0;
            load_weights_o     <= 0;
            load_activations_o <= 0;
            weight_row_idx_o   <= 0;
            w_in0_o <= 0; w_in1_o <= 0; w_in2_o <= 0; w_in3_o <= 0;
            a_in0_o <= 0; a_in1_o <= 0; a_in2_o <= 0; a_in3_o <= 0;
        end
        else begin
            reg_ready          <= 0;
            npu_start_o        <= 0;
            bist_start_o       <= 0;
            load_weights_o     <= 0;
            load_activations_o <= 0;

            if (reg_write) begin
                reg_ready <= 1;
                case (reg_addr)
                    ADDR_CONTROL: begin
                        npu_start_o        <= reg_wdata[0];
                        bist_start_o       <= reg_wdata[1];
                        load_weights_o     <= reg_wdata[2];
                        load_activations_o <= reg_wdata[3];
                    end
                    ADDR_W_ROW_IDX:
                        weight_row_idx_o <= reg_wdata[1:0];
                    ADDR_W_DATA: begin
                        w_in0_o <= reg_wdata[7:0];
                        w_in1_o <= reg_wdata[15:8];
                        w_in2_o <= reg_wdata[23:16];
                        w_in3_o <= reg_wdata[31:24];
                    end
                    ADDR_A_DATA: begin
                        a_in0_o <= reg_wdata[7:0];
                        a_in1_o <= reg_wdata[15:8];
                        a_in2_o <= reg_wdata[23:16];
                        a_in3_o <= reg_wdata[31:24];
                    end
                    default: ;
                endcase
            end

            if (reg_read) begin
                reg_ready <= 1;
                case (reg_addr)
                    ADDR_STATUS: reg_rdata <= {28'b0,
                                    hazard_detected_i,
                                    bist_fail_i,
                                    bist_pass_i,
                                    npu_done_i};
                    ADDR_OUT0: reg_rdata <= out0_i;
                    ADDR_OUT1: reg_rdata <= out1_i;
                    ADDR_OUT2: reg_rdata <= out2_i;
                    ADDR_OUT3: reg_rdata <= out3_i;
                    ADDR_CHIP_ID: reg_rdata <= 32'h4C41474E;
                    default: reg_rdata <= 32'h0;
                endcase
            end
        end
    end
endmodule
