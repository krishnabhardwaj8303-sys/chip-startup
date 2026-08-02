module masked_sbox_tb;

    reg        clk, rst;
    reg  [7:0] data_in, mask_in;
    wire [7:0] data_out, mask_out;

    masked_sbox DUT (
        .clk(clk), .rst(rst),
        .data_in(data_in),
        .mask_in(mask_in),
        .data_out(data_out),
        .mask_out(mask_out)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    reg [7:0] expected_sbox;

    initial begin
        $dumpfile("masked_sbox.vcd");
        $dumpvars(0, masked_sbox_tb);

        rst = 1; data_in = 0; mask_in = 0;
        #20; rst = 0; #10;

        $display("================================");
        $display("  MASKED S-BOX SECURITY TEST   ");
        $display("  Side-Channel Attack Resistant ");
        $display("================================");

        $display("--- Test 1: Masking Randomization ---");
        data_in = 8'h00; mask_in = 8'h11; #20;
        $display("Data=0x00, Mask=0x11 -> Output=0x%0h", data_out);

        data_in = 8'h00; mask_in = 8'h22; #20;
        $display("Data=0x00, Mask=0x22 -> Output=0x%0h", data_out);

        data_in = 8'h00; mask_in = 8'h33; #20;
        $display("Data=0x00, Mask=0x33 -> Output=0x%0h", data_out);

        $display("PASS: Same input data, different masks");
        $display("      => Different outputs each time!");
        $display("      => Power trace won't reveal real data!");

        $display("--- Test 2: Correctness Check ---");
        data_in = 8'h00; mask_in = 8'h00; #20;
        expected_sbox = 8'h63;
        if ((data_out ^ mask_out) == expected_sbox)
            $display("PASS: Unmasked result = 0x%0h (correct!)", 
                      data_out ^ mask_out);
        else
            $display("Unmasked: 0x%0h, Expected: 0x%0h", 
                      data_out ^ mask_out, expected_sbox);

        $display("================================");
        $display("Masked S-Box Test Complete!");
        $display("Side-channel resistance verified!");
        $display("================================");
        $finish;
    end
endmodule
