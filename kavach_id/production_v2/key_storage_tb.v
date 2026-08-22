module key_storage_tb;

    reg         clk, rst;
    reg         reg_write, reg_read;
    reg  [7:0]  reg_addr;
    reg  [31:0] reg_wdata;
    wire [31:0] reg_rdata;
    wire        reg_ready;
    reg         uart_rx_in;
    wire        uart_tx_out;
    wire        chip_healthy, verification_blocked;

    kavach_id_top DUT (
        .clk(clk), .rst(rst),
        .reg_write(reg_write), .reg_read(reg_read),
        .reg_addr(reg_addr), .reg_wdata(reg_wdata),
        .reg_rdata(reg_rdata), .reg_ready(reg_ready),
        .uart_rx_in(uart_rx_in), .uart_tx_out(uart_tx_out),
        .chip_healthy(chip_healthy),
        .verification_blocked(verification_blocked)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    task reg_wr(input [7:0] addr, input [31:0] data);
        begin
            reg_addr = addr; reg_wdata = data; reg_write = 1;
            @(posedge clk); #1;
            reg_write = 0;
            @(posedge clk); #1;
        end
    endtask

    task reg_rd(input [7:0] addr);
        begin
            reg_addr = addr; reg_read = 1;
            @(posedge clk); #1;
            reg_read = 0;
            @(posedge clk); #1;
        end
    endtask

    initial begin
        rst = 1; reg_write = 0; reg_read = 0; reg_addr = 0; reg_wdata = 0;
        uart_rx_in = 1;
        #20; rst = 0; #30;

        $display("================================================");
        $display("  PER-CHIP KEY STORAGE TESTS");
        $display("================================================");

        $display("--- TEST A: Key starts unprogrammed (key_locked = 0) ---");
        reg_rd(8'h30); // KEY_STATUS
        $display("KEY_STATUS=0x%0h (expect bit0=0)", reg_rdata);
        if (reg_rdata[0] == 0)
            $display("PASS: key starts unlocked");
        else
            $display("FAIL");

        $display("--- TEST B: Program a key, confirm it locks ---");
        reg_wr(8'h28, 32'hCAFEF00D);  // KEY_DATA
        reg_wr(8'h2C, 32'h0000_0001); // KEY_CONTROL bit0 = prog_enable
        repeat (3) @(posedge clk);
        reg_rd(8'h30);
        $display("KEY_STATUS=0x%0h (expect bit0=1)", reg_rdata);
        if (reg_rdata[0] == 1)
            $display("PASS: key is now locked");
        else
            $display("FAIL");

        $display("--- TEST C: Attempt to reprogram - must be rejected ---");
        reg_wr(8'h28, 32'hDEADBEEF);  // try a DIFFERENT key
        reg_wr(8'h2C, 32'h0000_0001); // try to re-trigger prog_enable
        repeat (3) @(posedge clk);
        $display("chip_key internal value = 0x%0h (expect still 0xCAFEF00D, NOT 0xDEADBEEF)", DUT.chip_key_w);
        if (DUT.chip_key_w == 32'hCAFEF00D)
            $display("PASS: second programming attempt correctly rejected, original key preserved");
        else
            $display("FAIL: SECURITY BUG - key was overwritten after lock");

        $display("================================================");
        $display("Key storage tests complete");
        $display("================================================");
        $finish;
    end
endmodule
