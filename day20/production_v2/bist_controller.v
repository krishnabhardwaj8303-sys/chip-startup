module bist_controller(
    input  wire        clk,
    input  wire        rst,
    input  wire        start_bist,
    output reg         bist_pass,
    output reg         bist_fail,
    output reg         bist_done,
    output reg  [3:0]  bist_stage,     // Kaunsa test chal raha hai
    // Test hooks — actual hardware blocks se connect hote hain
    input  wire [7:0]  sbox_test_out,  // S-box se known input ka output
    input  wire [127:0] aes_test_out,  // AES se known vector ka output
    input  wire        puf_test_valid  // PUF se ek valid response mila
);
    parameter IDLE          = 4'd0;
    parameter TEST_SBOX     = 4'd1;
    parameter TEST_AES      = 4'd2;
    parameter TEST_PUF      = 4'd3;
    parameter TEST_MEMORY   = 4'd4;
    parameter DONE_PASS     = 4'd5;
    parameter DONE_FAIL     = 4'd6;

    reg [3:0]  state;
    reg [15:0] wait_counter;

    // Known-answer test vectors (KAT) — 
    // yeh chip power-up hone pe apne aap 
    // verify karta hai ki crypto blocks 
    // sahi kaam kar rahe hain
    parameter EXPECTED_SBOX = 8'h63;      // S[0x00] = 0x63
    parameter EXPECTED_AES  = 128'h3902dc1925dc116a8409850b1dfb9732;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state        <= IDLE;
            bist_pass    <= 0;
            bist_fail    <= 0;
            bist_done    <= 0;
            bist_stage   <= 0;
            wait_counter <= 0;
        end
        else begin
            case (state)
                IDLE: begin
                    bist_done <= 0;
                    bist_pass <= 0;
                    bist_fail <= 0;
                    if (start_bist) begin
                        state      <= TEST_SBOX;
                        bist_stage <= 1;
                    end
                end

                // Test 1: S-Box known-answer test
                TEST_SBOX: begin
                    if (sbox_test_out == EXPECTED_SBOX) begin
                        state      <= TEST_AES;
                        bist_stage <= 2;
                    end
                    else begin
                        state <= DONE_FAIL; // S-box galat — chip faulty!
                    end
                end

                // Test 2: AES core known-answer test
                TEST_AES: begin
                    if (aes_test_out == EXPECTED_AES) begin
                        state      <= TEST_PUF;
                        bist_stage <= 3;
                    end
                    else begin
                        state <= DONE_FAIL; // AES galat — chip faulty!
                    end
                end

                // Test 3: PUF response validity
                TEST_PUF: begin
                    if (puf_test_valid) begin
                        state      <= TEST_MEMORY;
                        bist_stage <= 4;
                    end
                    else begin
                        state <= DONE_FAIL;
                    end
                end

                // Test 4: Memory/register integrity 
                // (simplified — real chip mein march test hota hai)
                TEST_MEMORY: begin
                    if (wait_counter == 16'd100) begin
                        state      <= DONE_PASS;
                        bist_stage <= 5;
                    end
                    else
                        wait_counter <= wait_counter + 1;
                end

                DONE_PASS: begin
                    bist_pass <= 1;
                    bist_done <= 1;
                    state     <= IDLE;
                end

                DONE_FAIL: begin
                    // CRITICAL: Chip faulty hai — 
                    // isko production mein use 
                    // nahi karna chahiye!
                    bist_fail <= 1;
                    bist_done <= 1;
                    state     <= IDLE;
                end
            endcase
        end
    end
endmodule
