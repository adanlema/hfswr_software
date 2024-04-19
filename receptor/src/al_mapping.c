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
/*==================[macros and definitions]=================================*/
#define CANTIDAD 10
/*==================[internal data declaration]==============================*/
static addrs_t fpga_addr[CANTIDAD] = {0};
static uint8_t posicion            = 0;
// static volatile uint32_t * fpga_addr = NULL;
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
addrs_t mapping_initialize(uint32_t addrs, uint32_t cant_reg) {
    if (posicion < 10) {
        posicion++;
    } else {
        return -1;
    }
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        perror("Error opening /dev/mem");
        exit(EXIT_FAILURE);
    }

    fpga_addr[posicion] =
        mmap(NULL, cant_reg * sizeof(int32_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, addrs);
    if (fpga_addr[posicion] == MAP_FAILED) {
        perror("Error mapping FPGA register");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
    return fpga_addr[posicion];
}
void mapping_finalize(addrs_t addr, uint32_t cant_reg) {
    if (addr != NULL) {
        munmap((void *)addr, cant_reg * sizeof(int32_t));
        addr = NULL;
    }
}
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/