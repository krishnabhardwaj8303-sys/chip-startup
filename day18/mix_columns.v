module mix_columns(
    input  wire [127:0] in,
    output wire [127:0] out
);
    function [7:0] xtime;
        input [7:0] b;
        begin
            xtime = (b[7]) ?
                ({b[6:0],1'b0} ^ 8'h1b) :
                {b[6:0],1'b0};
        end
    endfunction

    function [7:0] gmul2;
        input [7:0] b;
        begin gmul2 = xtime(b); end
    endfunction

    function [7:0] gmul3;
        input [7:0] b;
        begin gmul3 = xtime(b) ^ b; end
    endfunction

    genvar i;
    generate
        for (i=0; i<4; i=i+1) begin : col
            wire [7:0] b0,b1,b2,b3;
            assign b0 = in[127-i*32 -: 8];
            assign b1 = in[119-i*32 -: 8];
            assign b2 = in[111-i*32 -: 8];
            assign b3 = in[103-i*32 -: 8];

            assign out[127-i*32 -: 8] =
                gmul2(b0)^gmul3(b1)^b2^b3;
            assign out[119-i*32 -: 8] =
                b0^gmul2(b1)^gmul3(b2)^b3;
            assign out[111-i*32 -: 8] =
                b0^b1^gmul2(b2)^gmul3(b3);
            assign out[103-i*32 -: 8] =
                gmul3(b0)^b1^b2^gmul2(b3);
        end
    endgenerate
endmodule
