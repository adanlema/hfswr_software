module bram_int (
    // Entradas
    input  wire             clk,
    input  wire             valid,
    input  wire             sinc,
    input  wire [31:0]      datos,
    // Salidas
    output wire [31:0]      addr,
    output wire             clkb,
    output wire [31:0]      din,
    output wire             en_a,
    output wire             en_b,
    input  wire [1:0]       rdy_w,
    output wire [1:0]       rdy,
    output wire [3:0]       we,
    output wire [31:0]      size_data
);

//////////////////////////////////////////////////////////////////////////////////
//      WIRE AND REGISTERS
//////////////////////////////////////////////////////////////////////////////////

//CONTADOR
wire                en;
wire                rst_ctrl;
wire [31:0]         addr_count;

//SINC_EDGE
wire                sinc_wire;
wire                sincedge_wire;


//////////////////////////////////////////////////////////////////////////////////
//      LOGICA
//////////////////////////////////////////////////////////////////////////////////

bram_counter    bram_1 (
    //LI
    .clk(clk),
    .hab(en),
    .valid(valid),
    .rst(rst_ctrl),
    //LD
    .enable(en),
    .addr(addr_count)
);

assign  sinc_wire   = !sinc;

bram_sincedge   bram_2 (
    .clk(clk),
    .sinc(sinc_wire),
    .sinc_edge(sincedge_wire)
);

bram_ctrl       bram_3 (
    //LI
    .clk(clk),
    .en(en),
    .sinc(sinc_wire),
    .sinc_edge(sincedge_wire),
    .rst_count(rst_ctrl),
    .addr(addr_count),
    //LD
    .en_a(en_a),
    .en_b(en_b),
    .rdy_w(rdy_w),
    .rdy(rdy),
    .size_data(size_data)
);


//////////////////////////////////////////////////////////////////////////////////
//      SALIDAS
//////////////////////////////////////////////////////////////////////////////////

assign  clkb    = clk;
assign  we      = (valid && ~en) ? 4'b1111 : 4'b0000;
assign  addr    = addr_count;
assign  din     = datos;

endmodule