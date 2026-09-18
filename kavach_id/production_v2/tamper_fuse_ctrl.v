module tamper_fuse_ctrl #(
    parameter integer DEBOUNCE_CYCLES = 4
)(
    input  wire clk,
    input  wire rst_n,
    input  wire continuity_loop_ok,
    output reg  tamper_fuse_tripped,
    output wire auth_block
);

    localparam integer CW = (DEBOUNCE_CYCLES <= 1) ? 1 : $clog2(DEBOUNCE_CYCLES + 1);
    reg [CW-1:0] break_count;

    initial tamper_fuse_tripped = 1'b0;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            break_count <= {CW{1'b0}};
        end else begin
            if (!continuity_loop_ok) begin
                if (break_count < DEBOUNCE_CYCLES[CW-1:0])
                    break_count <= break_count + 1'b1;
            end else begin
                break_count <= {CW{1'b0}};
            end

            if (break_count == DEBOUNCE_CYCLES[CW-1:0])
                tamper_fuse_tripped <= 1'b1;
        end
    end

    assign auth_block = tamper_fuse_tripped;

endmodule
