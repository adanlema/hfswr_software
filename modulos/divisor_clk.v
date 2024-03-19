module divisor_clk (
    input wire clk,
    input wire rst,
    output wire clk_div
);

reg salida = 0;
reg [15:0] counter = 0;

always @(posedge clk or posedge rst) begin
    if(!rst) begin
        salida = 0;
        counter = 0; 
    end else begin
        if(counter < 18432) begin
            counter = counter + 1;
        end else begin
            salida = ~salida;
            counter = 0;
        end
    end
end

assign clk_div = salida;

endmodule