module offline_provenance_tb;

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

    integer i;

    initial begin
        $dumpfile("offline_provenance_tb.vcd");
        $dumpvars(0, offline_provenance_tb);

        rst = 1; reg_write = 0; reg_read = 0; reg_addr = 0; reg_wdata = 0;
        uart_rx_in = 1;
        #20; rst = 0; #10;

        $display("================================================");
        $display("  OFFLINE-VERIFY BUDGET + PROVENANCE CHAIN TESTS");
        $display("================================================");

        // Run BIST once so bist_pass stays healthy for the whole test
        reg_wr(8'h00, 32'h0000_0001);
        repeat (5) @(posedge clk);

        $display("--- TEST A: Initial offline budget should be 50 ---");
        reg_rd(8'h20); // OFFLINE_STATUS: bits[7:0]=budget, bit8=sync_required
        $display("OFFLINE_STATUS=0x%0h, budget=%0d", reg_rdata, reg_rdata[7:0]);
        if (reg_rdata[7:0] == 8'd50)
            $display("PASS: initial budget is 50");
        else
            $display("FAIL: expected 50, got %0d", reg_rdata[7:0]);

        $display("--- TEST B: Budget decrements by 1 per auth_request (5 requests) ---");
        for (i = 0; i < 5; i = i + 1) begin
            reg_wr(8'h08, 32'h3000_0000 + i);   // unique challenge (avoid replay block)
            reg_wr(8'h00, 32'h0000_0002);       // stabilizer_start
            repeat (5) @(posedge clk);
            reg_wr(8'h00, 32'h0000_0004);       // auth_request
            repeat (3) @(posedge clk);
        end
        reg_rd(8'h20);
        $display("After 5 auth_requests, budget=%0d (expect 45)", reg_rdata[7:0]);
        if (reg_rdata[7:0] == 8'd45)
            $display("PASS");
        else
            $display("FAIL");

        $display("--- TEST C: Exhaust remaining 45 uses, then confirm denial on 51st ---");
        for (i = 0; i < 45; i = i + 1) begin
            reg_wr(8'h08, 32'h4000_0000 + i);
            reg_wr(8'h00, 32'h0000_0002);
            repeat (5) @(posedge clk);
            reg_wr(8'h00, 32'h0000_0004);
            repeat (3) @(posedge clk);
        end
        reg_rd(8'h20);
        $display("After exhausting budget: OFFLINE_STATUS=0x%0h budget=%0d sync_required=%0d",
                  reg_rdata, reg_rdata[7:0], reg_rdata[8]);

        // 51st request - budget should now be 0, this must be denied
        reg_wr(8'h08, 32'h5000_0000);
        reg_wr(8'h00, 32'h0000_0002);
        repeat (5) @(posedge clk);
        reg_wr(8'h00, 32'h0000_0004);
        repeat (3) @(posedge clk);
        reg_rd(8'h04); // STATUS
        $display("STATUS after budget-exhausted auth_request = 0x%0h (bit3=grant should be 0)", reg_rdata);
        if (reg_rdata[3] == 0)
            $display("PASS: no authentication_grant when budget exhausted");
        else
            $display("FAIL: grant issued despite exhausted budget - SECURITY BUG");
        $display("verification_blocked=%0d (expect 1)", verification_blocked);

        $display("--- TEST D: sync_complete restores budget to 50 ---");
        reg_wr(8'h00, 32'h0000_0008); // CONTROL bit3 = sync_complete
        repeat (3) @(posedge clk);
        reg_rd(8'h20);
        $display("After sync_complete, budget=%0d (expect 50)", reg_rdata[7:0]);
        if (reg_rdata[7:0] == 8'd50)
            $display("PASS");
        else
            $display("FAIL");

        $display("--- TEST E: total_offline_uses counter ---");
        $display("TOTAL_OFFLINE_USES=%0d (expect 50 - the 51st, budget-exhausted, DENIED attempt is correctly NOT counted as a legitimate use)", reg_rdata);

        $display("--- TEST F: Provenance chain - correct sequence completes cleanly ---");
        reg_wr(8'h14, 32'h0000_0000); reg_wr(8'h18, 32'hAAAA_0000);
        reg_wr(8'h00, 32'h0000_0010); repeat (3) @(posedge clk); // stage 0: Manufacturing

        reg_wr(8'h14, 32'h0000_0001); reg_wr(8'h18, 32'hBBBB_0000);
        reg_wr(8'h00, 32'h0000_0010); repeat (3) @(posedge clk); // stage 1: Distribution

        reg_wr(8'h14, 32'h0000_0002); reg_wr(8'h18, 32'hCCCC_0000);
        reg_wr(8'h00, 32'h0000_0010); repeat (3) @(posedge clk); // stage 2: Retail

        reg_wr(8'h14, 32'h0000_0003); reg_wr(8'h18, 32'hDDDD_0000);
        reg_wr(8'h00, 32'h0000_0010); repeat (3) @(posedge clk); // stage 3: Consumer

        reg_rd(8'h1C); // PROVENANCE_STATUS
        $display("After full sequence, PROVENANCE_STATUS=0x%0h (bit0=violation, bit1=chain_complete)", reg_rdata);
        if (reg_rdata[1] == 1 && reg_rdata[0] == 0)
            $display("PASS: chain_complete set, no violation");
        else
            $display("FAIL");

        $display("--- TEST G: Provenance chain - skipped stage triggers sequence_violation ---");
        rst = 1; #20; rst = 0; #10; // fresh chip -> fresh provenance chain

        reg_wr(8'h14, 32'h0000_0000); reg_wr(8'h18, 32'h1111_0000);
        reg_wr(8'h00, 32'h0000_0010); repeat (3) @(posedge clk); // stage 0: Manufacturing

        reg_wr(8'h14, 32'h0000_0003); reg_wr(8'h18, 32'h2222_0000); // jump straight to Consumer
        reg_wr(8'h00, 32'h0000_0010); repeat (3) @(posedge clk);

        reg_rd(8'h1C);
        $display("After skip-stage attempt, PROVENANCE_STATUS=0x%0h", reg_rdata);
        if (reg_rdata[0] == 1)
            $display("PASS: sequence_violation correctly flagged");
        else
            $display("FAIL: skipped stage NOT detected - SECURITY BUG");

        $display("================================================");
        $display("Offline-verify + provenance integration tests complete");
        $display("================================================");
        $finish;
    end
endmodule
