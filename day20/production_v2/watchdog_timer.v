module watchdog_timer(
    input  wire        clk,
    input  wire        rst,
    input  wire        wdt_kick,      // CPU periodically "kick" karta hai
    input  wire        wdt_enable,
    output reg         wdt_timeout,   // Agar CPU hang ho jaaye
    output reg  [15:0] wdt_count      // Debug ke liye counter dikhta hai
);
    // Agar CPU 65535 cycles tak "kick" nahi karta,
    // matlab woh hang ho gaya hai —
    // watchdog isko detect karke chip ko
    // safe state mein force karega
    parameter TIMEOUT_LIMIT = 16'hFFFF;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            wdt_count   <= 0;
            wdt_timeout <= 0;
        end
        else if (wdt_enable) begin
            if (wdt_timeout) begin
                // FIX: Ek baar timeout latch ho jaaye, sirf
                // reset hi ise clear kar sakta hai — normal
                // wdt_kick ab ise silently clear nahi karega.
                // Yeh sticky/safety-critical behavior hai.
                wdt_count   <= wdt_count;
                wdt_timeout <= wdt_timeout;
            end
            else if (wdt_kick) begin
                // CPU ne "main zinda hoon" signal bheja
                // (sirf tabhi valid jab timeout abhi tak latch nahi hua)
                wdt_count   <= 0;
                wdt_timeout <= 0;
            end
            else if (wdt_count == TIMEOUT_LIMIT) begin
                // CPU ne bahut der se kick nahi kiya — HANG!
                wdt_timeout <= 1;
            end
            else begin
                wdt_count <= wdt_count + 1;
            end
        end
    end
endmodule
