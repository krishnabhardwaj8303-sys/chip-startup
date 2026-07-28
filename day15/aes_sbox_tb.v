module aes_sbox_tb;

    reg  [7:0] in;
    wire [7:0] out;

    aes_sbox DUT (.in(in), .out(out));

    integer pass, fail;

    initial begin
        $dumpfile("sbox.vcd");
        $dumpvars(0, aes_sbox_tb);

        pass=0; fail=0;

        $display("================================");
        $display("   AES S-BOX NIST VERIFY TEST  ");
        $display("================================");

        // NIST official test vectors
        in=8'h00; #10;
        if(out==8'h63) begin pass=pass+1;
            $display("PASS: S[0x00]=0x%0h", out); end
        else begin fail=fail+1;
            $display("FAIL: S[0x00]=0x%0h exp 0x63", out); end

        in=8'h01; #10;
        if(out==8'h7c) begin pass=pass+1;
            $display("PASS: S[0x01]=0x%0h", out); end
        else begin fail=fail+1;
            $display("FAIL: S[0x01]=0x%0h exp 0x7c", out); end

        in=8'h53; #10;
        if(out==8'hed) begin pass=pass+1;
            $display("PASS: S[0x53]=0x%0h", out); end
        else begin fail=fail+1;
            $display("FAIL: S[0x53]=0x%0h exp 0xed", out); end

        in=8'hff; #10;
        if(out==8'h16) begin pass=pass+1;
            $display("PASS: S[0xff]=0x%0h", out); end
        else begin fail=fail+1;
            $display("FAIL: S[0xff]=0x%0h exp 0x16", out); end

        in=8'hf0; #10;
        if(out==8'h8c) begin pass=pass+1;
            $display("PASS: S[0xf0]=0x%0h", out); end
        else begin fail=fail+1;
            $display("FAIL: S[0xf0]=0x%0h exp 0x8c", out); end

        in=8'hab; #10;
        if(out==8'h62) begin pass=pass+1;
            $display("PASS: S[0xab]=0x%0h", out); end
        else begin fail=fail+1;
            $display("FAIL: S[0xab]=0x%0h exp 0x62", out); end

        $display("================================");
        $display("Results: %0d PASS, %0d FAIL", pass, fail);
        if(fail==0)
            $display("ALL NIST VECTORS PASS!");
        $display("Day 15 Complete! AES S-Box ready!");
        $display("BharatSE Block 1 DONE!");
        $display("================================");
        $finish;
    end
endmodule
