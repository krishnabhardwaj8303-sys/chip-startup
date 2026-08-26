module key_storage_tb;

    reg          clk, rst;
    reg          prog_enable;
    reg  [127:0] prog_key_in;
    wire [127:0] chip_key;
    wire         key_locked;

    key_storage DUT (
        .clk(clk), .rst(rst),
        .prog_enable(prog_enable),
        .prog_key_in(prog_key_in),
        .chip_key(chip_key),
        .key_locked(key_locked)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst = 1; prog_enable = 0; prog_key_in = 0;
        #20; rst = 0; #10;

        $display("================================");
        $display("  KEY_STORAGE TEST (128-bit)   ");
        $display("================================");

        $display("--- Test 1: Unprogrammed state ---");
        if (chip_key == 128'h0 && key_locked == 0)
            $display("PASS: chip_key=0, key_locked=0 after reset!");
        else
            $display("FAIL: unexpected reset state");

        $display("--- Test 2: Program 128-bit key, locks ---");
        prog_key_in = 128'h000102030405060708090a0b0c0d0e0f;
        prog_enable = 1;
        @(posedge clk); #1;
        prog_enable = 0;
        #1;
        if (chip_key == 128'h000102030405060708090a0b0c0d0e0f && key_locked == 1)
            $display("PASS: full 128-bit key programmed and locked!");
        else
            $display("FAIL: got chip_key=0x%032h, locked=%0d", chip_key, key_locked);

        $display("--- Test 3: Write-after-lock rejected ---");
        prog_key_in = 128'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF;
        prog_enable = 1;
        @(posedge clk); #1;
        prog_enable = 0;
        #1;
        if (chip_key == 128'h000102030405060708090a0b0c0d0e0f)
            $display("PASS: locked key rejected the new write attempt!");
        else
            $display("FAIL: SECURITY BUG - locked key was overwritten!");

        $display("--- Test 4: Reset allows reprogramming ---");
        rst = 1; #10; rst = 0; #10;
        if (chip_key == 128'h0 && key_locked == 0)
            $display("PASS: reset correctly clears key and lock!");
        else
            $display("FAIL: reset did not clear key/lock state");

        prog_key_in = 128'h1;
        prog_enable = 1;
        @(posedge clk); #1;
        prog_enable = 0; #1;
        if (chip_key == 128'h1 && key_locked == 1)
            $display("PASS: reprogramming after reset works correctly!");
        else
            $display("FAIL: reprogramming after reset failed");

        $display("================================");
        $display("key_storage.v Complete!");
        $display("================================");
        $finish;
    end
endmodule
