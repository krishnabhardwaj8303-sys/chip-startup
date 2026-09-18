// AES-128 Core (encryption-only) — standalone, for Kavach-ID
//
// FIX: encrypted_channel.v's derive_keystream() previously used a
// simple XOR/arithmetic mixing function (key ^ constant, rotations,
// additions) - NOT a real cryptographic algorithm. This is trivially
// weak: given any known plaintext/ciphertext pair (easy to obtain
// since chip behavior is predictable), the keystream is recoverable
// with basic cryptanalysis, regardless of how good the key itself is.
//
// This module implements the real NIST FIPS-197 AES-128 algorithm:
// 10 rounds of SubBytes + ShiftRows + MixColumns + AddRoundKey (final
// round omits MixColumns), with an initial AddRoundKey and on-the-fly
// key expansion. Iterative (multi-cycle, one round per few clock
// cycles) implementation - not pipelined, not yet hardened against
// power/timing side-channel analysis (see scope note below).
//
// SCOPE NOTE: this core provides functional correctness (verified
// against the NIST FIPS-197 published test vector), not side-channel
// resistance. A production deployment where physical access to the
// chip is possible should additionally apply masking/hiding
// countermeasures - that hardening is a distinct, separate piece of
// future work from getting a functionally-correct AES core into
// Kavach-ID.
module aes128_core (
    input  wire         clk,
    input  wire         rst,
    input  wire         start,
    input  wire [127:0] key,
    input  wire [127:0] plaintext,
    output reg  [127:0] ciphertext,
    output reg           done
);

    // ── S-Box (NIST FIPS-197 standard, 256 entries) ──
    reg [7:0] sbox [0:255];

    initial begin
        sbox[8'h00]=8'h63; sbox[8'h01]=8'h7c; sbox[8'h02]=8'h77; sbox[8'h03]=8'h7b;
        sbox[8'h04]=8'hf2; sbox[8'h05]=8'h6b; sbox[8'h06]=8'h6f; sbox[8'h07]=8'hc5;
        sbox[8'h08]=8'h30; sbox[8'h09]=8'h01; sbox[8'h0a]=8'h67; sbox[8'h0b]=8'h2b;
        sbox[8'h0c]=8'hfe; sbox[8'h0d]=8'hd7; sbox[8'h0e]=8'hab; sbox[8'h0f]=8'h76;
        sbox[8'h10]=8'hca; sbox[8'h11]=8'h82; sbox[8'h12]=8'hc9; sbox[8'h13]=8'h7d;
        sbox[8'h14]=8'hfa; sbox[8'h15]=8'h59; sbox[8'h16]=8'h47; sbox[8'h17]=8'hf0;
        sbox[8'h18]=8'had; sbox[8'h19]=8'hd4; sbox[8'h1a]=8'ha2; sbox[8'h1b]=8'haf;
        sbox[8'h1c]=8'h9c; sbox[8'h1d]=8'ha4; sbox[8'h1e]=8'h72; sbox[8'h1f]=8'hc0;
        sbox[8'h20]=8'hb7; sbox[8'h21]=8'hfd; sbox[8'h22]=8'h93; sbox[8'h23]=8'h26;
        sbox[8'h24]=8'h36; sbox[8'h25]=8'h3f; sbox[8'h26]=8'hf7; sbox[8'h27]=8'hcc;
        sbox[8'h28]=8'h34; sbox[8'h29]=8'ha5; sbox[8'h2a]=8'he5; sbox[8'h2b]=8'hf1;
        sbox[8'h2c]=8'h71; sbox[8'h2d]=8'hd8; sbox[8'h2e]=8'h31; sbox[8'h2f]=8'h15;
        sbox[8'h30]=8'h04; sbox[8'h31]=8'hc7; sbox[8'h32]=8'h23; sbox[8'h33]=8'hc3;
        sbox[8'h34]=8'h18; sbox[8'h35]=8'h96; sbox[8'h36]=8'h05; sbox[8'h37]=8'h9a;
        sbox[8'h38]=8'h07; sbox[8'h39]=8'h12; sbox[8'h3a]=8'h80; sbox[8'h3b]=8'he2;
        sbox[8'h3c]=8'heb; sbox[8'h3d]=8'h27; sbox[8'h3e]=8'hb2; sbox[8'h3f]=8'h75;
        sbox[8'h40]=8'h09; sbox[8'h41]=8'h83; sbox[8'h42]=8'h2c; sbox[8'h43]=8'h1a;
        sbox[8'h44]=8'h1b; sbox[8'h45]=8'h6e; sbox[8'h46]=8'h5a; sbox[8'h47]=8'ha0;
        sbox[8'h48]=8'h52; sbox[8'h49]=8'h3b; sbox[8'h4a]=8'hd6; sbox[8'h4b]=8'hb3;
        sbox[8'h4c]=8'h29; sbox[8'h4d]=8'he3; sbox[8'h4e]=8'h2f; sbox[8'h4f]=8'h84;
        sbox[8'h50]=8'h53; sbox[8'h51]=8'hd1; sbox[8'h52]=8'h00; sbox[8'h53]=8'hed;
        sbox[8'h54]=8'h20; sbox[8'h55]=8'hfc; sbox[8'h56]=8'hb1; sbox[8'h57]=8'h5b;
        sbox[8'h58]=8'h6a; sbox[8'h59]=8'hcb; sbox[8'h5a]=8'hbe; sbox[8'h5b]=8'h39;
        sbox[8'h5c]=8'h4a; sbox[8'h5d]=8'h4c; sbox[8'h5e]=8'h58; sbox[8'h5f]=8'hcf;
        sbox[8'h60]=8'hd0; sbox[8'h61]=8'hef; sbox[8'h62]=8'haa; sbox[8'h63]=8'hfb;
        sbox[8'h64]=8'h43; sbox[8'h65]=8'h4d; sbox[8'h66]=8'h33; sbox[8'h67]=8'h85;
        sbox[8'h68]=8'h45; sbox[8'h69]=8'hf9; sbox[8'h6a]=8'h02; sbox[8'h6b]=8'h7f;
        sbox[8'h6c]=8'h50; sbox[8'h6d]=8'h3c; sbox[8'h6e]=8'h9f; sbox[8'h6f]=8'ha8;
        sbox[8'h70]=8'h51; sbox[8'h71]=8'ha3; sbox[8'h72]=8'h40; sbox[8'h73]=8'h8f;
        sbox[8'h74]=8'h92; sbox[8'h75]=8'h9d; sbox[8'h76]=8'h38; sbox[8'h77]=8'hf5;
        sbox[8'h78]=8'hbc; sbox[8'h79]=8'hb6; sbox[8'h7a]=8'hda; sbox[8'h7b]=8'h21;
        sbox[8'h7c]=8'h10; sbox[8'h7d]=8'hff; sbox[8'h7e]=8'hf3; sbox[8'h7f]=8'hd2;
        sbox[8'h80]=8'hcd; sbox[8'h81]=8'h0c; sbox[8'h82]=8'h13; sbox[8'h83]=8'hec;
        sbox[8'h84]=8'h5f; sbox[8'h85]=8'h97; sbox[8'h86]=8'h44; sbox[8'h87]=8'h17;
        sbox[8'h88]=8'hc4; sbox[8'h89]=8'ha7; sbox[8'h8a]=8'h7e; sbox[8'h8b]=8'h3d;
        sbox[8'h8c]=8'h64; sbox[8'h8d]=8'h5d; sbox[8'h8e]=8'h19; sbox[8'h8f]=8'h73;
        sbox[8'h90]=8'h60; sbox[8'h91]=8'h81; sbox[8'h92]=8'h4f; sbox[8'h93]=8'hdc;
        sbox[8'h94]=8'h22; sbox[8'h95]=8'h2a; sbox[8'h96]=8'h90; sbox[8'h97]=8'h88;
        sbox[8'h98]=8'h46; sbox[8'h99]=8'hee; sbox[8'h9a]=8'hb8; sbox[8'h9b]=8'h14;
        sbox[8'h9c]=8'hde; sbox[8'h9d]=8'h5e; sbox[8'h9e]=8'h0b; sbox[8'h9f]=8'hdb;
        sbox[8'ha0]=8'he0; sbox[8'ha1]=8'h32; sbox[8'ha2]=8'h3a; sbox[8'ha3]=8'h0a;
        sbox[8'ha4]=8'h49; sbox[8'ha5]=8'h06; sbox[8'ha6]=8'h24; sbox[8'ha7]=8'h5c;
        sbox[8'ha8]=8'hc2; sbox[8'ha9]=8'hd3; sbox[8'haa]=8'hac; sbox[8'hab]=8'h62;
        sbox[8'hac]=8'h91; sbox[8'had]=8'h95; sbox[8'hae]=8'he4; sbox[8'haf]=8'h79;
        sbox[8'hb0]=8'he7; sbox[8'hb1]=8'hc8; sbox[8'hb2]=8'h37; sbox[8'hb3]=8'h6d;
        sbox[8'hb4]=8'h8d; sbox[8'hb5]=8'hd5; sbox[8'hb6]=8'h4e; sbox[8'hb7]=8'ha9;
        sbox[8'hb8]=8'h6c; sbox[8'hb9]=8'h56; sbox[8'hba]=8'hf4; sbox[8'hbb]=8'hea;
        sbox[8'hbc]=8'h65; sbox[8'hbd]=8'h7a; sbox[8'hbe]=8'hae; sbox[8'hbf]=8'h08;
        sbox[8'hc0]=8'hba; sbox[8'hc1]=8'h78; sbox[8'hc2]=8'h25; sbox[8'hc3]=8'h2e;
        sbox[8'hc4]=8'h1c; sbox[8'hc5]=8'ha6; sbox[8'hc6]=8'hb4; sbox[8'hc7]=8'hc6;
        sbox[8'hc8]=8'he8; sbox[8'hc9]=8'hdd; sbox[8'hca]=8'h74; sbox[8'hcb]=8'h1f;
        sbox[8'hcc]=8'h4b; sbox[8'hcd]=8'hbd; sbox[8'hce]=8'h8b; sbox[8'hcf]=8'h8a;
        sbox[8'hd0]=8'h70; sbox[8'hd1]=8'h3e; sbox[8'hd2]=8'hb5; sbox[8'hd3]=8'h66;
        sbox[8'hd4]=8'h48; sbox[8'hd5]=8'h03; sbox[8'hd6]=8'hf6; sbox[8'hd7]=8'h0e;
        sbox[8'hd8]=8'h61; sbox[8'hd9]=8'h35; sbox[8'hda]=8'h57; sbox[8'hdb]=8'hb9;
        sbox[8'hdc]=8'h86; sbox[8'hdd]=8'hc1; sbox[8'hde]=8'h1d; sbox[8'hdf]=8'h9e;
        sbox[8'he0]=8'he1; sbox[8'he1]=8'hf8; sbox[8'he2]=8'h98; sbox[8'he3]=8'h11;
        sbox[8'he4]=8'h69; sbox[8'he5]=8'hd9; sbox[8'he6]=8'h8e; sbox[8'he7]=8'h94;
        sbox[8'he8]=8'h9b; sbox[8'he9]=8'h1e; sbox[8'hea]=8'h87; sbox[8'heb]=8'he9;
        sbox[8'hec]=8'hce; sbox[8'hed]=8'h55; sbox[8'hee]=8'h28; sbox[8'hef]=8'hdf;
        sbox[8'hf0]=8'h8c; sbox[8'hf1]=8'ha1; sbox[8'hf2]=8'h89; sbox[8'hf3]=8'h0d;
        sbox[8'hf4]=8'hbf; sbox[8'hf5]=8'he6; sbox[8'hf6]=8'h42; sbox[8'hf7]=8'h68;
        sbox[8'hf8]=8'h41; sbox[8'hf9]=8'h99; sbox[8'hfa]=8'h2d; sbox[8'hfb]=8'h0f;
        sbox[8'hfc]=8'hb0; sbox[8'hfd]=8'h54; sbox[8'hfe]=8'hbb; sbox[8'hff]=8'h16;
    end

    reg [7:0] rcon [1:10];
    initial begin
        rcon[1]=8'h01; rcon[2]=8'h02; rcon[3]=8'h04; rcon[4]=8'h08; rcon[5]=8'h10;
        rcon[6]=8'h20; rcon[7]=8'h40; rcon[8]=8'h80; rcon[9]=8'h1b; rcon[10]=8'h36;
    end

    function [7:0] xtime;
        input [7:0] a;
        begin
            xtime = a[7] ? ((a << 1) ^ 8'h1b) : (a << 1);
        end
    endfunction

    function [7:0] gmul2;
        input [7:0] a;
        begin
            gmul2 = xtime(a);
        end
    endfunction

    function [7:0] gmul3;
        input [7:0] a;
        begin
            gmul3 = xtime(a) ^ a;
        end
    endfunction

    reg [7:0] state [0:15];
    reg [7:0] round_key [0:15];
    reg [7:0] key_bytes [0:15];

    integer i;

    task sub_shift_rows;
        reg [7:0] tmp [0:15];
        integer c;
        begin
            for (c = 0; c < 16; c = c + 1)
                tmp[c] = sbox[state[c]];
            state[0]  = tmp[0];  state[4]  = tmp[4];  state[8]  = tmp[8];  state[12] = tmp[12];
            state[1]  = tmp[5];  state[5]  = tmp[9];  state[9]  = tmp[13]; state[13] = tmp[1];
            state[2]  = tmp[10]; state[6]  = tmp[14]; state[10] = tmp[2];  state[14] = tmp[6];
            state[3]  = tmp[15]; state[7]  = tmp[3];  state[11] = tmp[7];  state[15] = tmp[11];
        end
    endtask

    task mix_columns;
        integer col;
        reg [7:0] a0, a1, a2, a3;
        begin
            for (col = 0; col < 4; col = col + 1) begin
                a0 = state[col*4 + 0];
                a1 = state[col*4 + 1];
                a2 = state[col*4 + 2];
                a3 = state[col*4 + 3];
                state[col*4 + 0] = gmul2(a0) ^ gmul3(a1) ^ a2 ^ a3;
                state[col*4 + 1] = a0 ^ gmul2(a1) ^ gmul3(a2) ^ a3;
                state[col*4 + 2] = a0 ^ a1 ^ gmul2(a2) ^ gmul3(a3);
                state[col*4 + 3] = gmul3(a0) ^ a1 ^ a2 ^ gmul2(a3);
            end
        end
    endtask

    task add_round_key;
        integer c;
        begin
            for (c = 0; c < 16; c = c + 1)
                state[c] = state[c] ^ round_key[c];
        end
    endtask

    reg [3:0] round_num;

    task next_round_key;
        reg [7:0] t0, t1, t2, t3;
        begin
            t0 = sbox[round_key[13]];
            t1 = sbox[round_key[14]];
            t2 = sbox[round_key[15]];
            t3 = sbox[round_key[12]];
            t0 = t0 ^ rcon[round_num];

            round_key[0]  = round_key[0]  ^ t0;
            round_key[1]  = round_key[1]  ^ t1;
            round_key[2]  = round_key[2]  ^ t2;
            round_key[3]  = round_key[3]  ^ t3;

            round_key[4]  = round_key[4]  ^ round_key[0];
            round_key[5]  = round_key[5]  ^ round_key[1];
            round_key[6]  = round_key[6]  ^ round_key[2];
            round_key[7]  = round_key[7]  ^ round_key[3];

            round_key[8]  = round_key[8]  ^ round_key[4];
            round_key[9]  = round_key[9]  ^ round_key[5];
            round_key[10] = round_key[10] ^ round_key[6];
            round_key[11] = round_key[11] ^ round_key[7];

            round_key[12] = round_key[12] ^ round_key[8];
            round_key[13] = round_key[13] ^ round_key[9];
            round_key[14] = round_key[14] ^ round_key[10];
            round_key[15] = round_key[15] ^ round_key[11];
        end
    endtask

    localparam ST_IDLE   = 3'd0,
               ST_INIT   = 3'd1,
               ST_ROUND  = 3'd2,
               ST_FINAL  = 3'd3,
               ST_DONE   = 3'd4;

    reg [2:0] fsm_state;
    reg [3:0] round_ctr;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            fsm_state  <= ST_IDLE;
            done       <= 1'b0;
            round_num  <= 4'd1;
            round_ctr  <= 4'd0;
            ciphertext <= 128'd0;
        end
        else begin
            done <= 1'b0;
            case (fsm_state)
                ST_IDLE: begin
                    if (start) begin
                        for (i = 0; i < 16; i = i + 1) begin
                            state[i]     <= plaintext[127 - i*8 -: 8];
                            round_key[i] <= key[127 - i*8 -: 8];
                        end
                        round_num <= 4'd1;
                        round_ctr <= 4'd0;
                        fsm_state <= ST_INIT;
                    end
                end

                ST_INIT: begin
                    add_round_key;
                    fsm_state <= ST_ROUND;
                end

                ST_ROUND: begin
                    if (round_ctr < 9) begin
                        next_round_key;
                        sub_shift_rows;
                        mix_columns;
                        add_round_key;
                        round_ctr <= round_ctr + 1'b1;
                        round_num <= round_num + 1'b1;
                    end
                    else begin
                        fsm_state <= ST_FINAL;
                    end
                end

                ST_FINAL: begin
                    next_round_key;
                    sub_shift_rows;
                    add_round_key;
                    fsm_state <= ST_DONE;
                end

                ST_DONE: begin
                    for (i = 0; i < 16; i = i + 1)
                        ciphertext[127 - i*8 -: 8] <= state[i];
                    done      <= 1'b1;
                    fsm_state <= ST_IDLE;
                end

                default: fsm_state <= ST_IDLE;
            endcase
        end
    end

endmodule
