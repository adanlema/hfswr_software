/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

// #include "xil_types.h"
// #include "xstatus.h"
// #include "xsysmon.h"
// #include "xparameters.h"
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

    printf("Bienvenido al programa de modificación de señal en la FPGA.\n");
    // ===================================
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        perror("Error opening /dev/mem");
        return -1;
    }

    volatile uint32_t * fpga_addr =
        mmap(NULL, sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, FPGA_BASE_ADDRESS);
    if (fpga_addr == MAP_FAILED) {
        perror("Error mapping FPGA register");
        close(fd);
        return -1;
    }
    uint32_t codigo = 1000;
    *fpga_addr      = CODE_BARKER11;

    munmap((void *)fpga_addr, sizeof(uint32_t));
    close(fd);
    // ====================================
    // Xil_Out32(FPGA_BASE_ADDRESS + FPGA_OFFSET_CODE, CODE_BARKER11);
    printf("Codigo actualizado\n");
    return 0;
}
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
