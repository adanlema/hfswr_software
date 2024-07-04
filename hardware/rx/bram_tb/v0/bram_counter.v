module bram_counter (
    input           clk,
    input           hab,
    input           valid,
    input           rst,
    // SALIDA
    output          enable,
    output [31:0]   addr
);

//////////////////////////////////////////////////////////////////////////////////
//      CONSTANST
//////////////////////////////////////////////////////////////////////////////////
parameter COUNT_MAX = 2;
parameter POS_DIG   = 13;
//////////////////////////////////////////////////////////////////////////////////
//      WIRE AND REGISTERS
//////////////////////////////////////////////////////////////////////////////////

reg                 bandera = 0;
reg [7:0]           count = 0;
reg [31:0]          addr_count = 0;


always @(posedge clk) begin
    if(rst) begin
        addr_count <= 0;
    end else begin
        if(!hab && valid && !bandera) begin
            bandera <= 1'b1;
        end

        if(bandera) begin
            if (count < COUNT_MAX) begin
                count       <= count + 1;
            end else begin
                count       <= 1'b0;
                addr_count  <= addr_count + 8'd4;
                bandera     <= 1'b0;
            end
        end
    end
end


//////////////////////////////////////////////////////////////////////////////////
//      SALIDAS
//////////////////////////////////////////////////////////////////////////////////

assign addr         = addr_count;
assign enable       = addr_count[POS_DIG];

endmodule