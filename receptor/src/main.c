/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "al_client.h"
#include "al_mapping.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
int main() {

    addrs_t addr_mem1 = mapping_initialize(FPGA_MEM1, FPGA_REG);
    if (addr_mem1 == NULL) {
        return -1;
    }
    addrs_t addr_mem2 = mapping_initialize(FPGA_MEM2, FPGA_REG);
    if (addr_mem2 == NULL) {
        return -1;
    }
    printf("\n\n\nMapeo de memoria realizo con exito...\n");

    uint8_t bandera = 0;
    int16_t real    = 0;
    // banderas igual a 0
    addr_mem1[FPGA_OFFSET_VALID] = 0;
    addr_mem2[FPGA_OFFSET_VALID] = 0;

    while (bandera < 2) {
        if (addr_mem1[FPGA_OFFSET_VALID] == 1) {
            addr_mem1[FPGA_OFFSET_VALID] = 0;
            printf("\n\nDatos buffer uno...\n");
            for (addrs_t p = addr_mem1; p < (addr_mem1 + 200); ++p) {
                real = (int16_t)(0xFFFF * (*p));
                printf("%d\n", real);
            }
            bandera++;
        }
        if (addr_mem2[FPGA_OFFSET_VALID] == 1) {
            addr_mem2[FPGA_OFFSET_VALID] = 0;
            printf("\n\nDatos buffer dos...\n");
            for (addrs_t p = addr_mem2; p < (addr_mem2 + 200); ++p) {
                real = (int16_t)(0xFFFF * (*p));
                printf("%d\n", real);
            }
            bandera++;
        }
    };

    mapping_finalize(addr_mem1, FPGA_REG);
    mapping_finalize(addr_mem2, FPGA_REG);
    return 0;
}
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/