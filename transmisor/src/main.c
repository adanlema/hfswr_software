/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include "fpga_driver.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
int main() {
    /*  Inicializamos el bloque de memoria a modificar */
    if (fpga_initialize() != 0) {
        printf("Error al inicializar el driver de la FPGA.\n");
        return -1;
    }

    printf("Bienvenido al programa de modificación de señal en la FPGA.\n");
    /*  Variables por defecto */
    uint32_t PRF  = 50;
    uint32_t AB   = 5000;
    uint32_t FREQ = 10000000;

    /* Escritura y liberacion del bloque */
    fpga_write_registers(PRF, AB, FREQ);
    fpga_finalize();

    printf("Parámetros actualizados.\n");

    return 0;
}

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
