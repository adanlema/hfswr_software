/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
/*==================[macros and definitions]=================================*/
#define CODE_BARKER7  0x72
#define CODE_BARKER11 0x0712
#define CODE_BARKER13 0x1F35
/* DIRECCIONES DE MEMORIA*/
#define FPGA_BASE_ADDRESS 0x43C00000
#define FPGA_OFFSET_CODE  0
#define FPGA_OFFSET_PRT   4
#define FPGA_OFFSET_T     8
#define FPGA_OFFSET_PHASE 12
#define FPGA_OFFSET_START 16
#define FPGA_REG          5
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

    volatile uint32_t * fpga_addr = mmap(NULL, FPGA_REG * sizeof(uint32_t), PROT_READ | PROT_WRITE,
                                         MAP_SHARED, fd, FPGA_BASE_ADDRESS);
    if (fpga_addr == MAP_FAILED) {
        perror("Error mapping FPGA register");
        close(fd);
        return -1;
    }
    /* Variables a editar */
    uint32_t PRF  = 50;
    uint32_t AB   = 5000;
    uint32_t FREQ = 10000000;

    /* Calculos necesarios */
    uint32_t prt, t, phase;
    prt   = ceil(122880000 / PRF);
    t     = ceil((16 * 122880000) / AB);
    phase = ceil((FREQ * 1e9) / 28610229);

    /* Asignacion en la memoria */
    *(fpga_addr + FPGA_OFFSET_START) = 0;
    *(fpga_addr + FPGA_OFFSET_CODE)  = CODE_BARKER11;
    *(fpga_addr + FPGA_OFFSET_PRT)   = prt;
    *(fpga_addr + FPGA_OFFSET_T)     = t;
    *(fpga_addr + FPGA_OFFSET_PHASE) = phase;
    *(fpga_addr + FPGA_OFFSET_START) = 1;

    /* Salir */
    munmap((void *)fpga_addr, FPGA_REG * sizeof(uint32_t));
    close(fd);
    // ====================================
    printf("Parametros Actualizados\n");
    return 0;
}
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/