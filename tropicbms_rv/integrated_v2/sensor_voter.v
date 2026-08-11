module sensor_voter(
    input  wire        clk,
    input  wire        rst,
    input  wire [11:0] sensor_1,
    input  wire [11:0] sensor_2,
    input  wire [11:0] sensor_3,
    output reg  [11:0] voted_value,
    output reg          sensor_fault_detected,
    output reg  [2:0]   faulty_sensor_mask  // bit0=s1, bit1=s2, bit2=s3
);
    // Real safety systems (automotive, aerospace) kabhi 
    // single sensor pe trust nahi karte. Agar ek sensor 
    // fail ho jaaye (short, open, drift), poora safety 
    // system down nahi hona chahiye.
    //
    // 2-out-of-3 voting: agar 2 sensors agree karte hain 
    // (within tolerance), unka average use karo. Teesra 
    // sensor jo bahut alag hai, use "faulty" flag karo.

    parameter TOLERANCE = 12'd50; // Acceptable deviation

    wire diff_12, diff_13, diff_23;
    wire [11:0] abs_diff_12, abs_diff_13, abs_diff_23;

    assign abs_diff_12 = (sensor_1 > sensor_2) ? 
                          (sensor_1 - sensor_2) : (sensor_2 - sensor_1);
    assign abs_diff_13 = (sensor_1 > sensor_3) ? 
                          (sensor_1 - sensor_3) : (sensor_3 - sensor_1);
    assign abs_diff_23 = (sensor_2 > sensor_3) ? 
                          (sensor_2 - sensor_3) : (sensor_3 - sensor_2);

    assign diff_12 = (abs_diff_12 <= TOLERANCE);
    assign diff_13 = (abs_diff_13 <= TOLERANCE);
    assign diff_23 = (abs_diff_23 <= TOLERANCE);

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            voted_value            <= 0;
            sensor_fault_detected  <= 0;
            faulty_sensor_mask     <= 0;
        end
        else begin
            // Case 1: Sab teen agree karte hain — sabse safe
            if (diff_12 && diff_13 && diff_23) begin
                voted_value           <= (sensor_1 + sensor_2 + sensor_3) / 3;
                sensor_fault_detected <= 0;
                faulty_sensor_mask    <= 3'b000;
            end
            // Case 2: Sensor 1 aur 2 agree, sensor 3 outlier hai
            else if (diff_12 && !diff_13 && !diff_23) begin
                voted_value           <= (sensor_1 + sensor_2) / 2;
                sensor_fault_detected <= 1;
                faulty_sensor_mask    <= 3'b100; // sensor 3 faulty
            end
            // Case 3: Sensor 1 aur 3 agree, sensor 2 outlier hai
            else if (diff_13 && !diff_12 && !diff_23) begin
                voted_value           <= (sensor_1 + sensor_3) / 2;
                sensor_fault_detected <= 1;
                faulty_sensor_mask    <= 3'b010; // sensor 2 faulty
            end
            // Case 4: Sensor 2 aur 3 agree, sensor 1 outlier hai
            else if (diff_23 && !diff_12 && !diff_13) begin
                voted_value           <= (sensor_2 + sensor_3) / 2;
                sensor_fault_detected <= 1;
                faulty_sensor_mask    <= 3'b001; // sensor 1 faulty
            end
            // Case 5: CRITICAL — koi bhi do sensors agree nahi karte!
            // Yeh worst case hai — teeno sensors alag values de rahe hain
            else begin
                voted_value           <= (sensor_1 + sensor_2 + sensor_3) / 3;
                sensor_fault_detected <= 1;
                faulty_sensor_mask    <= 3'b111; // All flagged - major fault!
            end
        end
    end
endmodule
