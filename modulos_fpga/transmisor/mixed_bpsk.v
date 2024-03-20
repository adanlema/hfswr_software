module mixed_bpsk (
    input wire clk,
    input wire rst,
    input wire cod,
    input [13:0] senial,
    output reg [13:0] senial_mod
);

parameter MAX_VALUE = 16383;
parameter CERO_DAC = 16'h1FFF;

reg [13:0] salida = CERO_DAC;

always @(posedge clk or posedge rst) begin
    if(!rst) begin
        salida = CERO_DAC;
    end else begin
        if(cod == 1) begin
            // Interpolación lineal para suavizar la transición
            salida = senial;
            //salida = (MAX_VALUE - senial + salida) >> 1; // Promedio de salida actual y el valor modulado
            //salida = MAX_VALUE;
        end else begin
            //salida = senial;
            salida = ~senial;
            //salida = MAX_VALUE / 2;
        end
    end
end

always @(*) begin
    senial_mod = {salida[14-1], ~salida[14-2:0]};
    //senial_mod = salida;
end

endmodule
