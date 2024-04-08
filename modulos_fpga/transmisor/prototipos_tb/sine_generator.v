module sine_generator (
    input wire clk,
    input wire rst,
    output reg [13:0] dac_output
);

localparam FILE_SIZE = 12288;
parameter CLK_FREQ = 122880000;
parameter SIN_FREQ =   1000000;

// Tabla de onda sinusoidal precalculada e indice
reg [15:0] index;
reg [13:0] sine_table [0:FILE_SIZE-1];    // Tamaño de la tabla: 123
reg [13:0] salida;
reg [15:0] paso;
// Inicialización de la tabla de onda sinusoidal desde archivo
initial begin
    index = 0;
    paso = $ceil(FILE_SIZE / (CLK_FREQ / SIN_FREQ));
    $readmemb("sine_table.txt", sine_table);
    salida = sine_table[index];
end


// Proceso para generar la onda sinusoidal
always @(posedge clk or posedge rst) begin
    if(rst) begin
        index  = 0;
        salida = sine_table[0];    
    end else begin
        index = index + paso;
        if (index >= FILE_SIZE) begin
            index = index - FILE_SIZE;
        end 
        salida = sine_table[index];
    end
end


// Asignación del valor de salida del DAC
always @(*) begin
    dac_output = salida;
end

endmodule
