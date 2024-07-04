`timescale 1ns / 1ps

module sine_generator_tb;

    parameter SIM_TIME = 1000; // Tiempo de simulación en ps

    reg clk;
    reg rst;
    wire [13:0] dac_output;

    // Instancia del módulo bajo prueba
    sine_generator dut (
        .clk(clk),
        .rst(rst),
        .dac_output(dac_output)
    );

    // Generador de reloj
    always #4.069 clk = ~clk;

    // Inicialización de señales
    initial begin
        // Con esto puedo abrir el GTKWave
        $dumpfile("sine_generator_tb.vcd");
        $dumpvars(0,sine_generator_tb);

        clk = 0;
        rst = 0;
        #10 rst = 1; // Activar rst
        #10 rst = 0; // Desactivar rst
        // Esperar un tiempo para permitir que el módulo genere la onda sinusoidal
        #SIM_TIME;
        // Finalizar la simulación
        $finish;
    end

    // Visualización de la salida del DAC
    initial begin
        $monitor("Time = %0t, DAC Output = %d", $time, dac_output);
    end

endmodule
