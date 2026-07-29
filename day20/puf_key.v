module puf_key(
    input  wire        clk,
    input  wire        rst,
    input  wire        start,
    output reg  [127:0] device_key,
    output reg          key_ready
);
    wire [63:0] puf_resp1, puf_resp2;
    wire        puf_valid1, puf_valid2;
    reg         puf_en1, puf_en2;

    // Two PUF instances — 64+64 = 128-bit key
    puf PUF1 (
        .clk(clk), .rst(rst),
        .enable(puf_en1),
        .challenge(8'hA5),
        .response(puf_resp1),
        .valid(puf_valid1)
    );

    puf PUF2 (
        .clk(clk), .rst(rst),
        .enable(puf_en2),
        .challenge(8'h5A),
        .response(puf_resp2),
        .valid(puf_valid2)
    );

    parameter IDLE    = 3'd0;
    parameter PUF1_EN = 3'd1;
    parameter WAIT1   = 3'd2;
    parameter PUF2_EN = 3'd3;
    parameter WAIT2   = 3'd4;
    parameter COMBINE = 3'd5;

    reg [2:0] state;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state      <= IDLE;
            puf_en1    <= 0;
            puf_en2    <= 0;
            device_key <= 0;
            key_ready  <= 0;
        end
        else begin
            case (state)
                IDLE: begin
                    key_ready <= 0;
                    if (start) begin
                        puf_en1 <= 1;
                        state   <= PUF1_EN;
                    end
                end

                PUF1_EN: begin
                    puf_en1 <= 0;
                    state   <= WAIT1;
                end

                WAIT1: begin
                    if (puf_valid1) begin
                        puf_en2 <= 1;
                        state   <= PUF2_EN;
                    end
                end

                PUF2_EN: begin
                    puf_en2 <= 0;
                    state   <= WAIT2;
                end

                WAIT2: begin
                    if (puf_valid2)
                        state <= COMBINE;
                end

                COMBINE: begin
                    // 128-bit key = PUF1 || PUF2
                    device_key <= {puf_resp1, puf_resp2};
                    key_ready  <= 1;
                    state      <= IDLE;
                end
            endcase
        end
    end
endmodule
