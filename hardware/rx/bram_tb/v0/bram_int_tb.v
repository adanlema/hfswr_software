`timescale 1ns / 1ps

module bram_int_tb;

    parameter PERIOD_CLOK = 8.138;

    // Entradas
    reg             clk = 0;
    reg             valid = 0;
    reg  [31:0]     datos = 32'b1111;
    reg  [31:0]     dout = 1'b1;

    // Salidas
    wire            enable;
    wire            we;
    wire [31:0]     din;
    wire [31:0]     addr;


    // Instancia del módulo bajo prueba
    bram_int dut_int(
        //LI
        .clk(clk),
        .valid(valid),
        .datos(datos),
        //LD
        .enable(enable),
        .dout(dout),
        .din(din),
        .we(we),
        .addr(addr)
    );

    // Generador de reloj
    always #4.069 clk = ~clk;

    // Inicialización de señales
    initial begin
        // Con esto puedo abrir el GTKWave
        $dumpfile("bram_int_tb.vcd");
        $dumpvars(0,bram_int_tb);

        clk     = 0;
        valid   = 0;
        datos   = 0;
        dout    = 0;
        #(4.5*PERIOD_CLOK);
        
        // +1
        valid   = 1;
        #(PERIOD_CLOK);
        valid   = 0;
        #(10*PERIOD_CLOK);
        
        // +2
        valid   = 1;
        #(PERIOD_CLOK);
        valid   = 0;
        #(10*PERIOD_CLOK);
        
        // +3
        valid   = 1;
        #(PERIOD_CLOK);
        valid   = 0;
        #(10*PERIOD_CLOK);
        

        // +4
        valid   = 1;
        #(PERIOD_CLOK);
        dout    = 1;
        valid   = 0;
        #(10*PERIOD_CLOK);
        
        // +5
        valid   = 1;
        #(PERIOD_CLOK);
        valid   = 0;
        #(10*PERIOD_CLOK);

        // +6
        valid   = 1;
        #(PERIOD_CLOK);
        valid   = 0;
        #(10*PERIOD_CLOK);

        // +7
        valid   = 1;
        #(PERIOD_CLOK);
        valid   = 0;
        #(10*PERIOD_CLOK);

        //REINICIO MEDIANTE DOUT
        dout = 1'b0;
        #(PERIOD_CLOK);

        // +1
        #(PERIOD_CLOK);
        valid   = 1;
        #(PERIOD_CLOK);
        valid   = 0;
        #(10*PERIOD_CLOK);
        // +2
        valid   = 1;
        #(PERIOD_CLOK);
        valid   = 0;
        #(10*PERIOD_CLOK);



        #(50*PERIOD_CLOK);
        $finish;
    end

    //initial begin
    //    $monitor("Time = %0t, Senial = %d, Senial Modulada = %d", $time, senial, senial_mod);
    //end

endmodule
