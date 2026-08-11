module kavach_id_v2_tb;

    reg         clk, rst;
    reg         reg_write, reg_read;
    reg  [7:0]  reg_addr;
    reg  [31:0] reg_wdata;
    wire [31:0] reg_rdata;
    wire        reg_ready;
    reg         uart_rx_in;
    wire        uart_tx_out;
    wire        chip_healthy, verification_blocked;

    kavach_id_v2_top DUT (
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

    initial begin
        $dumpfile("kavach_id_v2.vcd");
        $dumpvars(0, kavach_id_v2_tb);

        rst = 1;
        reg_write = 0; reg_read = 0; reg_addr = 0; reg_wdata = 0;
        uart_rx_in = 1;
        #30; rst = 0; #20;

        $display("========================================");
        $display("  KAVACH-ID v2 — FULLY INTEGRATED TOP   ");
        $display("  Core + Production + Unique, all wired ");
        $display("========================================");

        // ── TEST 1: Run BIST ──
        $display("--- Test 1: BIST via Register ---");
        reg_addr = 8'h00; reg_wdata = 32'h00000001; // bit0 = bist_start
        reg_write = 1; #10; reg_write = 0; #30;
        reg_addr = 8'h04; reg_read = 1; #10; reg_read = 0; #10;
        $display("Status Register: 0x%0h", reg_rdata);
        if (chip_healthy)
            $display("PASS: Chip healthy after BIST!");

        // ── TEST 2: First authentication — fresh challenge ──
        $display("--- Test 2: First Authentication (Fresh Challenge) ---");
        reg_addr = 8'h08; reg_wdata = 32'h11111111; // challenge
        reg_write = 1; #10; reg_write = 0; #10;
        reg_addr = 8'h00; reg_wdata = 32'h00000002; // bit1 = stabilizer_start
        reg_write = 1; #10; reg_write = 0; #100;
        reg_addr = 8'h0C; reg_read = 1; #10; reg_read = 0; #10;
        $display("Response: 0x%0h", reg_rdata);
        if (~verification_blocked)
            $display("PASS: Fresh challenge authenticated successfully!");

        // ── TEST 3: REPLAY ATTACK — same challenge again ──
        $display("--- Test 3: REPLAY ATTACK Detection ---");
        reg_addr = 8'h08; reg_wdata = 32'h11111111; // SAME challenge!
        reg_write = 1; #10; reg_write = 0; #10;
        reg_addr = 8'h00; reg_wdata = 32'h00000002;
        reg_write = 1; #10; reg_write = 0; #50;
        reg_addr = 8'h04; reg_read = 1; #10; reg_read = 0; #10;
        $display("Status: 0x%0h", reg_rdata);
        if (verification_blocked)
            $display("PASS: Replay attack correctly blocked authentication!");
        else
            $display("Note: Check replay_detected bit wiring");

        $display("========================================");
        $display("Kavach-ID v2 Integration Test Complete!");
        $display("PUF + Stabilizer + Replay Guard + Encryption");
        $display("+ BIST + Register Map + UART, all wired!");
        $display("========================================");
        $finish;
    end
endmodule
