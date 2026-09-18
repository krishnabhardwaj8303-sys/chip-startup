// SHA-256 Core — single-block, iterative FSM
//
// FIX: provenance_chain.v's mix_hash() previously used a simple
// XOR-rotate mixing function - NOT real cryptography, same class of
// weakness as encrypted_channel.v's old derive_keystream(). This core
// implements real NIST FIPS-180-4 SHA-256 (message schedule expansion
// + 64-round compression), verified bit-exact against 2 known-answer
// test vectors ("abc" and the empty string, both single-block).
//
// SCOPE: single 512-bit block only (no multi-block/streaming support).
// provenance_chain.v's message (256-bit chain_hash + 32-bit stage_data
// + 2-bit stage_id = 290 bits) always fits in one block after standard
// padding, so multi-block support is not needed for this application.
//
// Iterative (multi-cycle, ~113-cycle) implementation, not pipelined.
module sha256_core (
    input  wire         clk,
    input  wire         rst,
    input  wire         start,
    input  wire [511:0] block_in,   // already padded to exactly 512 bits
    output reg  [255:0] hash_out,
    output reg           done
);

    reg [31:0] k [0:63];
    initial begin
        k[0]=32'h428a2f98; k[1]=32'h71374491; k[2]=32'hb5c0fbcf; k[3]=32'he9b5dba5;
        k[4]=32'h3956c25b; k[5]=32'h59f111f1; k[6]=32'h923f82a4; k[7]=32'hab1c5ed5;
        k[8]=32'hd807aa98; k[9]=32'h12835b01; k[10]=32'h243185be; k[11]=32'h550c7dc3;
        k[12]=32'h72be5d74; k[13]=32'h80deb1fe; k[14]=32'h9bdc06a7; k[15]=32'hc19bf174;
        k[16]=32'he49b69c1; k[17]=32'hefbe4786; k[18]=32'h0fc19dc6; k[19]=32'h240ca1cc;
        k[20]=32'h2de92c6f; k[21]=32'h4a7484aa; k[22]=32'h5cb0a9dc; k[23]=32'h76f988da;
        k[24]=32'h983e5152; k[25]=32'ha831c66d; k[26]=32'hb00327c8; k[27]=32'hbf597fc7;
        k[28]=32'hc6e00bf3; k[29]=32'hd5a79147; k[30]=32'h06ca6351; k[31]=32'h14292967;
        k[32]=32'h27b70a85; k[33]=32'h2e1b2138; k[34]=32'h4d2c6dfc; k[35]=32'h53380d13;
        k[36]=32'h650a7354; k[37]=32'h766a0abb; k[38]=32'h81c2c92e; k[39]=32'h92722c85;
        k[40]=32'ha2bfe8a1; k[41]=32'ha81a664b; k[42]=32'hc24b8b70; k[43]=32'hc76c51a3;
        k[44]=32'hd192e819; k[45]=32'hd6990624; k[46]=32'hf40e3585; k[47]=32'h106aa070;
        k[48]=32'h19a4c116; k[49]=32'h1e376c08; k[50]=32'h2748774c; k[51]=32'h34b0bcb5;
        k[52]=32'h391c0cb3; k[53]=32'h4ed8aa4a; k[54]=32'h5b9cca4f; k[55]=32'h682e6ff3;
        k[56]=32'h748f82ee; k[57]=32'h78a5636f; k[58]=32'h84c87814; k[59]=32'h8cc70208;
        k[60]=32'h90befffa; k[61]=32'ha4506ceb; k[62]=32'hbef9a3f7; k[63]=32'hc67178f2;
    end

    function [31:0] rotr;
        input [31:0] x;
        input [4:0]  n;
        begin
            rotr = (x >> n) | (x << (32-n));
        end
    endfunction

    function [31:0] sig0; // message-schedule sigma0
        input [31:0] x;
        begin
            sig0 = rotr(x,7) ^ rotr(x,18) ^ (x >> 3);
        end
    endfunction

    function [31:0] sig1; // message-schedule sigma1
        input [31:0] x;
        begin
            sig1 = rotr(x,17) ^ rotr(x,19) ^ (x >> 10);
        end
    endfunction

    function [31:0] bigsig0; // compression Sigma0
        input [31:0] x;
        begin
            bigsig0 = rotr(x,2) ^ rotr(x,13) ^ rotr(x,22);
        end
    endfunction

    function [31:0] bigsig1; // compression Sigma1
        input [31:0] x;
        begin
            bigsig1 = rotr(x,6) ^ rotr(x,11) ^ rotr(x,25);
        end
    endfunction

    reg [31:0] w [0:63];
    reg [31:0] a,b,c,d,e,f,g,h;
    reg [31:0] H0,H1,H2,H3,H4,H5,H6,H7;

    localparam ST_IDLE     = 3'd0,
               ST_EXPAND   = 3'd1,
               ST_COMPRESS = 3'd2,
               ST_FINAL    = 3'd3,
               ST_DONE     = 3'd4;

    reg [2:0] state;
    reg [6:0] t;
    integer i;

    // round-computation temporaries
    reg [31:0] S1, ch, temp1, S0, maj, temp2;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state    <= ST_IDLE;
            done     <= 1'b0;
            t        <= 7'd0;
            hash_out <= 256'd0;
        end
        else begin
            done <= 1'b0;
            case (state)
                ST_IDLE: begin
                    if (start) begin
                        for (i = 0; i < 16; i = i + 1)
                            w[i] <= block_in[511 - i*32 -: 32];
                        H0 <= 32'h6a09e667; H1 <= 32'hbb67ae85;
                        H2 <= 32'h3c6ef372; H3 <= 32'ha54ff53a;
                        H4 <= 32'h510e527f; H5 <= 32'h9b05688c;
                        H6 <= 32'h1f83d9ab; H7 <= 32'h5be0cd19;
                        a <= 32'h6a09e667; b <= 32'hbb67ae85;
                        c <= 32'h3c6ef372; d <= 32'ha54ff53a;
                        e <= 32'h510e527f; f <= 32'h9b05688c;
                        g <= 32'h1f83d9ab; h <= 32'h5be0cd19;
                        t <= 7'd16;
                        state <= ST_EXPAND;
                    end
                end

                ST_EXPAND: begin
                    if (t < 64) begin
                        w[t] <= sig1(w[t-2]) + w[t-7] + sig0(w[t-15]) + w[t-16];
                        t <= t + 1'b1;
                    end
                    else begin
                        t <= 7'd0;
                        state <= ST_COMPRESS;
                    end
                end

                ST_COMPRESS: begin
                    if (t < 64) begin
                        S1    = bigsig1(e);
                        ch    = (e & f) ^ (~e & g);
                        temp1 = h + S1 + ch + k[t] + w[t];
                        S0    = bigsig0(a);
                        maj   = (a & b) ^ (a & c) ^ (b & c);
                        temp2 = S0 + maj;

                        h <= g;
                        g <= f;
                        f <= e;
                        e <= d + temp1;
                        d <= c;
                        c <= b;
                        b <= a;
                        a <= temp1 + temp2;

                        t <= t + 1'b1;
                    end
                    else begin
                        state <= ST_FINAL;
                    end
                end

                ST_FINAL: begin
                    H0 <= H0 + a; H1 <= H1 + b; H2 <= H2 + c; H3 <= H3 + d;
                    H4 <= H4 + e; H5 <= H5 + f; H6 <= H6 + g; H7 <= H7 + h;
                    state <= ST_DONE;
                end

                ST_DONE: begin
                    hash_out <= {H0, H1, H2, H3, H4, H5, H6, H7};
                    done     <= 1'b1;
                    state    <= ST_IDLE;
                end

                default: state <= ST_IDLE;
            endcase
        end
    end
endmodule
