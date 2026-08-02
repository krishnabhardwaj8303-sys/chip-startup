module register_map_tb;

    reg        clk, rst;
    reg        reg_write, reg_read;
    reg  [7:0] reg_addr;
    reg  [31:0] reg_wdata;
    wire [31:0] reg_rdata;
    wire        reg_ready;

    reg         bist_pass_i, bist_fail_i;
    reg         wdt_timeout_i, glitch_detected_i;
    reg         aes_done_i;
    reg  [127:0] aes_result_i;

    wire        aes_start_o, bist_start_o, wdt_enable_o;
    wire [127:0] aes_key_o, aes_plaintext_o;

    register_map DUT (
        .clk(clk), .rst(rst),
        .reg_write(reg_write), .reg_read(reg_read),
        .reg_addr(reg_addr), .reg_wdata(reg_wdata),
        .reg_rdata(reg_rdata), .reg_ready(reg_ready),
        .bist_pass_i(bist_pass_i), .bist_fail_i(bist_fail_i),
        .wdt_timeout_i(wdt_timeout_i), 
        .glitch_detected_i(glitch_detected_i),
        .aes_done_i(aes_done_i), .aes_result_i(aes_result_i),
        .aes_start_o(aes_start_o), .bist_start_o(bist_start_o),
        .wdt_enable_o(wdt_enable_o),
        .aes_key_o(aes_key_o), .aes_plaintext_o(aes_plaintext_o)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    // Pulse ko latch karke rakho taaki miss na ho
    reg aes_start_seen;
    always @(posedge aes_start_o) aes_start_seen = 1;

    initial begin
        $dumpfile("register_map.vcd");
        $dumpvars(0, register_map_tb);

        rst = 1;
        reg_write = 0; reg_read = 0; reg_addr = 0; reg_wdata = 0;
        bist_pass_i = 0; bist_fail_i = 0;
        wdt_timeout_i = 0; glitch_detected_i = 0;
        aes_done_i = 0; aes_result_i = 0;
        aes_start_seen = 0;
        #20; rst = 0; #10;

        $display("================================");
        $display("  REGISTER MAP INTERFACE TEST  ");
        $display("  Production Chip Control I/F   ");
        $display("================================");

        $display("--- Test 1: Read Chip ID ---");
        reg_addr = 8'hFC; reg_read = 1; #10; reg_read = 0; #10;
        if (reg_rdata == 32'h4E45454C)
            $display("PASS: Chip ID = 0x%0h (NEEL)", reg_rdata);
        else
            $display("FAIL: Chip ID = 0x%0h", reg_rdata);

        $display("--- Test 2: Write AES Key ---");
        reg_addr = 8'h08; reg_wdata = 32'h2B7E1516; 
        reg_write = 1; #10; reg_write = 0; #10;
        reg_addr = 8'h0C; reg_wdata = 32'h28AED2A6; 
        reg_write = 1; #10; reg_write = 0; #10;
        if (aes_key_o[127:96] == 32'h2B7E1516)
            $display("PASS: AES Key register write working!");
        else
            $display("FAIL: Key not written correctly");

        $display("--- Test 3: Control Register (AES Start) ---");
        reg_addr = 8'h00; reg_wdata = 32'h00000001;
        reg_write = 1; #10; reg_write = 0; #10;
        if (aes_start_seen)
            $display("PASS: AES start signal triggered via register!");
        else
            $display("FAIL: AES start not triggered");

        $display("--- Test 4: Status Register Read ---");
        bist_pass_i = 1; aes_done_i = 1;
        reg_addr = 8'h04; reg_read = 1; #10; reg_read = 0; #10;
        if (reg_rdata[0] == 1 && reg_rdata[1] == 1)
            $display("PASS: Status register reflects AES done + BIST pass!");
        else
            $display("FAIL: Status register incorrect: 0x%0h", reg_rdata);

        $display("--- Test 5: AES Result Read ---");
        aes_result_i = 128'hDEADBEEFCAFEBABE1234567890ABCDEF;
        reg_addr = 8'h28; reg_read = 1; #10; reg_read = 0; #10;
        if (reg_rdata == 32'hDEADBEEF)
            $display("PASS: AES result readable via register: 0x%0h", 
                      reg_rdata);
        else
            $display("FAIL: Result mismatch: 0x%0h", reg_rdata);

        $display("================================");
        $display("Phase 3 Complete!");
        $display("Register-Mapped Interface working!");
        $display("================================");
        $finish;
    end
endmodule
