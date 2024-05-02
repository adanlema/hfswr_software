/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include "al_mapping.h"
/*==================[macros and definitions]=================================*/
#define PRF  50
#define AB   5000
#define FREQ 10000000

#define BARKER7_CODE  0x72
#define BARKER7_NUM   0x7
#define BARKER11_CODE 0x0712
#define BARKER11_NUM  0xB
#define BARKER13_CODE 0x1F35
#define BARKER13_NUM  0xD
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

int main() {
    addrs_t addr_fpga = mapping_initialize(FPGA_ADDRS, FPGA_REG);
    if (addr_fpga == NULL) {
        return -1;
    }
    printf("\n\n\nMapeo de memoria realizo con exito...\n");

    /*  Variables por defecto */
    uint32_t prt_value   = ceil(122880000 / PRF);
    uint32_t phase_value = ceil((FREQ * 1e9) / 28610229);
    uint32_t tb          = ceil(122880000 / AB);
    uint32_t t_value     = ceil(BARKER11_NUM * tb);

    /* Escritura y liberacion del bloque */
    addr_fpga[OFFSET_START]  = 0;
    addr_fpga[OFFSET_PHASE]  = phase_value;
    addr_fpga[OFFSET_PERIOD] = t_value;
    addr_fpga[OFFSET_PRT]    = prt_value;
    addr_fpga[OFFSET_CODE]   = BARKER11_CODE;
    addr_fpga[OFFSET_NUMDIG] = BARKER11_NUM;
    addr_fpga[OFFSET_TB]     = tb;
    addr_fpga[OFFSET_START]  = 1;

    mapping_finalize(addr_fpga, FPGA_REG);
    return 0;
}

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
