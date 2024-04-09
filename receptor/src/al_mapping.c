/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h>

#include "al_mapping.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
static volatile uint32_t * fpga_addr = NULL;
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
volatile uint32_t * mapping_initialize() {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        perror("Error opening /dev/mem");
        exit(EXIT_FAILURE);
    }

    fpga_addr = mmap(NULL, FPGA_REG * sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd,
                     FPGA_BASE_ADDRESS);
    if (fpga_addr == MAP_FAILED) {
        perror("Error mapping FPGA register");
        close(fd);
        exit(EXIT_FAILURE);
    }

    return fpga_addr;
}
void mapping_finalize(volatile uint32_t * addr) {
    if (addr != NULL) {
        munmap((void *)addr, FPGA_REG * sizeof(uint32_t));
        addr = NULL;
    }
}
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/