/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
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
static addrs_t fpga_addr[CANTIDAD] = {0};
static uint8_t posicion            = 0;
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
addrs_t mappingInit(uint32_t addrs, uint32_t cant_reg) {
    if (posicion < 10) {
        posicion++;
    } else {
        return NULL;
    }
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        log_add("[ERROR]Error al abrir /dev/mem");
        exit(EXIT_FAILURE);
    }

    fpga_addr[posicion] =
        mmap(NULL, cant_reg * sizeof(int32_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, addrs);
    if (fpga_addr[posicion] == MAP_FAILED) {
        log_add("[ERROR]]Error al mapear los regisros de FPGA.");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
    return fpga_addr[posicion];
}
void mappingFinalize(addrs_t addr, uint32_t cant_reg) {
    if (addr != NULL) {
        munmap((void *)addr, cant_reg * sizeof(int32_t));
        addr = NULL;
    }
}
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/