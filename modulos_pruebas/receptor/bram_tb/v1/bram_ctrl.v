module bram_ctrl (
    //LI
    input               clk,
    input               en,
    input               sinc,
    input               sinc_edge,
    output              rst_count,
    //LD
    output              en_a,
    output              en_b,
    output              rdy,
    output  [3:0]       we
);

//////////////////////////////////////////////////////////////////////////////////
//      WIRE AND REGISTERS
//////////////////////////////////////////////////////////////////////////////////
parameter               EST_INIT        = 2'b00;
parameter               EST_MEM1        = 2'b01;
parameter               EST_MEM2        = 2'b10;

reg     [1:0]           estado_actual   = 0;
reg                     rst_reg         = 1;
reg                     rst_bd          = 0;
reg                     rdy_reg         = 0;
//////////////////////////////////////////////////////////////////////////////////
//      LOGIC
//////////////////////////////////////////////////////////////////////////////////

always @(posedge clk) begin
    if(rst_bd && sinc) begin
        rst_reg <= 1'b0;
        rst_bd  <= 1'b0;        
    end
end

always @(posedge en) begin
    case (estado_actual)
        EST_INIT: begin
            if(sinc_edge) begin
                estado_actual   <= EST_MEM1;
                rst_reg         <= 1'b0;
                rdy_reg         <= 1'b0;
            end
        end
        EST_MEM1: begin
            if(sinc) begin
                if(en) begin
                    rst_reg         <= 1'b1;
                    rst_bd          <= 1'b1;
                    estado_actual   <= EST_MEM2; 
                end
            end else begin
                rst_reg             <= 1'b1;
                rdy_reg             <= 1'b1;
                estado_actual       <= EST_INIT;
            end
        end
        EST_MEM2: begin
            if(sinc) begin
                if(en) begin
                    rst_reg         <= 1'b1;
                    rdy_reg         <= 1'b1;
                    estado_actual   <= EST_INIT; 
                end
            end else begin
                rst_reg             <= 1'b1;
                rdy_reg             <= 1'b1;
                estado_actual       <= EST_INIT;
            end
        end
        default: begin
            estado_actual           <= EST_INIT;
            rst_reg                 <= 1'b1;
            rst_bd                  <= 1'b0;
            rdy_reg                 <= 1'b0;
        end

    endcase
end


//////////////////////////////////////////////////////////////////////////////////
//      SALIDAS
//////////////////////////////////////////////////////////////////////////////////

assign rst_count    = rst_reg;
assign rdy          = rdy_reg;

endmodule