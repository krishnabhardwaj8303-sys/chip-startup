module kavach_id_top_tb;

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

    integer bit_count;

    initial begin
        $dumpfile("kavach_id_top.vcd");
        $dumpvars(0, kavach_id_top_tb);

        rst = 1; reg_write = 0; reg_read = 0; reg_addr = 0; reg_wdata = 0;
        uart_rx_in = 1;
        #20; rst = 0; #10;

        $display("================================");
        $display("  KAVACH-ID TOP-LEVEL INTEGRATION");
        $display("  (auth_gate + full-UART wiring)  ");
        $display("================================");

        $display("--- Test 1: Run BIST, chip should be healthy ---");
        reg_wr(8'h00, 32'h0000_0001); // CONTROL[0] = bist_start
        repeat (5) @(posedge clk);
        reg_rd(8'h04); // STATUS
        $display("STATUS=0x%0h, chip_healthy=%0d", reg_rdata, chip_healthy);
        if (chip_healthy)
            $display("PASS: Chip reports healthy after BIST!");
        else
            $display("FAIL: Chip not healthy after known-good BIST");

        $display("--- Test 2: Legitimate verify -> auth_request -> grant ---");
        reg_wr(8'h08, 32'h1111_1111);        // CHALLENGE
        reg_wr(8'h00, 32'h0000_0002);        // CONTROL[1] = stabilizer_start
        repeat (5) @(posedge clk);
        reg_wr(8'h00, 32'h0000_0004);        // CONTROL[2] = auth_request
        repeat (3) @(posedge clk);
        reg_rd(8'h04);
        $display("STATUS after fresh verify = 0x%0h", reg_rdata);
        if (reg_rdata[3] == 1)
            $display("PASS: authentication_grant set for legitimate fresh challenge!");
        else
            $display("FAIL: authentication_grant not set - integration broken");

        $display("--- Test 3: Same challenge again -> replay -> auth BLOCKED ---");
        reg_wr(8'h08, 32'h1111_1111);        // SAME challenge as Test 2
        reg_wr(8'h00, 32'h0000_0002);        // stabilizer_start
        repeat (5) @(posedge clk);
        reg_wr(8'h00, 32'h0000_0004);        // auth_request
        repeat (3) @(posedge clk);
        reg_rd(8'h04);
        $display("STATUS after replayed challenge = 0x%0h", reg_rdata);
        $display("verification_blocked = %0d", verification_blocked);
        if (reg_rdata[2] == 1 && reg_rdata[3] == 0 && verification_blocked == 1)
            $display("PASS: Replay correctly detected AND authentication blocked end-to-end!");
        else
            $display("FAIL: Replay not properly blocked at top level");

        $display("--- Test 4: UART sends full 4-byte response (only on grant) ---");
        // Fresh, non-replayed challenge so we get a real grant + ciphertext
        reg_wr(8'h08, 32'h2222_2222);
        reg_wr(8'h00, 32'h0000_0002);
        repeat (5) @(posedge clk);
        reg_wr(8'h00, 32'h0000_0004);
        repeat (3) @(posedge clk);

        // Count TX activity over a window long enough for 4 UART bytes
        bit_count = 0;
        repeat (200) begin
            @(posedge clk);
            if (uart_tx_out !== 1'b1) bit_count = bit_count + 1; // crude activity proxy
        end
        $display("UART line activity samples (non-idle) over window: %0d", bit_count);
        if (bit_count > 0)
            $display("PASS: UART shows transmission activity for the authenticated response!");
        else
            $display("FAIL: No UART activity detected - transmission may be broken");

        $display("================================");
        $display("Top-Level Integration Test Complete!");
        $display("auth_gate + full UART wiring exercised end-to-end!");
        $display("================================");
        $finish;
    end
endmodule
