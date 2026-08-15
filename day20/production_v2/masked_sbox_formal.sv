module masked_sbox_formal(
    input wire clk,
    input wire rst,
    input wire [7:0] data_in,
    input wire [7:0] mask_in
);
    wire [7:0] data_out, mask_out;

    masked_sbox dut (
        .clk(clk), .rst(rst),
        .data_in(data_in), .mask_in(mask_in),
        .data_out(data_out), .mask_out(mask_out)
    );

    // Reference (golden) table — module-level, single instance, same
    // fix as the DUT: declared once via initial block, not once per
    // function call.
    reg [7:0] ref_table [0:255];
    initial begin
        ref_table[8'h00]=8'h63; ref_table[8'h01]=8'h7c; ref_table[8'h02]=8'h77; ref_table[8'h03]=8'h7b;
        ref_table[8'h04]=8'hf2; ref_table[8'h05]=8'h6b; ref_table[8'h06]=8'h6f; ref_table[8'h07]=8'hc5;
        ref_table[8'h08]=8'h30; ref_table[8'h09]=8'h01; ref_table[8'h0a]=8'h67; ref_table[8'h0b]=8'h2b;
        ref_table[8'h0c]=8'hfe; ref_table[8'h0d]=8'hd7; ref_table[8'h0e]=8'hab; ref_table[8'h0f]=8'h76;
        ref_table[8'h10]=8'hca; ref_table[8'h11]=8'h82; ref_table[8'h12]=8'hc9; ref_table[8'h13]=8'h7d;
        ref_table[8'h14]=8'hfa; ref_table[8'h15]=8'h59; ref_table[8'h16]=8'h47; ref_table[8'h17]=8'hf0;
        ref_table[8'h18]=8'had; ref_table[8'h19]=8'hd4; ref_table[8'h1a]=8'ha2; ref_table[8'h1b]=8'haf;
        ref_table[8'h1c]=8'h9c; ref_table[8'h1d]=8'ha4; ref_table[8'h1e]=8'h72; ref_table[8'h1f]=8'hc0;
        ref_table[8'h20]=8'hb7; ref_table[8'h21]=8'hfd; ref_table[8'h22]=8'h93; ref_table[8'h23]=8'h26;
        ref_table[8'h24]=8'h36; ref_table[8'h25]=8'h3f; ref_table[8'h26]=8'hf7; ref_table[8'h27]=8'hcc;
        ref_table[8'h28]=8'h34; ref_table[8'h29]=8'ha5; ref_table[8'h2a]=8'he5; ref_table[8'h2b]=8'hf1;
        ref_table[8'h2c]=8'h71; ref_table[8'h2d]=8'hd8; ref_table[8'h2e]=8'h31; ref_table[8'h2f]=8'h15;
        ref_table[8'h30]=8'h04; ref_table[8'h31]=8'hc7; ref_table[8'h32]=8'h23; ref_table[8'h33]=8'hc3;
        ref_table[8'h34]=8'h18; ref_table[8'h35]=8'h96; ref_table[8'h36]=8'h05; ref_table[8'h37]=8'h9a;
        ref_table[8'h38]=8'h07; ref_table[8'h39]=8'h12; ref_table[8'h3a]=8'h80; ref_table[8'h3b]=8'he2;
        ref_table[8'h3c]=8'heb; ref_table[8'h3d]=8'h27; ref_table[8'h3e]=8'hb2; ref_table[8'h3f]=8'h75;
        ref_table[8'h40]=8'h09; ref_table[8'h41]=8'h83; ref_table[8'h42]=8'h2c; ref_table[8'h43]=8'h1a;
        ref_table[8'h44]=8'h1b; ref_table[8'h45]=8'h6e; ref_table[8'h46]=8'h5a; ref_table[8'h47]=8'ha0;
        ref_table[8'h48]=8'h52; ref_table[8'h49]=8'h3b; ref_table[8'h4a]=8'hd6; ref_table[8'h4b]=8'hb3;
        ref_table[8'h4c]=8'h29; ref_table[8'h4d]=8'he3; ref_table[8'h4e]=8'h2f; ref_table[8'h4f]=8'h84;
        ref_table[8'h50]=8'h53; ref_table[8'h51]=8'hd1; ref_table[8'h52]=8'h00; ref_table[8'h53]=8'hed;
        ref_table[8'h54]=8'h20; ref_table[8'h55]=8'hfc; ref_table[8'h56]=8'hb1; ref_table[8'h57]=8'h5b;
        ref_table[8'h58]=8'h6a; ref_table[8'h59]=8'hcb; ref_table[8'h5a]=8'hbe; ref_table[8'h5b]=8'h39;
        ref_table[8'h5c]=8'h4a; ref_table[8'h5d]=8'h4c; ref_table[8'h5e]=8'h58; ref_table[8'h5f]=8'hcf;
        ref_table[8'h60]=8'hd0; ref_table[8'h61]=8'hef; ref_table[8'h62]=8'haa; ref_table[8'h63]=8'hfb;
        ref_table[8'h64]=8'h43; ref_table[8'h65]=8'h4d; ref_table[8'h66]=8'h33; ref_table[8'h67]=8'h85;
        ref_table[8'h68]=8'h45; ref_table[8'h69]=8'hf9; ref_table[8'h6a]=8'h02; ref_table[8'h6b]=8'h7f;
        ref_table[8'h6c]=8'h50; ref_table[8'h6d]=8'h3c; ref_table[8'h6e]=8'h9f; ref_table[8'h6f]=8'ha8;
        ref_table[8'h70]=8'h51; ref_table[8'h71]=8'ha3; ref_table[8'h72]=8'h40; ref_table[8'h73]=8'h8f;
        ref_table[8'h74]=8'h92; ref_table[8'h75]=8'h9d; ref_table[8'h76]=8'h38; ref_table[8'h77]=8'hf5;
        ref_table[8'h78]=8'hbc; ref_table[8'h79]=8'hb6; ref_table[8'h7a]=8'hda; ref_table[8'h7b]=8'h21;
        ref_table[8'h7c]=8'h10; ref_table[8'h7d]=8'hff; ref_table[8'h7e]=8'hf3; ref_table[8'h7f]=8'hd2;
        ref_table[8'h80]=8'hcd; ref_table[8'h81]=8'h0c; ref_table[8'h82]=8'h13; ref_table[8'h83]=8'hec;
        ref_table[8'h84]=8'h5f; ref_table[8'h85]=8'h97; ref_table[8'h86]=8'h44; ref_table[8'h87]=8'h17;
        ref_table[8'h88]=8'hc4; ref_table[8'h89]=8'ha7; ref_table[8'h8a]=8'h7e; ref_table[8'h8b]=8'h3d;
        ref_table[8'h8c]=8'h64; ref_table[8'h8d]=8'h5d; ref_table[8'h8e]=8'h19; ref_table[8'h8f]=8'h73;
        ref_table[8'h90]=8'h60; ref_table[8'h91]=8'h81; ref_table[8'h92]=8'h4f; ref_table[8'h93]=8'hdc;
        ref_table[8'h94]=8'h22; ref_table[8'h95]=8'h2a; ref_table[8'h96]=8'h90; ref_table[8'h97]=8'h88;
        ref_table[8'h98]=8'h46; ref_table[8'h99]=8'hee; ref_table[8'h9a]=8'hb8; ref_table[8'h9b]=8'h14;
        ref_table[8'h9c]=8'hde; ref_table[8'h9d]=8'h5e; ref_table[8'h9e]=8'h0b; ref_table[8'h9f]=8'hdb;
        ref_table[8'ha0]=8'he0; ref_table[8'ha1]=8'h32; ref_table[8'ha2]=8'h3a; ref_table[8'ha3]=8'h0a;
        ref_table[8'ha4]=8'h49; ref_table[8'ha5]=8'h06; ref_table[8'ha6]=8'h24; ref_table[8'ha7]=8'h5c;
        ref_table[8'ha8]=8'hc2; ref_table[8'ha9]=8'hd3; ref_table[8'haa]=8'hac; ref_table[8'hab]=8'h62;
        ref_table[8'hac]=8'h91; ref_table[8'had]=8'h95; ref_table[8'hae]=8'he4; ref_table[8'haf]=8'h79;
        ref_table[8'hb0]=8'he7; ref_table[8'hb1]=8'hc8; ref_table[8'hb2]=8'h37; ref_table[8'hb3]=8'h6d;
        ref_table[8'hb4]=8'h8d; ref_table[8'hb5]=8'hd5; ref_table[8'hb6]=8'h4e; ref_table[8'hb7]=8'ha9;
        ref_table[8'hb8]=8'h6c; ref_table[8'hb9]=8'h56; ref_table[8'hba]=8'hf4; ref_table[8'hbb]=8'hea;
        ref_table[8'hbc]=8'h65; ref_table[8'hbd]=8'h7a; ref_table[8'hbe]=8'hae; ref_table[8'hbf]=8'h08;
        ref_table[8'hc0]=8'hba; ref_table[8'hc1]=8'h78; ref_table[8'hc2]=8'h25; ref_table[8'hc3]=8'h2e;
        ref_table[8'hc4]=8'h1c; ref_table[8'hc5]=8'ha6; ref_table[8'hc6]=8'hb4; ref_table[8'hc7]=8'hc6;
        ref_table[8'hc8]=8'he8; ref_table[8'hc9]=8'hdd; ref_table[8'hca]=8'h74; ref_table[8'hcb]=8'h1f;
        ref_table[8'hcc]=8'h4b; ref_table[8'hcd]=8'hbd; ref_table[8'hce]=8'h8b; ref_table[8'hcf]=8'h8a;
        ref_table[8'hd0]=8'h70; ref_table[8'hd1]=8'h3e; ref_table[8'hd2]=8'hb5; ref_table[8'hd3]=8'h66;
        ref_table[8'hd4]=8'h48; ref_table[8'hd5]=8'h03; ref_table[8'hd6]=8'hf6; ref_table[8'hd7]=8'h0e;
        ref_table[8'hd8]=8'h61; ref_table[8'hd9]=8'h35; ref_table[8'hda]=8'h57; ref_table[8'hdb]=8'hb9;
        ref_table[8'hdc]=8'h86; ref_table[8'hdd]=8'hc1; ref_table[8'hde]=8'h1d; ref_table[8'hdf]=8'h9e;
        ref_table[8'he0]=8'he1; ref_table[8'he1]=8'hf8; ref_table[8'he2]=8'h98; ref_table[8'he3]=8'h11;
        ref_table[8'he4]=8'h69; ref_table[8'he5]=8'hd9; ref_table[8'he6]=8'h8e; ref_table[8'he7]=8'h94;
        ref_table[8'he8]=8'h9b; ref_table[8'he9]=8'h1e; ref_table[8'hea]=8'h87; ref_table[8'heb]=8'he9;
        ref_table[8'hec]=8'hce; ref_table[8'hed]=8'h55; ref_table[8'hee]=8'h28; ref_table[8'hef]=8'hdf;
        ref_table[8'hf0]=8'h8c; ref_table[8'hf1]=8'ha1; ref_table[8'hf2]=8'h89; ref_table[8'hf3]=8'h0d;
        ref_table[8'hf4]=8'hbf; ref_table[8'hf5]=8'he6; ref_table[8'hf6]=8'h42; ref_table[8'hf7]=8'h68;
        ref_table[8'hf8]=8'h41; ref_table[8'hf9]=8'h99; ref_table[8'hfa]=8'h2d; ref_table[8'hfb]=8'h0f;
        ref_table[8'hfc]=8'hb0; ref_table[8'hfd]=8'h54; ref_table[8'hfe]=8'hbb; ref_table[8'hff]=8'h16;
    end

    // FUNCTIONAL CORRECTNESS: registered (data_out ^ mask_out) must
    // equal ref_table[] of the PREVIOUS cycle's data_in (one-cycle
    // register latency in the DUT).
    always @(posedge clk) begin
        if (!rst && $past(1'b1) && !$past(rst))
            assert( (data_out ^ mask_out) == ref_table[$past(data_in)] );
    end

    always @(posedge clk) begin
        cover( mask_in != 8'h00 );
    end
endmodule
