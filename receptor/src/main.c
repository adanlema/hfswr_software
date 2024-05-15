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
#define PHASE_CARRIER  0
#define ADDR_RESET     1
#define WRITE_EN       2
#define LAST_ADDR      3
#define BUFFER_TO_READ 4
#define LOST_DATA      5
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
    addrs_t ctrl_regs = mapping_initialize(FPGA_MEM_CTRL, FPGA_MEM_CTRL_REG);
    if (addr_mem2 == NULL) {
        return -1;
    }
    printf("\n\n\nMapeo de memoria realizo con exito...\n");
    // Frecuencia de portadora 10 MHz
    ctrl_regs[PHASE_CARRIER] = 0x14d5555c;
    ctrl_regs[ADDR_RESET]    = 1;
    ctrl_regs[WRITE_EN]      = 3;

    uint8_t bandera    = 0;
    int16_t real       = 0;
    uint8_t mem1_leido = 0;
    uint8_t mem2_leido = 0;

    while (bandera < 5) {
        // printf("\n\nBuffer a leer: %u\n",ctrl_regs[BUFFER_TO_READ]);
        // printf("Se perdio datos %u\n",ctrl_regs[LOST_DATA]);
        // printf("Ultima direccion: %u\n",ctrl_regs[LAST_ADDR]);
        // printf("Phase:%d\nRESET:%d\nWRITE_EN:%d\n",ctrl_regs[PHASE_CARRIER],
        // ctrl_regs[ADDR_RESET], ctrl_regs[WRITE_EN]); printf("dato: %d\n",addr_mem1[0]);

        switch (ctrl_regs[BUFFER_TO_READ]) {
            case 1:
                // Agregar la logica para limitar la lectura a LAST_ADDR
                if (!mem1_leido) {
                    ctrl_regs[WRITE_EN] = (uint32_t)(0xFFFFFFFE & (ctrl_regs[WRITE_EN]));
                    printf("\n\nDatos buffer uno...\n");
                    for (addrs_t p = addr_mem1; p < (addr_mem1 + 200); ++p) {
                        real = (int16_t)(0xFFFF & (*p));
                        printf("%d\n", real);
                    }
                    if (ctrl_regs[LOST_DATA]) {
                        printf("\n\nSe Perdieron datos...\n");
                    }
                    ctrl_regs[WRITE_EN] = (uint32_t)(0x1 | (ctrl_regs[WRITE_EN]));
                    bandera++;
                    mem1_leido = 1;
                    mem2_leido = 0;
                }
                break;
            case 2:
                // Agregar la logica para limitar la lectura a LAST_ADDR
                if (!mem2_leido) {
                    ctrl_regs[WRITE_EN] = (uint32_t)(0xFFFFFFFD & (ctrl_regs[WRITE_EN]));
                    printf("\n\nDatos buffer dos...\n");
                    for (addrs_t p = addr_mem2; p < (addr_mem2 + 200); ++p) {
                        real = (int16_t)(0xFFFF & (*p));
                        printf("%d\n", real);
                    }
                    if (ctrl_regs[LOST_DATA]) {
                        printf("\n\nSe Perdieron datos...\n");
                    }
                    ctrl_regs[WRITE_EN] = (uint32_t)(0x2 | (ctrl_regs[WRITE_EN]));
                    bandera++;
                    mem1_leido = 0;
                    mem2_leido = 1;
                }
                break;
            default:
                //              bandera++;
                break;
        };

        // if (addr_mem1[FPGA_OFFSET_VALID] == 1) {
        //     addr_mem1[FPGA_OFFSET_VALID] = 0;
        //     printf("\n\nDatos buffer uno...\n");
        //     for (addrs_t p = addr_mem1; p < (addr_mem1 + 200); ++p) {
        //         real = (int16_t)(0xFFFF * (*p));
        //         printf("%d\n", real);
        //     }
        //     bandera++;
        // }
        // if (addr_mem2[FPGA_OFFSET_VALID] == 1) {
        //     addr_mem2[FPGA_OFFSET_VALID] = 0;
        //     printf("\n\nDatos buffer dos...\n");
        //     for (addrs_t p = addr_mem2; p < (addr_mem2 + 200); ++p) {
        //         real = (int16_t)(0xFFFF * (*p));
        //         printf("%d\n", real);
        //     }
        //     bandera++;
        // }
    };

    mapping_finalize(addr_mem1, FPGA_REG);
    mapping_finalize(addr_mem2, FPGA_REG);
    mapping_finalize(ctrl_regs, FPGA_MEM_CTRL_REG);
    return 0;
}
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
