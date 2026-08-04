module hazard_detector(
    input  wire        clk,
    input  wire        rst,
    input  wire        load_weights,
    input  wire        load_activations,
    input  wire        compute_start,
    output reg         hazard_detected,
    output reg  [1:0]  hazard_type      // 1=weight race, 2=activation race, 3=both
);
    // Real NPU chips mein bada bug yeh hota hai: 
    // agar weights abhi load ho rahe hain aur 
    // usi cycle mein compute start ho jaaye, 
    // toh chip PURANE/GALAT weights se calculate 
    // kar dega — silent wrong AI output!
    //
    // Yeh module compute_start ko block karta hai 
    // jab tak loading complete na ho

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            hazard_detected <= 0;
            hazard_type     <= 0;
        end
        else begin
            hazard_detected <= 0;
            hazard_type     <= 0;

            // Weight loading ke saath compute start = HAZARD
            if (load_weights && compute_start) begin
                hazard_detected <= 1;
                hazard_type     <= 2'b01;
            end

            // Activation loading ke saath compute start = HAZARD
            if (load_activations && compute_start) begin
                hazard_detected <= 1;
                hazard_type     <= 2'b10;
            end

            // Dono ek saath
            if (load_weights && load_activations && compute_start) begin
                hazard_detected <= 1;
                hazard_type     <= 2'b11;
            end
        end
    end
endmodule
