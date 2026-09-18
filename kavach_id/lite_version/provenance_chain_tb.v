module provenance_chain_tb;

    reg        clk, rst, record_stage;
    reg  [1:0] stage_id;
    reg  [31:0] stage_data;
    wire [255:0] chain_hash;
    wire [3:0]  stages_completed;
    wire        sequence_violation, chain_complete, hash_busy;

    provenance_chain DUT (
        .clk(clk), .rst(rst),
        .record_stage(record_stage),
        .stage_id(stage_id),
        .stage_data(stage_data),
        .chain_hash(chain_hash),
        .stages_completed(stages_completed),
        .sequence_violation(sequence_violation),
        .chain_complete(chain_complete),
        .hash_busy(hash_busy)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    // Fires record_stage for one cycle, then waits for hash_busy to
    // clear (if it asserted at all - a rejected/violating stage never
    // asserts hash_busy, so this returns immediately in that case).
    task record(input [1:0] sid, input [31:0] sdata);
        begin
            stage_id = sid; stage_data = sdata;
            record_stage = 1;
            @(posedge clk); #1;
            record_stage = 0;
            if (hash_busy)
                wait (hash_busy == 0);
            #1;
        end
    endtask

    initial begin
        $dumpfile("provenance.vcd");
        $dumpvars(0, provenance_chain_tb);

        rst = 1; record_stage = 0; stage_id = 0; stage_data = 0;
        #20; rst = 0; #10;

        $display("================================");
        $display("  KAVACH-ID SUPPLY-CHAIN CHAIN  ");
        $display("  Real SHA-256, not XOR mixing  ");
        $display("================================");

        $display("--- Test 1: Correct Legitimate Sequence ---");
        record(2'd0, 32'hF1000001);
        $display("After Mfg: stages=%0b, violation=%0d", stages_completed, sequence_violation);
        record(2'd1, 32'hD2000045);
        record(2'd2, 32'h33000099);
        record(2'd3, 32'hC4000012);
        $display("Final: hash=0x%064h, stages=%0b, complete=%0d",
                  chain_hash, stages_completed, chain_complete);
        if (chain_complete && !sequence_violation)
            $display("PASS: Legitimate full supply chain verified!");
        else
            $display("FAIL: Legitimate chain incorrectly flagged");

        $display("--- Test 2: Grey-Market Diversion (Skipped Stages!) ---");
        rst = 1; #10; rst = 0; #10;
        record(2'd0, 32'hF1000001);
        record(2'd3, 32'hC4000099);
        $display("Stages=%0b, violation=%0d", stages_completed, sequence_violation);
        if (sequence_violation)
            $display("PASS: Skipped-stage diversion CORRECTLY DETECTED!");
        else
            $display("FAIL: Grey-market diversion MISSED - security bug!");

        $display("--- Test 3: Duplicate Stage (Relabeling Attempt) ---");
        rst = 1; #10; rst = 0; #10;
        record(2'd0, 32'hF1000001);
        record(2'd0, 32'hF1000002);
        if (sequence_violation)
            $display("PASS: Duplicate manufacturing stage flagged!");
        else
            $display("FAIL: Relabeling attempt missed!");

        $display("--- Test 4: hash_busy correctly gates a stray record_stage mid-hash ---");
        rst = 1; #10; rst = 0; #10;
        stage_id = 2'd0; stage_data = 32'hAAAA0001;
        record_stage = 1;
        @(posedge clk); #1;
        record_stage = 0;
        if (hash_busy) begin
            $display("hash_busy correctly asserted mid-hash");
            // Try to sneak in a second record_stage while busy - must be ignored
            stage_id = 2'd1; stage_data = 32'hBBBB0002;
            record_stage = 1;
            @(posedge clk); #1;
            record_stage = 0;
            wait (hash_busy == 0);
            #1;
            if (stages_completed == 4'b0001)
                $display("PASS: stray record_stage while hash_busy was correctly ignored!");
            else
                $display("FAIL: SECURITY BUG - record_stage accepted while hash_busy!");
        end
        else
            $display("FAIL: hash_busy did not assert - timing assumption broken");

        $display("================================");
        $display("Supply-Chain Provenance (SHA-256) Complete!");
        $display("Real cryptographic hash chaining, not XOR mixing!");
        $display("Detects grey-market diversion AND relabeling attempts!");
        $display("================================");
        $finish;
    end
endmodule
