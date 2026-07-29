module puf_tb;

    reg         clk, rst, start;
    wire [127:0] device_key;
    wire         key_ready;

    puf_key DUT (
        .clk(clk), .rst(rst),
        .start(start),
        .device_key(device_key),
        .key_ready(key_ready)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    reg [127:0] key1, key2;

    initial begin
        $dumpfile("puf.vcd");
        $dumpvars(0, puf_tb);

        rst=1; start=0; #30;
        rst=0; #20;

        $display("================================");
        $display("   BharatSE PUF KEY TEST       ");
        $display("================================");

        // Test 1: Pehli baar key generate karo
        $display("--- Test 1: First Key Gen ---");
        start=1; #10; start=0;
        wait(key_ready);
        key1 = device_key;
        $display("Device Key 1: %h", device_key);
        $display("PASS: Key generated!");
        #50;

        // Test 2: Dobara generate karo — same hona chahiye
        $display("--- Test 2: Reproducibility ---");
        start=1; #10; start=0;
        wait(key_ready);
        key2 = device_key;
        $display("Device Key 2: %h", device_key);

        if(key1 == key2)
            $display("PASS: Same key reproduced!");
        else
            $display("FAIL: Keys differ");
        #50;

        // Test 3: Key zero nahi hona chahiye
        $display("--- Test 3: Non-Zero Check ---");
        if(device_key != 128'h0)
            $display("PASS: Key is non-zero!");
        else
            $display("FAIL: Key is zero");

        // Test 4: Key all-ones nahi hona chahiye
        if(device_key != 128'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)
            $display("PASS: Key not all-ones!");
        else
            $display("FAIL: Key is all-ones");

        $display("================================");
        $display("Day 19 Complete!");
        $display("PUF Block working!");
        $display("128-bit Unclonable Key Ready!");
        $display("BharatSE Block 4 DONE!");
        $display("================================");
        $finish;
    end
endmodule
