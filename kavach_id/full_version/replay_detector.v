module replay_detector(
    input  wire        clk,
    input  wire        rst,
    input  wire        challenge_ready,
    input  wire [31:0] challenge_in,
    output reg          replay_detected,
    output reg  [31:0]  last_challenge,
    output reg  [7:0]   history_hit_count
);
    // Real authentication attack: attacker records ek 
    // valid challenge-response pair aur baad mein SAME 
    // challenge dobara bhejta hai, expecting same response.
    //
    // Production defense: chip ko yaad rakhna chahiye 
    // recent challenges — agar same challenge dobara aaye 
    // (thoda time ke andar), yeh SUSPICIOUS hai.
    //
    // Simple history buffer — last 4 challenges track karte hain

    reg [31:0] history [0:3];
    reg [1:0]  history_ptr;
    integer i;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            replay_detected   <= 0;
            last_challenge    <= 0;
            history_hit_count <= 0;
            history_ptr       <= 0;
            history[0] <= 0; history[1] <= 0; 
            history[2] <= 0; history[3] <= 0;
        end
        else if (challenge_ready) begin
            replay_detected <= 0;

            // Check karo ki yeh challenge history mein hai kya
            for (i = 0; i < 4; i = i + 1) begin
                if (history[i] == challenge_in && 
                    challenge_in != 32'h0) begin
                    replay_detected   <= 1;
                    history_hit_count <= history_hit_count + 1;
                end
            end

            // Naya challenge history mein add karo (circular buffer)
            history[history_ptr] <= challenge_in;
            history_ptr <= history_ptr + 1;
            last_challenge <= challenge_in;
        end
    end
endmodule
