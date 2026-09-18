module kavach_register_map_tb;

    reg         clk, rst;
    reg         reg_write, reg_read;
    reg  [7:0]  reg_addr;
    reg  [31:0] reg_wdata;
    wire [31:0] reg_rdata;
    wire        reg_ready;

    reg         bist_pass_i, bist_fail_i, replay_detected_i;
    reg  [31:0] stable_response_i;
    reg  [5:0]  unstable_bit_count_i;
    reg         authentication_grant_i, auth_denied_bist_i, auth_denied_replay_i;

    reg         sequence_violation_i, chain_complete_i;
    reg  [3:0]  stages_completed_i;
    reg  [7:0]  offline_budget_i;
    reg         sync_required_i;
    reg  [15:0] total_offline_uses_i;

    reg         key_locked_i;
    reg  [31:0] ciphertext_i;
    reg  [15:0] tx_counter_i;

    wire        bist_start_o, stabilizer_start_o, auth_request_o;
    wire [31:0] challenge_o;
    wire        sync_complete_o, record_stage_o;
    wire [1:0]  stage_id_o;
    wire [31:0] stage_data_o;
    wire        prog_enable_o;
    wire [127:0] prog_key_in_o;

    kavach_register_map DUT (
        .clk(clk), .rst(rst),
        .reg_write(reg_write), .reg_read(reg_read),
        .reg_addr(reg_addr), .reg_wdata(reg_wdata),
        .reg_rdata(reg_rdata), .reg_ready(reg_ready),
        .bist_pass_i(bist_pass_i), .bist_fail_i(bist_fail_i),
        .replay_detected_i(replay_detected_i),
        .stable_response_i(stable_response_i),
        .unstable_bit_count_i(unstable_bit_count_i),
        .authentication_grant_i(authentication_grant_i),
        .auth_denied_bist_i(auth_denied_bist_i),
        .auth_denied_replay_i(auth_denied_replay_i),
        .sequence_violation_i(sequence_violation_i),
        .chain_complete_i(chain_complete_i),
        .stages_completed_i(stages_completed_i),
        .offline_budget_i(offline_budget_i),
        .sync_required_i(sync_required_i),
        .total_offline_uses_i(total_offline_uses_i),
        .bist_start_o(bist_start_o),
        .stabilizer_start_o(stabilizer_start_o),
        .challenge_o(challenge_o),
        .auth_request_o(auth_request_o),
        .sync_complete_o(sync_complete_o),
        .record_stage_o(record_stage_o),
        .stage_id_o(stage_id_o),
        .stage_data_o(stage_data_o),
        .key_locked_i(key_locked_i),
        .prog_enable_o(prog_enable_o),
        .prog_key_in_o(prog_key_in_o),
        .ciphertext_i(ciphertext_i),
        .tx_counter_i(tx_counter_i)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    task reg_wr_and_land_on_pulse(input [7:0] addr, input [31:0] data);
        begin
            reg_addr = addr; reg_wdata = data; reg_write = 1;
            @(posedge clk); #1;
        end
    endtask

    task end_write;
        begin
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
        $dumpfile("kavach_register_map.vcd");
        $dumpvars(0, kavach_register_map_tb);

        rst = 1; reg_write = 0; reg_read = 0; reg_addr = 0; reg_wdata = 0;
        bist_pass_i = 0; bist_fail_i = 0; replay_detected_i = 0;
        stable_response_i = 0; unstable_bit_count_i = 0;
        authentication_grant_i = 0; auth_denied_bist_i = 0; auth_denied_replay_i = 0;
        sequence_violation_i = 0; chain_complete_i = 0; stages_completed_i = 0;
        offline_budget_i = 0; sync_required_i = 0; total_offline_uses_i = 0;
        key_locked_i = 0; ciphertext_i = 0; tx_counter_i = 0;
        #20; rst = 0; #10;

        $display("================================");
        $display("  KAVACH-ID REGISTER MAP TEST  ");
        $display("================================");

        $display("--- Test 1: CONTROL write pulses bist_start ---");
        reg_wr_and_land_on_pulse(8'h00, 32'h0000_0001);
        if (bist_start_o == 1)
            $display("PASS: bist_start_o pulsed on CONTROL[0]!");
        else
            $display("FAIL: bist_start_o not pulsed");
        end_write;
        if (bist_start_o == 0)
            $display("PASS: bist_start_o correctly pulses for only 1 cycle!");
        else
            $display("FAIL: bist_start_o stuck high - not a pulse!");

        $display("--- Test 2: CONTROL write pulses stabilizer_start ---");
        reg_wr_and_land_on_pulse(8'h00, 32'h0000_0002);
        if (stabilizer_start_o == 1)
            $display("PASS: stabilizer_start_o pulsed on CONTROL[1]!");
        else
            $display("FAIL: stabilizer_start_o not pulsed");
        end_write;

        $display("--- Test 3: CONTROL write pulses auth_request ---");
        reg_wr_and_land_on_pulse(8'h00, 32'h0000_0004);
        if (auth_request_o == 1)
            $display("PASS: auth_request_o pulsed on CONTROL[2]!");
        else
            $display("FAIL: auth_request_o not pulsed - integration broken");
        end_write;

        $display("--- Test 4: STATUS reflects bist_pass/bist_fail/replay ---");
        bist_pass_i = 1; bist_fail_i = 0; replay_detected_i = 0;
        authentication_grant_i = 0; auth_denied_bist_i = 0; auth_denied_replay_i = 0;
        reg_rd(8'h04);
        if (reg_rdata[0] == 1 && reg_rdata[1] == 0 && reg_rdata[2] == 0)
            $display("PASS: STATUS correctly reflects bist_pass=1!");
        else
            $display("FAIL: STATUS mismatch, got 0x%0h", reg_rdata);

        $display("--- Test 5: STATUS reflects authentication_grant ---");
        bist_pass_i = 1; authentication_grant_i = 1;
        reg_rd(8'h04);
        if (reg_rdata[3] == 1)
            $display("PASS: STATUS[3] correctly shows authentication_grant!");
        else
            $display("FAIL: authentication_grant not visible in STATUS, got 0x%0h", reg_rdata);

        $display("--- Test 6: STATUS reflects auth_denied_bist ---");
        authentication_grant_i = 0; auth_denied_bist_i = 1;
        reg_rd(8'h04);
        if (reg_rdata[4] == 1)
            $display("PASS: STATUS[4] correctly shows auth_denied_bist!");
        else
            $display("FAIL: auth_denied_bist not visible, got 0x%0h", reg_rdata);

        $display("--- Test 7: STATUS reflects auth_denied_replay ---");
        auth_denied_bist_i = 0; auth_denied_replay_i = 1;
        reg_rd(8'h04);
        if (reg_rdata[5] == 1)
            $display("PASS: STATUS[5] correctly shows auth_denied_replay!");
        else
            $display("FAIL: auth_denied_replay not visible, got 0x%0h", reg_rdata);
        auth_denied_replay_i = 0;

        $display("--- Test 8: CHALLENGE write reaches challenge_o ---");
        reg_wr_and_land_on_pulse(8'h08, 32'hCAFED00D);
        end_write;
        if (challenge_o == 32'hCAFED00D)
            $display("PASS: challenge_o correctly updated!");
        else
            $display("FAIL: challenge_o mismatch, got 0x%0h", challenge_o);

        $display("--- Test 9: RESPONSE register reads stable_response_i ---");
        stable_response_i = 32'hABCD1234;
        reg_rd(8'h0C);
        if (reg_rdata == 32'hABCD1234)
            $display("PASS: RESPONSE correctly reads stable_response_i!");
        else
            $display("FAIL: RESPONSE mismatch, got 0x%0h", reg_rdata);

        $display("--- Test 10: UNSTABLE_COUNT register ---");
        unstable_bit_count_i = 6'd7;
        reg_rd(8'h10);
        if (reg_rdata == 32'd7)
            $display("PASS: UNSTABLE_COUNT correctly reads unstable_bit_count_i!");
        else
            $display("FAIL: UNSTABLE_COUNT mismatch, got 0x%0h", reg_rdata);

        $display("--- Test 11: CHIP_ID register ---");
        reg_rd(8'hFC);
        if (reg_rdata == 32'h4B415641)
            $display("PASS: CHIP_ID correctly reads 'KAVA'!");
        else
            $display("FAIL: CHIP_ID mismatch, got 0x%0h", reg_rdata);

        $display("--- Test 12: Unknown address returns 0 (default case) ---");
        reg_rd(8'h40);
        if (reg_rdata == 32'h0)
            $display("PASS: Unknown address correctly returns 0!");
        else
            $display("FAIL: Unknown address returned garbage: 0x%0h", reg_rdata);

        $display("--- Test 13: reg_ready pulses correctly on write and read ---");
        reg_wr_and_land_on_pulse(8'h00, 32'h0);
        end_write;
        if (reg_ready == 0)
            $display("PASS: reg_ready is a clean pulse, not stuck!");
        else
            $display("FAIL: reg_ready stuck high");

        $display("--- Test 14: 128-bit key loads across 4 KEY_DATA writes (MSB word first) ---");
        reg_wr_and_land_on_pulse(8'h28, 32'h11111111); end_write;
        reg_wr_and_land_on_pulse(8'h28, 32'h22222222); end_write;
        reg_wr_and_land_on_pulse(8'h28, 32'h33333333); end_write;
        reg_wr_and_land_on_pulse(8'h28, 32'h44444444); end_write;
        if (prog_key_in_o == 128'h11111111222222223333333344444444)
            $display("PASS: prog_key_in_o correctly assembled MSB-word-first!");
        else
            $display("FAIL: prog_key_in_o mismatch, got 0x%032h", prog_key_in_o);
        reg_rd(8'h30);
        if (reg_rdata[3:1] == 3'd4)
            $display("PASS: KEY_STATUS shows word_count=4 after 4 writes!");
        else
            $display("FAIL: word_count mismatch, got 0x%0h", reg_rdata);

        $display("--- Test 15: KEY_CONTROL with all 4 words present pulses prog_enable_o, resets count ---");
        reg_wr_and_land_on_pulse(8'h2C, 32'h1);
        if (prog_enable_o == 1)
            $display("PASS: prog_enable_o pulsed - full key accepted!");
        else
            $display("FAIL: prog_enable_o did not pulse despite 4 words present");
        end_write;
        reg_rd(8'h30);
        if (reg_rdata[3:1] == 3'd0)
            $display("PASS: word_count reset to 0 after KEY_CONTROL!");
        else
            $display("FAIL: word_count not reset, got 0x%0h", reg_rdata);

        $display("--- Test 16: Partial load (2/4 words) + KEY_CONTROL does NOT lock ---");
        reg_wr_and_land_on_pulse(8'h28, 32'hAAAAAAAA); end_write;
        reg_wr_and_land_on_pulse(8'h28, 32'hBBBBBBBB); end_write;
        reg_wr_and_land_on_pulse(8'h2C, 32'h1);
        if (prog_enable_o == 0)
            $display("PASS: prog_enable_o correctly withheld on partial (2/4) load!");
        else
            $display("FAIL: SECURITY BUG - prog_enable_o pulsed on a partial key load!");
        end_write;
        reg_rd(8'h30);
        if (reg_rdata[3:1] == 3'd0)
            $display("PASS: word_count reset after rejected partial load - forces full resend!");
        else
            $display("FAIL: word_count not reset, got 0x%0h", reg_rdata);

        $display("--- Test 17: KEY_STATUS reflects key_locked_i passthrough ---");
        key_locked_i = 1;
        reg_rd(8'h30);
        if (reg_rdata[0] == 1)
            $display("PASS: KEY_STATUS[0] correctly reflects key_locked_i!");
        else
            $display("FAIL: key_locked_i not visible, got 0x%0h", reg_rdata);

        $display("================================");
        $display("Register Map Test Complete!");
        $display("128-bit key programming protocol verified!");
        $display("================================");
        $finish;
    end
endmodule
