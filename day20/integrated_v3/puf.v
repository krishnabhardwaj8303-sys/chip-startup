module puf(
    input  wire        clk,
    input  wire        rst,
    input  wire        enable,
    input  wire [7:0]  challenge,
    output reg  [63:0] response,
    output reg         valid
);
    // SRAM PUF simulation
    // Real chip mein: SRAM power-up state
    // random hoti hai per-chip — physically unique
    // Simulation mein: challenge-based deterministic model

    parameter IDLE    = 2'd0;
    parameter SAMPLE  = 2'd1;
    parameter PROCESS = 2'd2;
    parameter DONE    = 2'd3;

    reg [1:0]  state;
    reg [3:0]  count;
    reg [63:0] raw_bits;
    reg [63:0] chip_id;

    // Simulated per-chip unique ID
    // Real silicon mein yeh manufacturing variation se aata hai
    initial chip_id = 64'hDEADBEEF_CAFEBABE;

    // PUF response generation
    function [63:0] puf_response;
        input [7:0]  challenge;
        input [63:0] uid;
        reg   [63:0] resp;
        integer i;
        begin
            resp = uid;
            for (i=0; i<8; i=i+1) begin
                if (challenge[i])
                    resp = {resp[62:0], resp[63]} ^ uid;
                else
                    resp = {resp[0], resp[63:1]} ^ ~uid;
            end
            puf_response = resp;
        end
    endfunction

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state    <= IDLE;
            response <= 64'h0;
            valid    <= 0;
            count    <= 0;
            raw_bits <= 0;
        end
        else begin
            case (state)
                IDLE: begin
                    valid <= 0;
                    if (enable) begin
                        count    <= 0;
                        raw_bits <= 0;
                        state    <= SAMPLE;
                    end
                end

                SAMPLE: begin
                    raw_bits <= puf_response(challenge, chip_id);
                    count    <= count + 1;
                    if (count == 4'd7)
                        state <= PROCESS;
                end

                PROCESS: begin
                    // Von Neumann debiasing
                    response <= raw_bits ^ (raw_bits >> 32);
                    state    <= DONE;
                end

                DONE: begin
                    valid <= 1;
                    state <= IDLE;
                end
            endcase
        end
    end
endmodule
