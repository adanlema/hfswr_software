/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
/*==================[macros and definitions]=================================*/
#define FPGA_BASE_ADDRESS 0x40000000
#define FPGA_REG_SIZE     0x1000
#define MOD_FREQ          0
#define MOD_CODE          1
#define MOD_PRF           2
#define MOD_BW            3

struct fpga_registers_s {
    volatile uint32_t freq;
    volatile uint32_t code;
    volatile uint32_t prf;
    volatile uint32_t bw;
};
typedef struct fpga_registers_s * fpga_registers_t;
/*==================[internal data declaration]==============================*/
static struct fpga_registers_s fpga_regs = {0};
/*==================[internal functions declaration]=========================*/
static int  fpga_init(fpga_registers_t * self);
static void fpga_exit();
static void fpga_write(fpga_registers_t self, uint32_t estado, uint32_t valor);
/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
fpga_registers_t fpga_Create(void) {
    return &fpga_regs;
}

static int fpga_init(fpga_registers_t * self) {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        perror("Error opening /dev/mem");
        return -1;
    }

    *self = (fpga_registers_t)mmap(NULL, FPGA_REG_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd,
                                   FPGA_BASE_ADDRESS);
    if (*self == MAP_FAILED) {
        perror("Error mapping FPGA registers");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}

static void fpga_write(fpga_registers_t self, uint32_t estado, uint32_t valor) {
    if (self != NULL) {
        volatile uint32_t * registro;
        switch (estado) {
            case MOD_FREQ:
                registro = &self->freq;
                break;
            case MOD_CODE:
                registro = &self->code;
                break;
            case MOD_PRF:
                registro = &self->prf;
                break;
            case MOD_BW:
                registro = &self->bw;
                break;
            default:
                return;
        }
        *registro = valor;
    }
}

static void fpga_exit() {
    munmap((void *)fpga_regs, FPGA_REG_SIZE);
}

/*==================[external functions definition]==========================*/

int main() {
    fpga_registers_t fpga = fpga_Create();
    uint32_t         freq_rp, freq_s, codigo, ancho_b;
    char             respuesta;
    if (fpga_init(&fpga) == 0) {
        printf("Bienvenido al programa de modificación de señal en la FPGA.\n");
        printf("Frecuencia = %u[Hz]\nCodigo = %u\nPRF = %u[Hz]\nBW = %u[Hz]\n", fpga->freq,
               fpga->code, fpga->prf, fpga->bw);

        // ======================= FRECUENCIA ============================
        printf("¿Deseas modificar la frecuencia? (S/N): ");
        scanf(" %c", &respuesta);
        if (respuesta == 'S' || respuesta == 's') {
            printf("Introduce el valor de la frecuencia: ");
            scanf("%u", &freq_s);
            fpga_write(fpga, MOD_FREQ, freq_s);
        }
        // ======================= CODIGO ============================
        printf("¿Deseas modificar el código? (S/N): ");
        scanf(" %c", &respuesta);
        if (respuesta == 'S' || respuesta == 's') {
            printf("Introduce el valor del código: ");
            scanf("%u", &codigo);
            fpga_write(fpga, MOD_CODE, codigo);
        }

        // ======================= PRF ============================
        printf("¿Deseas modificar la PRF? (S/N): ");
        scanf(" %c", &respuesta);
        if (respuesta == 'S' || respuesta == 's') {
            printf("Introduce el valor de la PRF: ");
            scanf("%u", &freq_rp);
            fpga_write(fpga, MOD_PRF, freq_rp);
        }

        // ======================= ANCHO DE BANDA ============================
        printf("¿Deseas modificar el ancho de banda? (S/N): ");
        scanf(" %c", &respuesta);
        if (respuesta == 'S' || respuesta == 's') {
            printf("Introduce el valor del ancho de banda: ");
            scanf("%u", &ancho_b);
            fpga_write(fpga, MOD_BW, ancho_b);
        }

        fpga_exit();
    }

    return 0;
}

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/