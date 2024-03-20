module modulador_bpsk (
    input wire clk,
    input wire rst,
    input wire sinc,
    input wire [15:0] cod,
    input [13:0] senial,
    output[13:0] senial_mod
);

parameter CERO_DAC = 16'h1FFF;
wire code;
wire [13:0] datos_mixed;
reg [13:0] salida = CERO_DAC;

code_generator code_generator_inst (
    .clk(clk),
    .rst(rst),
    .sinc(sinc),
    .codigo(cod),
    .out(code)
);

mixed_bpsk mixed_bpsk_inst (
    .clk(clk),
    .rst(rst),
    .cod(code),
    .senial(senial),
    .senial_mod(datos_mixed)
);

always @(posedge clk or posedge rst) begin
    if(!rst) begin
        salida <= CERO_DAC;
    end else begin
        if (sinc == 0) begin
            salida = CERO_DAC;
        end else begin
            salida = datos_mixed; 
        end
    end 
end

assign senial_mod = salida;

endmodule