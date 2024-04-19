module bram_mult (
    input               clk,
    input               en,
    //ENT1
    input   [31:0]      addr1,
    input   [31:0]      din1,
    output  [31:0]      dout1,
    input               valid1,
    //ENT2
    input   [31:0]      addr2,
    input   [31:0]      din2,
    output  [31:0]      dout2,
    input               valid2,
    // SALIDA
    output              valid,
    output              enable,
    output  [31:0]      addr,
    output  [31:0]      din,
    input   [31:0]      dout
);

//////////////////////////////////////////////////////////////////////////////////
//      SALIDAS
//////////////////////////////////////////////////////////////////////////////////

assign enable       = 1'b1;
assign addr         = (!en) ? addr1  : addr2;
assign din          = (!en) ? din1   : din2;
assign valid        = (!en) ? valid1 : valid2;
assign dout1        = (!en) ? dout   : 32'b1;
assign dout2        =  (en) ? dout   : 32'b1;

endmodule