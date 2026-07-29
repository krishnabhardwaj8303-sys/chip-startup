module key_schedule(
    input  wire [127:0] key,
    output reg  [127:0] rk0,  rk1,  rk2,  rk3,
    output reg  [127:0] rk4,  rk5,  rk6,  rk7,
    output reg  [127:0] rk8,  rk9,  rk10
);
    function [7:0] sb;
        input [7:0] in;
        reg [7:0] s [0:255];
        begin
            s[8'h00]=8'h63; s[8'h01]=8'h7c; s[8'h02]=8'h77; s[8'h03]=8'h7b;
            s[8'h04]=8'hf2; s[8'h05]=8'h6b; s[8'h06]=8'h6f; s[8'h07]=8'hc5;
            s[8'h08]=8'h30; s[8'h09]=8'h01; s[8'h0a]=8'h67; s[8'h0b]=8'h2b;
            s[8'h0c]=8'hfe; s[8'h0d]=8'hd7; s[8'h0e]=8'hab; s[8'h0f]=8'h76;
            s[8'h10]=8'hca; s[8'h11]=8'h82; s[8'h12]=8'hc9; s[8'h13]=8'h7d;
            s[8'h14]=8'hfa; s[8'h15]=8'h59; s[8'h16]=8'h47; s[8'h17]=8'hf0;
            s[8'h18]=8'had; s[8'h19]=8'hd4; s[8'h1a]=8'ha2; s[8'h1b]=8'haf;
            s[8'h1c]=8'h9c; s[8'h1d]=8'ha4; s[8'h1e]=8'h72; s[8'h1f]=8'hc0;
            s[8'h20]=8'hb7; s[8'h21]=8'hfd; s[8'h22]=8'h93; s[8'h23]=8'h26;
            s[8'h24]=8'h36; s[8'h25]=8'h3f; s[8'h26]=8'hf7; s[8'h27]=8'hcc;
            s[8'h28]=8'h34; s[8'h29]=8'ha5; s[8'h2a]=8'he5; s[8'h2b]=8'hf1;
            s[8'h2c]=8'h71; s[8'h2d]=8'hd8; s[8'h2e]=8'h31; s[8'h2f]=8'h15;
            s[8'h30]=8'h04; s[8'h31]=8'hc7; s[8'h32]=8'h23; s[8'h33]=8'hc3;
            s[8'h34]=8'h18; s[8'h35]=8'h96; s[8'h36]=8'h05; s[8'h37]=8'h9a;
            s[8'h38]=8'h07; s[8'h39]=8'h12; s[8'h3a]=8'h80; s[8'h3b]=8'he2;
            s[8'h3c]=8'heb; s[8'h3d]=8'h27; s[8'h3e]=8'hb2; s[8'h3f]=8'h75;
            s[8'h40]=8'h09; s[8'h41]=8'h83; s[8'h42]=8'h2c; s[8'h43]=8'h1a;
            s[8'h44]=8'h1b; s[8'h45]=8'h6e; s[8'h46]=8'h5a; s[8'h47]=8'ha0;
            s[8'h48]=8'h52; s[8'h49]=8'h3b; s[8'h4a]=8'hd6; s[8'h4b]=8'hb3;
            s[8'h4c]=8'h29; s[8'h4d]=8'he3; s[8'h4e]=8'h2f; s[8'h4f]=8'h84;
            s[8'h50]=8'h53; s[8'h51]=8'hd1; s[8'h52]=8'h00; s[8'h53]=8'hed;
            s[8'h54]=8'h20; s[8'h55]=8'hfc; s[8'h56]=8'hb1; s[8'h57]=8'h5b;
            s[8'h58]=8'h6a; s[8'h59]=8'hcb; s[8'h5a]=8'hbe; s[8'h5b]=8'h39;
            s[8'h5c]=8'h4a; s[8'h5d]=8'h4c; s[8'h5e]=8'h58; s[8'h5f]=8'hcf;
            s[8'h60]=8'hd0; s[8'h61]=8'hef; s[8'h62]=8'haa; s[8'h63]=8'hfb;
            s[8'h64]=8'h43; s[8'h65]=8'h4d; s[8'h66]=8'h33; s[8'h67]=8'h85;
            s[8'h68]=8'h45; s[8'h69]=8'hf9; s[8'h6a]=8'h02; s[8'h6b]=8'h7f;
            s[8'h6c]=8'h50; s[8'h6d]=8'h3c; s[8'h6e]=8'h9f; s[8'h6f]=8'ha8;
            s[8'h70]=8'h51; s[8'h71]=8'ha3; s[8'h72]=8'h40; s[8'h73]=8'h8f;
            s[8'h74]=8'h92; s[8'h75]=8'h9d; s[8'h76]=8'h38; s[8'h77]=8'hf5;
            s[8'h78]=8'hbc; s[8'h79]=8'hb6; s[8'h7a]=8'hda; s[8'h7b]=8'h21;
            s[8'h7c]=8'h10; s[8'h7d]=8'hff; s[8'h7e]=8'hf3; s[8'h7f]=8'hd2;
            s[8'h80]=8'hcd; s[8'h81]=8'h0c; s[8'h82]=8'h13; s[8'h83]=8'hec;
            s[8'h84]=8'h5f; s[8'h85]=8'h97; s[8'h86]=8'h44; s[8'h87]=8'h17;
            s[8'h88]=8'hc4; s[8'h89]=8'ha7; s[8'h8a]=8'h7e; s[8'h8b]=8'h3d;
            s[8'h8c]=8'h64; s[8'h8d]=8'h5d; s[8'h8e]=8'h19; s[8'h8f]=8'h73;
            s[8'h90]=8'h60; s[8'h91]=8'h81; s[8'h92]=8'h4f; s[8'h93]=8'hdc;
            s[8'h94]=8'h22; s[8'h95]=8'h2a; s[8'h96]=8'h90; s[8'h97]=8'h88;
            s[8'h98]=8'h46; s[8'h99]=8'hee; s[8'h9a]=8'hb8; s[8'h9b]=8'h14;
            s[8'h9c]=8'hde; s[8'h9d]=8'h5e; s[8'h9e]=8'h0b; s[8'h9f]=8'hdb;
            s[8'ha0]=8'he0; s[8'ha1]=8'h32; s[8'ha2]=8'h3a; s[8'ha3]=8'h0a;
            s[8'ha4]=8'h49; s[8'ha5]=8'h06; s[8'ha6]=8'h24; s[8'ha7]=8'h5c;
            s[8'ha8]=8'hc2; s[8'ha9]=8'hd3; s[8'haa]=8'hac; s[8'hab]=8'h62;
            s[8'hac]=8'h91; s[8'had]=8'h95; s[8'hae]=8'he4; s[8'haf]=8'h79;
            s[8'hb0]=8'he7; s[8'hb1]=8'hc8; s[8'hb2]=8'h37; s[8'hb3]=8'h6d;
            s[8'hb4]=8'h8d; s[8'hb5]=8'hd5; s[8'hb6]=8'h4e; s[8'hb7]=8'ha9;
            s[8'hb8]=8'h6c; s[8'hb9]=8'h56; s[8'hba]=8'hf4; s[8'hbb]=8'hea;
            s[8'hbc]=8'h65; s[8'hbd]=8'h7a; s[8'hbe]=8'hae; s[8'hbf]=8'h08;
            s[8'hc0]=8'hba; s[8'hc1]=8'h78; s[8'hc2]=8'h25; s[8'hc3]=8'h2e;
            s[8'hc4]=8'h1c; s[8'hc5]=8'ha6; s[8'hc6]=8'hb4; s[8'hc7]=8'hc6;
            s[8'hc8]=8'he8; s[8'hc9]=8'hdd; s[8'hca]=8'h74; s[8'hcb]=8'h1f;
            s[8'hcc]=8'h4b; s[8'hcd]=8'hbd; s[8'hce]=8'h8b; s[8'hcf]=8'h8a;
            s[8'hd0]=8'h70; s[8'hd1]=8'h3e; s[8'hd2]=8'hb5; s[8'hd3]=8'h66;
            s[8'hd4]=8'h48; s[8'hd5]=8'h03; s[8'hd6]=8'hf6; s[8'hd7]=8'h0e;
            s[8'hd8]=8'h61; s[8'hd9]=8'h35; s[8'hda]=8'h57; s[8'hdb]=8'hb9;
            s[8'hdc]=8'h86; s[8'hdd]=8'hc1; s[8'hde]=8'h1d; s[8'hdf]=8'h9e;
            s[8'he0]=8'he1; s[8'he1]=8'hf8; s[8'he2]=8'h98; s[8'he3]=8'h11;
            s[8'he4]=8'h69; s[8'he5]=8'hd9; s[8'he6]=8'h8e; s[8'he7]=8'h94;
            s[8'he8]=8'h9b; s[8'he9]=8'h1e; s[8'hea]=8'h87; s[8'heb]=8'he9;
            s[8'hec]=8'hce; s[8'hed]=8'h55; s[8'hee]=8'h28; s[8'hef]=8'hdf;
            s[8'hf0]=8'h8c; s[8'hf1]=8'ha1; s[8'hf2]=8'h89; s[8'hf3]=8'h0d;
            s[8'hf4]=8'hbf; s[8'hf5]=8'he6; s[8'hf6]=8'h42; s[8'hf7]=8'h68;
            s[8'hf8]=8'h41; s[8'hf9]=8'h99; s[8'hfa]=8'h2d; s[8'hfb]=8'h0f;
            s[8'hfc]=8'hb0; s[8'hfd]=8'h54; s[8'hfe]=8'hbb; s[8'hff]=8'h16;
            sb = s[in];
        end
    endfunction

    reg [31:0] w [0:43];
    reg [7:0]  rcon [0:10];

    always @(*) begin
        rcon[0]=8'h01; rcon[1]=8'h02; rcon[2]=8'h04;
        rcon[3]=8'h08; rcon[4]=8'h10; rcon[5]=8'h20;
        rcon[6]=8'h40; rcon[7]=8'h80; rcon[8]=8'h1b;
        rcon[9]=8'h36; rcon[10]=8'h6c;

        w[0]=key[127:96]; w[1]=key[95:64];
        w[2]=key[63:32];  w[3]=key[31:0];

        begin : expand
            integer i;
            for (i=4; i<44; i=i+1) begin
                if (i%4==0)
                    w[i] = w[i-4] ^
                        {sb(w[i-1][23:16])^rcon[i/4-1],
                         sb(w[i-1][15:8]),
                         sb(w[i-1][7:0]),
                         sb(w[i-1][31:24])};
                else
                    w[i] = w[i-4] ^ w[i-1];
            end
        end

        rk0  = {w[0], w[1],  w[2],  w[3] };
        rk1  = {w[4], w[5],  w[6],  w[7] };
        rk2  = {w[8], w[9],  w[10], w[11]};
        rk3  = {w[12],w[13], w[14], w[15]};
        rk4  = {w[16],w[17], w[18], w[19]};
        rk5  = {w[20],w[21], w[22], w[23]};
        rk6  = {w[24],w[25], w[26], w[27]};
        rk7  = {w[28],w[29], w[30], w[31]};
        rk8  = {w[32],w[33], w[34], w[35]};
        rk9  = {w[36],w[37], w[38], w[39]};
        rk10 = {w[40],w[41], w[42], w[43]};
    end
endmodule
