`timescale 1ns / 1ps

module bram_ctrl_tb;

    parameter PERIOD_CLOK = 8.138;

    // Entradas
    reg             clk;
    reg             en;
    reg  [31:0]     dout;

    // Salidas
    wire            rst_count;
    wire            valid;
    wire [31:0]     din;
    wire [31:0]     addr;
    


    // Instancia del módulo bajo prueba
    bram_ctrl dut_bram (
        //LI
        .clk(clk),
        .en(en),
        .rst_count(rst_count),
        //LD
        .dout(dout),
        .din(din),
        .valid(valid),
        .addr(addr)
    );

    // Generador de reloj
    always #4.069 clk = ~clk;

    // Inicialización de señales
    initial begin
        // Con esto puedo abrir el GTKWave
        $dumpfile("bram_ctrl_tb.vcd");
        $dumpvars(0,bram_ctrl_tb);

        clk     = 0;
        en      = 0;
        dout    = 1;
        #(10.5*PERIOD_CLOK);
        en      = 1;
        #(10*PERIOD_CLOK);
        dout    = 0;
        #(2*PERIOD_CLOK);
        en      = 0;
        #(50*PERIOD_CLOK);
        $finish;
    end

    //initial begin
    //    $monitor("Time = %0t, Senial = %d, Senial Modulada = %d", $time, senial, senial_mod);
    //end

endmodule
