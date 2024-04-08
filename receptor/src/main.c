/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
/*==================[macros and definitions]=================================*/
#define FPGA_BASE_ADDRESS 0x43C00000
#define FPGA_REG          7

/*==================[internal data declaration]==============================*/
static volatile uint32_t * fpga_addr = NULL;
/*==================[internal functions declaration]=========================*/
static int  fpga_initialize();
static void fpga_finalize();
static void save_memory(const char * filename);
/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static int fpga_initialize() {
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
static void fpga_finalize() {
    if (fpga_addr != NULL) {
        munmap(fpga_addr, FPGA_REG * sizeof(uint32_t));
        fpga_addr = NULL;
    }
}
static void save_memory(const char * filename) {
    FILE * fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    fprintf(fp, "FS = 120000\n");
    for (int i = 0; i < FPGA_REG; ++i) {
        uint32_t value = *((uint32_t *)fpga_addr + i);
        fprintf(fp, "0x%08x\n", value);
    }

    fclose(fp);
}
/*==================[external functions definition]==========================*/
int main() {
    if (fpga_initialize() != 0) {
        fprintf(stderr, "Error al inicializar el bloque de memoria de la FPGA\n");
        return 1;
    }
    printf("Bienvenido al programa de extracion de datos en la FPGA.\n");
    save_memory("datos_recuperados.txt");
    fpga_finalize();
    printf("Datos extraidos correctamente!.\n");

    return 0;
}
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/