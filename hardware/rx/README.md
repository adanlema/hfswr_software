# SIMULAR LOS MODULOS VERILOG

Para compilar los archivos en verilog usamos el simulador **IVERILOG** y graficamos mediante **GTKWAVE**. Para utilizar esto debemos realizar los siguientes comandos:

- iverilog.exe -o dsn bram_ctrl_tb.v bram_ctrl.v
- vpp.exe dsn
- gtkwave.exe bram_ctrl_tb.vcd

En este caso se utilizo un ejemplo de un bloque que se encarga de manejar una memoria BRAM. En caso de tener mas de un archivo **.v**, se los debe agregar en la primera linea de codigo, los demas comandos no tienen cambios.