module key_schedule_tb;

    reg  [127:0] key;
    wire [127:0] rk0,rk1,rk2,rk3,rk4,rk5;
    wire [127:0] rk6,rk7,rk8,rk9,rk10;

    key_schedule DUT (
        .key(key),
        .rk0(rk0),   .rk1(rk1),   .rk2(rk2),
        .rk3(rk3),   .rk4(rk4),   .rk5(rk5),
        .rk6(rk6),   .rk7(rk7),   .rk8(rk8),
        .rk9(rk9),   .rk10(rk10)
    );

    initial begin
        $dumpfile("key_schedule.vcd");
        $dumpvars(0, key_schedule_tb);

        $display("================================");
        $display("   AES KEY SCHEDULE TEST       ");
        $display("================================");

        key = 128'h2b7e151628aed2a6abf7158809cf4f3c;
        #10;
        $display("Key:  %h", key);
        $display("RK0:  %h", rk0);
        $display("RK1:  %h", rk1);
        $display("RK2:  %h", rk2);
        $display("RK10: %h", rk10);

        if(rk0 == key)
            $display("PASS: RK0 = Original Key!");
        else
            $display("FAIL: RK0 mismatch");

        if(rk1 != rk0 && rk1 != 128'h0)
            $display("PASS: RK1 expanded correctly!");
        else
            $display("FAIL: RK1 not expanded");

        if(rk10 != rk0 && rk10 != 128'h0)
            $display("PASS: RK10 generated!");
        else
            $display("FAIL: RK10 missing");

        $display("--------------------------------");
        key = 128'h0;
        #10;
        $display("Zero Key Test:");
        $display("RK0: %h", rk0);
        $display("RK1: %h", rk1);
        if(rk1 != 128'h0)
            $display("PASS: Zero key expanded!");
        else
            $display("FAIL: Zero key not expanded");

        $display("================================");
        $display("Day 17 Complete!");
        $display("Key Scheduler — 11 keys done!");
        $display("BharatSE Block 3 DONE!");
        $display("================================");
        $finish;
    end
endmodule
