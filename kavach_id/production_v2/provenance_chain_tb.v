module provenance_chain_tb;

    reg        clk, rst, record_stage;
    reg  [1:0] stage_id;
    reg  [31:0] stage_data;
    wire [31:0] chain_hash;
    wire [3:0]  stages_completed;
    wire        sequence_violation, chain_complete;

    provenance_chain DUT (
        .clk(clk), .rst(rst),
        .record_stage(record_stage),
        .stage_id(stage_id),
        .stage_data(stage_data),
        .chain_hash(chain_hash),
        .stages_completed(stages_completed),
        .sequence_violation(sequence_violation),
        .chain_complete(chain_complete)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("provenance.vcd");
        $dumpvars(0, provenance_chain_tb);

        rst = 1; record_stage = 0; stage_id = 0; stage_data = 0;
        #20; rst = 0; #10;

        $display("================================");
        $display("  KAVACH-ID SUPPLY-CHAIN CHAIN ");
        $display("  Unique: Full Provenance Track ");
        $display("================================");

        $display("--- Test 1: Correct Legitimate Sequence ---");
        stage_id = 2'd0; stage_data = 32'hF1000001;
        record_stage = 1; #10; record_stage = 0; #10;
        $display("After Mfg: hash=0x%0h, stages=%0b, violation=%0d",
                  chain_hash, stages_completed, sequence_violation);

        stage_id = 2'd1; stage_data = 32'hD2000045;
        record_stage = 1; #10; record_stage = 0; #10;

        stage_id = 2'd2; stage_data = 32'h33000099;
        record_stage = 1; #10; record_stage = 0; #10;

        stage_id = 2'd3; stage_data = 32'hC4000012;
        record_stage = 1; #10; record_stage = 0; #10;
        $display("Final: hash=0x%0h, stages=%0b, complete=%0d",
                  chain_hash, stages_completed, chain_complete);
        if (chain_complete && !sequence_violation)
            $display("PASS: Legitimate full supply chain verified!");
        else
            $display("FAIL: Legitimate chain incorrectly flagged");

        $display("--- Test 2: Grey-Market Diversion (Skipped Stages!) ---");
        rst = 1; #10; rst = 0; #10;
        stage_id = 2'd0; stage_data = 32'hF1000001;
        record_stage = 1; #10; record_stage = 0; #10;

        stage_id = 2'd3; stage_data = 32'hC4000099;
        record_stage = 1; #10; record_stage = 0; #10;
        $display("Stages=%0b, violation=%0d", stages_completed, sequence_violation);
        if (sequence_violation)
            $display("PASS: Skipped-stage diversion CORRECTLY DETECTED!");
        else
            $display("FAIL: Grey-market diversion MISSED - security bug!");

        $display("--- Test 3: Duplicate Stage (Relabeling Attempt) ---");
        rst = 1; #10; rst = 0; #10;
        stage_id = 2'd0; stage_data = 32'hF1000001;
        record_stage = 1; #10; record_stage = 0; #10;
        stage_id = 2'd0; stage_data = 32'hF1000002;
        record_stage = 1; #10; record_stage = 0; #10;
        if (sequence_violation)
            $display("PASS: Duplicate manufacturing stage flagged!");
        else
            $display("FAIL: Relabeling attempt missed!");

        $display("================================");
        $display("Supply-Chain Provenance Complete!");
        $display("Detects grey-market diversion AND");
        $display("relabeling/re-manufacturing attempts!");
        $display("================================");
        $finish;
    end
endmodule
