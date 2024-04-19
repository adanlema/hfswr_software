`timescale 1ns / 1ps

module bram_counter_tb;

    parameter PERIOD_CLOK = 8.138;

    // Entradas
    reg             clk;
    reg             valid;
    reg             rst;
    // Salidas
    wire            en;
    wire [31:0]     addr;
    
    // Instancia del módulo bajo prueba
    bram_counter dut_counter (
        //LI
        .clk(clk),
        .hab(en),
        .valid(valid),
        .rst(rst),
        //LD
        .enable(en),
        .addr(addr)
    );

    // Generador de reloj
    always #4.069 clk = ~clk;

    // Inicialización de señales
    initial begin
        // Con esto puedo abrir el GTKWave
        $dumpfile("bram_counter_tb.vcd");
        $dumpvars(0,bram_counter_tb);

        clk     = 0;
        valid   = 0;
        rst     = 0;
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

        //RST
        rst     = 1;
        #(PERIOD_CLOK);
        rst     = 0;

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
