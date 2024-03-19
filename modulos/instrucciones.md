# Pasar el codigo a la placa

- TERMINAL1 
    * ssh root@rp-xxxxxx.local
    * CLAVE: root
    * redpitaya> rw

- TERMINAL2 (EJECUTABLE DEL ARCHIVO)
    * scp ARCHIVO_BINARIO root@rp-xxxxxx.local:/root

- TERMINAL1
    * ls
    * sudo ./ARCHIVO_BINARIO


- Para Cortex-A9 se recomienda el siguiente compilador.
https://docs.amd.com/r/2021.2-English/ug1400-vitis-embedded/Arm-Cortex-A9-Compiler-Usage-and-Options
    * Primero instalamos el compilador.
        * sudo apt update
        * sudo apt install gcc-arm-none-eabi
    * Compilamos para generar el binario.
        * gcc -c file.c -o file.o
        * gcc file.o -o programa_ejecutable.elf
        * ./programa_ejecutable.elf

