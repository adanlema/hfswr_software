/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include "xil_types.h"
#include "xstatus.h"
#include "xsysmon.h"
#include "xparameters.h"
/*==================[macros and definitions]=================================*/
#define FPGA_BASE_ADDRESS 0x40000000
#define FPGA_OFFSET_CODE  0
#define CODE_BARKER11     0x0712
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
int main() {
    uint32_t senial = 0;

    printf("Bienvenido al programa de modificación de señal en la FPGA.\n");
    Xil_Out32(FPGA_BASE_ADDRESS + FPGA_OFFSET_CODE, CODE_BARKER11);
    printf("Codigo actualizado\n");
    return 0;
}
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/