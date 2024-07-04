module bram_ctrl (
    input           clk,
    input           en,
    // RESET CONTADOR
    output          rst_count,
    // ESCRITURA PARA EL PS
    input  [31:0]   dout,
    output          valid,
    output [31:0]   din,
    output [31:0]   addr
);

//////////////////////////////////////////////////////////////////////////////////
//      CONSTANS
//////////////////////////////////////////////////////////////////////////////////
parameter ADDRS = 2047;

//////////////////////////////////////////////////////////////////////////////////
//      WIRE AND REGISTERS
//////////////////////////////////////////////////////////////////////////////////

//RESET DEL CONTADOR
reg                 rst_reg = 0;
//ESCRITURA EN BRAM
reg [31:0]          datos_reg = 0;
reg [31:0]          addr_reg = 0;
reg                 valid_reg = 0;
reg                 bandera = 0;
reg [7:0]           count = 0;


always @(posedge clk) begin
    if(en && !bandera && !rst_reg) begin
        datos_reg   <= 1'b1;
        valid_reg   <= 1'b1;
        bandera     <= 1'b1;
        count       <= 1'b0;
    end
    // Retardo para asegurar la escritura por parte del PL
    if (bandera && valid_reg) begin
        if (count < 2) begin
            count       <= count + 1;
        end else begin
            count       <= 1'b0;
            valid_reg   <= 1'b0;
        end
    end 

    if(bandera && !valid_reg && !dout[0]) begin
        rst_reg         <= 1'b1;
        bandera         <= 1'b0;
        datos_reg       <= 1'b0;
    end else begin
        rst_reg         <= 1'b0;
    end
end


//////////////////////////////////////////////////////////////////////////////////
//      SALIDAS
//////////////////////////////////////////////////////////////////////////////////

assign rst_count    = rst_reg;
assign valid        = valid_reg;
assign din          = datos_reg;
assign addr         = ADDRS;

endmodule