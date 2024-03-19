`timescale 1ns / 1ps

module modulador_bpsk_tb;

    parameter SIM_TIME = 150000;        // Tiempo de simulación de 150[us]
    parameter TIEMPO_ESCUCHA = 200000;
    // BARKER 11 - [1],[1],[1],[0],[0],[0],[1],[0],[0],[1],[0]

    reg clk;
    reg sinc;
    reg rst;
    wire [13:0] senial;
    wire [13:0] senial_mod;
    reg  [15:0] codigo;

    // Instancia del módulo bajo prueba
    sine_generator dut_sine (
        .clk(clk),
        .rst(rst),
        .dac_output(senial)
    );

    modulador_bpsk dut_modulador (
        .clk(clk),
        .rst(rst),
        .sinc(sinc),
        .cod(codigo),
        .senial(senial),
        .senial_mod(senial_mod)
    );

    // Generador de reloj
    always #4.069 clk = ~clk;

    // Inicialización de señales
    initial begin
        // Con esto puedo abrir el GTKWave
        $dumpfile("modulador_bpsk_tb.vcd");
        $dumpvars(0,modulador_bpsk_tb);

        clk    = 0;
        codigo = 16'b11100010010;
        rst    = 0;
        sinc   = 0;
        #10 rst = 1;
        #10 rst = 0;
        sinc = 1;
        // Esperar un tiempo.
        #SIM_TIME;
        sinc = 0;
        #SIM_TIME;
        sinc = 1;
        #SIM_TIME;
        sinc = 0;
        #50000;
        // Finalizar la simulación
        $finish;
    end

    initial begin
        $monitor("Time = %0t, Senial = %d, Senial Modulada = %d", $time, senial, senial_mod);
    end

endmodule
