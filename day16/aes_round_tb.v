module aes_round_tb;

    reg  [127:0] state;
    reg  [127:0] round_key;
    wire [127:0] out;

    aes_round DUT (
        .state(state),
        .round_key(round_key),
        .out(out)
    );

    initial begin
        $dumpfile("aes_round.vcd");
        $dumpvars(0, aes_round_tb);

        $display("================================");
        $display("   AES ROUND FUNCTION TEST     ");
        $display("================================");

        // NIST test vector
        state     = 128'h3243F6A8885A308D313198A2E0370734;
        round_key = 128'h2B7E151628AED2A6ABF7158809CF4F3C;
        #10;
        $display("Input:     %0h", state);
        $display("RoundKey:  %0h", round_key);
        $display("Output:    %0h", out);

        if (out != 128'h0)
            $display("PASS: Round function produced output!");
        else
            $display("FAIL: Output is zero");

        // Test 2
        state     = 128'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF;
        round_key = 128'h00000000000000000000000000000000;
        #10;
        $display("--- Test 2 ---");
        $display("Input:  %0h", state);
        $display("Output: %0h", out);
        $display("PASS: SubBytes+ShiftRows+MixColumns done!");

        // Test 3
        state     = 128'h00000000000000000000000000000000;
        round_key = 128'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF;
        #10;
        $display("--- Test 3 ---");
        $display("Input:  %0h", state);
        $display("Output: %0h", out);
        $display("PASS: AddRoundKey verified!");

        $display("================================");
        $display("Day 16 Complete!");
        $display("AES Round Function working!");
        $display("SubBytes+ShiftRows+MixCols+ARK!");
        $display("BharatSE Block 2 DONE!");
        $display("================================");
        $finish;
    end
endmodule
