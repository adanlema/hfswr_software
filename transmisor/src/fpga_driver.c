/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

/*==================[inclusions]=============================================*/
#include "fpga_driver.h"
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <math.h>
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
static volatile uint32_t * fpga_addr = NULL;
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
int fpga_initialize() {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        perror("Error opening /dev/mem");
        return -1;
    }

    fpga_addr = mmap(NULL, FPGA_REG * sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd,
                     FPGA_BASE_ADDRESS);
    if (fpga_addr == MAP_FAILED) {
        perror("Error mapping FPGA register");
        close(fd);
        return -1;
    }

    return 0;
}

void fpga_finalize() {
    if (fpga_addr != NULL) {
        munmap((void *)fpga_addr, FPGA_REG * sizeof(uint32_t));
        fpga_addr = NULL;
    }
}

void fpga_write_registers(uint32_t prf, uint32_t bw, uint32_t freq) {
    if (fpga_addr == NULL) {
        printf("FPGA driver not initialized.\n");
        return;
    }

    uint32_t prt_value   = ceil(122880000 / prf);
    uint32_t t_value     = ceil((16 * 122880000) / bw);
    uint32_t phase_value = ceil((freq * 1e9) / 28610229);

    *(fpga_addr + FPGA_OFFSET_START) = 0;
    *(fpga_addr + FPGA_OFFSET_CODE)  = CODE_BARKER11;
    *(fpga_addr + FPGA_OFFSET_PRT)   = prt_value;
    *(fpga_addr + FPGA_OFFSET_T)     = t_value;
    *(fpga_addr + FPGA_OFFSET_PHASE) = phase_value;
    *(fpga_addr + FPGA_OFFSET_START) = 1;
}

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
