module bram_ctrl (
    //LI
    input  wire         clk,
    input  wire         en,
    input  wire         sinc,
    input  wire         sinc_edge,
    output wire         rst_count,
    input  wire [31:0]  addr,
    //LD
    output wire         en_a,
    output wire         en_b,
    input  wire [1:0]   rdy_w,
    output wire [1:0]   rdy,
    output wire [31:0]  size_data
);

//////////////////////////////////////////////////////////////////////////////////
//      WIRE AND REGISTERS
//////////////////////////////////////////////////////////////////////////////////
parameter               EST_INIT        = 2'b00;
parameter               EST_MEM1        = 2'b01;
parameter               EST_MEM2        = 2'b10;

reg                     rst_reg         = 1;
reg                     ena_reg         = 0;
reg                     enb_reg         = 0;
reg     [1:0]           estado_actual   = 0;
reg     [1:0]           rdy_reg         = 0;
reg     [31:0]          size_reg        = 0;


//////////////////////////////////////////////////////////////////////////////////
//      LOGIC
//////////////////////////////////////////////////////////////////////////////////

always @(posedge clk) begin
    case (estado_actual)
        EST_INIT: begin
            if(sinc_edge && (rdy_w == 2'b00)) begin
                rst_reg         <= 1'b0;
                ena_reg         <= 1'b1;
                enb_reg         <= 1'b0;
                rdy_reg         <= 2'b00;
                estado_actual   <= EST_MEM1;
            end
        end
        EST_MEM1: begin
            if(sinc) begin
                if(en) begin
                    rst_reg         <= 1'b1;
                    ena_reg         <= 1'b0;
                    enb_reg         <= 1'b1;
                    rdy_reg         <= 2'b01;
                    size_reg        <= 32'd2048;
                    estado_actual   <= EST_MEM2; 
                end
            end else begin
                rst_reg             <= 1'b1;
                ena_reg             <= 1'b0;
                enb_reg             <= 1'b0;
                rdy_reg             <= 2'b01;
                size_reg            <= (addr/4) + 1;
                estado_actual       <= EST_INIT;
            end
        end
        EST_MEM2: begin
            if(sinc) begin
                //Reseteamos el contador...
                if(rst_reg) begin
                    rst_reg         <= 1'b0;
                end
            
                if(en) begin
                    rst_reg         <= 1'b1;
                    ena_reg         <= 1'b0;
                    enb_reg         <= 1'b0;
                    rdy_reg         <= 2'b11;
                    size_reg        <= 32'd4096;
                    estado_actual   <= EST_INIT; 
                end
            end else begin
                rst_reg             <= 1'b1;
                ena_reg             <= 1'b0;
                enb_reg             <= 1'b0;
                rdy_reg             <= 2'b11;
                size_reg            <= size_reg + (addr/4) + 1;
                estado_actual       <= EST_INIT;
            end
        end
        default: begin
            rst_reg                 <= 1'b1;
            ena_reg                 <= 1'b0;
            enb_reg                 <= 1'b0;
            rdy_reg                 <= 2'b00;
            size_reg                <= 32'b0;
            estado_actual           <= EST_INIT;

        end

    endcase
end


//////////////////////////////////////////////////////////////////////////////////
//      SALIDAS
//////////////////////////////////////////////////////////////////////////////////

assign  rst_count   =   rst_reg;
assign  en_a        =   ena_reg;
assign  en_b        =   enb_reg;
assign  rdy         =   rdy_reg;
assign  size_data   =   size_reg;

endmodule