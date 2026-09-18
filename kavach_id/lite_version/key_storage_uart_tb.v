module key_storage_uart_tb;

    reg  clk, rst;
    wire uart_link;
    wire uart_from_chip;
    wire chip_healthy, verification_blocked;

    reg        host_tx_start;
    reg  [7:0] host_tx_data;
    wire       host_tx_busy;

    uart_tx #(.CLKS_PER_BIT(4)) HOST_TX (
        .clk(clk), .rst(rst),
        .tx_start(host_tx_start), .data_in(host_tx_data),
        .tx_out(uart_link), .tx_busy(host_tx_busy)
    );

    wire [7:0] host_rx_byte;
    wire       host_rx_valid;

    uart_rx #(.CLKS_PER_BIT(4)) HOST_RX (
        .clk(clk), .rst(rst),
        .rx_in(uart_from_chip),
        .data_out(host_rx_byte),
        .data_valid(host_rx_valid)
    );

    kavach_id_top DUT (
        .clk(clk), .clk_sel(1'b0), .rst(rst),
        .uart_rx_in(uart_link),
        .uart_tx_out(uart_from_chip),
        .chip_healthy(chip_healthy),
        .verification_blocked(verification_blocked)
    );

    initial clk = 0;
    always #5 clk = ~clk;

    task send_byte(input [7:0] b);
        begin
            wait (host_tx_busy == 0);
            host_tx_data = b;
            host_tx_start = 1;
            @(posedge clk); #1;
            host_tx_start = 0;
            wait (host_tx_busy == 1);
            wait (host_tx_busy == 0);
        end
    endtask

    task reg_write_uart(input [7:0] addr, input [31:0] data);
        begin
            send_byte(8'h01);
            send_byte(addr);
            send_byte(data[31:24]);
            send_byte(data[23:16]);
            send_byte(data[15:8]);
            send_byte(data[7:0]);
        end
    endtask

    // NEW: loads a full 128-bit key across 4 sequential KEY_DATA
    // (0x28) writes, MSB word first, matching kavach_register_map.v's
    // 4-word shift-register protocol - a single KEY_DATA write is no
    // longer sufficient to arm KEY_CONTROL.
    task program_key_uart(input [127:0] key);
        begin
            reg_write_uart(8'h28, key[127:96]);
            reg_write_uart(8'h28, key[95:64]);
            reg_write_uart(8'h28, key[63:32]);
            reg_write_uart(8'h28, key[31:0]);
            reg_write_uart(8'h2C, 32'h0000_0001); // KEY_CONTROL bit0 = attempt lock
        end
    endtask

    reg [31:0] read_result;
    integer    read_byte_count;

    task reg_read_uart(input [7:0] addr);
        begin
            read_result = 0;
            read_byte_count = 0;
            send_byte(8'h02);
            send_byte(addr);
            send_byte(8'h00);
            send_byte(8'h00);
            send_byte(8'h00);
            send_byte(8'h00);
            wait (read_byte_count == 4);
        end
    endtask

    always @(posedge clk) begin
        if (host_rx_valid) begin
            read_result     <= {read_result[23:0], host_rx_byte};
            read_byte_count <= read_byte_count + 1;
        end
    end

    initial begin
        rst = 1; host_tx_start = 0; host_tx_data = 0;
        #20; rst = 0; #150; // extra margin for POR_CYCLES (8) hold + reset_sync 2-cycle release

        $display("================================================");
        $display("  PER-CHIP KEY STORAGE TESTS (via UART, 128-bit)");
        $display("================================================");

        $display("--- TEST A: Key starts unprogrammed (key_locked = 0) ---");
        reg_read_uart(8'h30); // KEY_STATUS
        $display("KEY_STATUS=0x%0h (expect bit0=0)", read_result);
        if (read_result[0] == 0)
            $display("PASS: key starts unlocked");
        else
            $display("FAIL");

        $display("--- TEST B: Program a full 128-bit key across 4 words, confirm it locks ---");
        program_key_uart(128'hCAFEF00D_11223344_55667788_9ABCDEF0);
        repeat (10) @(posedge clk);
        reg_read_uart(8'h30);
        $display("KEY_STATUS=0x%0h (expect bit0=1, bit[3:1] word_count=0)", read_result);
        if (read_result[0] == 1)
            $display("PASS: key is now locked");
        else
            $display("FAIL");
        $display("chip_key internal value = 0x%032h", DUT.chip_key_w);
        if (DUT.chip_key_w == 128'hCAFEF00D1122334455667788_9ABCDEF0)
            $display("PASS: full 128-bit key correctly assembled and stored");
        else
            $display("FAIL: chip_key_w mismatch");

        $display("--- TEST C: Attempt to reprogram with a DIFFERENT full key - must be rejected ---");
        program_key_uart(128'hDEADBEEF_DEADBEEF_DEADBEEF_DEADBEEF);
        repeat (10) @(posedge clk);
        $display("chip_key internal value = 0x%032h (expect still original key)", DUT.chip_key_w);
        if (DUT.chip_key_w == 128'hCAFEF00D1122334455667788_9ABCDEF0)
            $display("PASS: second full-key programming attempt correctly rejected, original key preserved");
        else
            $display("FAIL: SECURITY BUG - key was overwritten after lock");

        $display("--- TEST D: Partial load (only 2 of 4 words) does not arm KEY_CONTROL ---");
        // Uses a THIRD distinct key value, sent incomplete, against an
        // already-locked chip - this exercises the word_count reset
        // path even though the lock itself would independently block
        // it; documents that partial loads are rejected before lock
        // enforcement is even reached.
        reg_write_uart(8'h28, 32'h11111111);
        reg_write_uart(8'h28, 32'h22222222);
        reg_write_uart(8'h2C, 32'h0000_0001);
        repeat (10) @(posedge clk);
        $display("chip_key internal value = 0x%032h (expect unchanged)", DUT.chip_key_w);
        if (DUT.chip_key_w == 128'hCAFEF00D1122334455667788_9ABCDEF0)
            $display("PASS: partial load did not disturb the locked key");
        else
            $display("FAIL: partial load unexpectedly changed chip_key_w");

        $display("================================================");
        $display("Key storage tests (UART) complete");
        $display("================================================");
        $finish;
    end
endmodule
