`timescale 1ns / 1ps

module bram_int_tb;

    parameter PERIOD_CLOK = 8.138;

    // Entradas
    reg  [31:0]     i       = 0;
    reg             clk     = 0;
    reg             valid   = 0;
    reg             sinc    = 1;
    reg  [31:0]     datos   = 32'b1111;
    reg             rdy_w;

    // Salidas
    wire [31:0]     addr;
    wire            clkb;
    wire [31:0]     din;
    wire            ena;
    wire            enb;
    wire [1:0]      rdy;
    wire [3:0]      we;
    wire [31:0]     size_data;

    // Instancia del módulo bajo prueba
    bram_int dut_int(
        //LI
        .clk(clk),
        .valid(valid),
        .sinc(sinc),
        .datos(datos),
        //LD
        .addr(addr),
        .clkb(clkb),
        .din(din),
        .en_a(ena),
        .en_b(enb),
        .rdy(rdy),
        .rdy_w(rdy_w),
        .we(we),
        .size_data(size_data)
    );

    // Generador de reloj
    always #4.069 clk   = ~clk;
    always #(150*PERIOD_CLOK)   sinc  = ~sinc;
    // Inicialización de señales
    initial begin
        // Con esto puedo abrir el GTKWave
        $dumpfile("bram_int_tb.vcd");
        $dumpvars(0,bram_int_tb);

        


        clk     = 0;
        valid   = 0;
        datos   = 0;
        #(4.5*PERIOD_CLOK);
        sinc    = 0;
        rdy_w   = 0;


        for (i = 0; i < 6; i = i + 1) begin
            valid = 1;              // Establece la señal valid en alto
            #PERIOD_CLOK; // Espera un periodo del reloj
            valid = 0; // Establece la señal valid en bajo
            #(10*PERIOD_CLOK); // Espera 10 periodos del reloj
        end

        rdy_w = 1;
        for (i = 0; i < 15; i = i + 1) begin
            valid = 1;              // Establece la señal valid en alto
            #PERIOD_CLOK; // Espera un periodo del reloj
            valid = 0; // Establece la señal valid en bajo
            #(10*PERIOD_CLOK); // Espera 10 periodos del reloj
        end

        rdy_w = 0;
        for (i = 0; i < 10; i = i + 1) begin
            valid = 1;              // Establece la señal valid en alto
            #PERIOD_CLOK; // Espera un periodo del reloj
            valid = 0; // Establece la señal valid en bajo
            #(10*PERIOD_CLOK); // Espera 10 periodos del reloj
        end


        #(400*PERIOD_CLOK);
        $finish;
    end

    //initial begin
    //    $monitor("Time = %0t, Senial = %d, Senial Modulada = %d", $time, senial, senial_mod);
    //end

endmodule
