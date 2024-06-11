/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

#include "al_mapping.h"
#include "log_manager.h"
/*==================[macros and definitions]=================================*/
#define CANTIDAD 10
/*==================[internal data declaration]==============================*/
struct mapping_mem {
    addrs_t  addr;
    uint32_t size_reg;
    bool     ocupado;
};
static struct mapping_mem mapping[CANTIDAD] = {0};
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
addrs_t mappingInit(uint32_t addrs, uint32_t cant_reg) {
    uint8_t posicion = 0;
    int     i;
    for (i = 0; (i < CANTIDAD) && (posicion == 0); i++) {
        if (mapping[i].ocupado == false) {
            posicion = i;
            break;
        }
    }
    if (posicion == 0 && i == CANTIDAD) {
        log_add("No hay espacio disponible para más clientes.\n");
        return (addrs_t)NULL;
    }
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        log_add("[ERROR]Error al abrir /dev/mem");
        exit(EXIT_FAILURE);
    }
    addrs_t fpga_addr =
        mmap(NULL, cant_reg * sizeof(int32_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, addrs);
    if (fpga_addr == MAP_FAILED) {
        log_add("[ERROR]Error al mapear los registros de la FPGA.");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);

    mapping[posicion].addr     = fpga_addr;
    mapping[posicion].size_reg = cant_reg;
    mapping[posicion].ocupado  = true;
    return fpga_addr;
}
void mappingFinalize(addrs_t addr) {
    if (addr != NULL) {
        for (int i = 0; i < CANTIDAD; i++) {
            if ((mapping[i].ocupado) && (mapping[i].addr == addr)) {
                munmap((void *)addr, mapping[i].size_reg * sizeof(int32_t));
                mapping[i].addr     = (addrs_t)NULL;
                mapping[i].size_reg = 0;
                mapping[i].ocupado  = false;
                break;
            }
        }
    }
}
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/