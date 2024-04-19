module bram_int (
    // Entradas
    input               clk,
    input               valid,
    input   [31:0]      datos,
    // Salidas
    output              enable,
    output              we,
    input   [31:0]      dout,
    output  [31:0]      addr,
    output  [31:0]      din
);

//////////////////////////////////////////////////////////////////////////////////
//      WIRE AND REGISTERS
//////////////////////////////////////////////////////////////////////////////////

wire [31:0]         dout1;
//CONTADOR
wire                en;
wire                rst_ctrl;
wire [31:0]         addr_count;

//CTRL
wire                valid_ctrl;
wire [31:0]         dout_ctrl;
wire [31:0]         addr_ctrl;
wire [31:0]         din_ctrl;


//COMPUERTA AND
wire                valid_and;

//SALIDA
wire                enable_wire;
wire                we_wire;
wire [31:0]         dout_wire;
wire [31:0]         addr_wire;
wire [31:0]         din_wire;
//////////////////////////////////////////////////////////////////////////////////
//      LOGICA
//////////////////////////////////////////////////////////////////////////////////

bram_counter counter_inst (
    //LI
    .clk(clk),
    .hab(en),
    .valid(valid),
    .rst(rst_ctrl),
    //LD
    .enable(en),
    .addr(addr_count)
);

bram_ctrl ctrl_inst (
    //LI
    .clk(clk),
    .en(en),
    .rst_count(rst_ctrl),
    //LD
    .dout(dout_ctrl),
    .din(din_ctrl),
    .valid(valid_ctrl),
    .addr(addr_ctrl)
);


assign valid_and = (!en) && valid;

bram_mult multiplexor_inst(
    .clk(clk),
    .en(en),
    //ENT1
    .addr1(addr_count),
    .din1(datos),
    .dout1(dout1),
    .valid1(valid_and),
    //ENT2
    .addr2(addr_ctrl),
    .din2(din_ctrl),
    .dout2(dout_ctrl),
    .valid2(valid_ctrl),
    //SALIDA
    .valid(we),
    .enable(enable),
    .addr(addr),
    .din(din),
    .dout(dout)
);

//////////////////////////////////////////////////////////////////////////////////
//      SALIDAS
//////////////////////////////////////////////////////////////////////////////////

//assign enable   = enable_wire;
//assign valid    = we_wire;
//assign addr     = addr_wire;
//assign din      = din_wire;

endmodule