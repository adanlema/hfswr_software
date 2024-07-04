/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "al_mapping.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
int main() {

    volatile uint32_t * addr = mapping_initialize();
    printf("\n\nMapeo de memoria realizo con exito...\n");
    printf("Direccion de memoria Base = %p\n\nValores Escritos:\n", addr);

    int i = 0;
    for (volatile uint32_t * p = addr; p < (addr + 10); ++p) {
        *p = 0x55555555UL;
        printf("Posicion %i - Direccion = %p - Valor = %u\n", i, p, *p);
        i++;
    }

    printf("\n\n ==> VALORES MODIFICADOS <==\n\n");
    addr[0] = 0;
    addr[2] = 0;
    addr[4] = 0;
    addr[6] = 0;
    addr[8] = 0;

    printf("\n\n Valores Leidos:\n");
    i = 0;

    for (volatile uint32_t * p = addr; p < (addr + 10); ++p) {
        printf("Posicion %i - Direccion = %p - Valor = %u\n", i, p, *p);
        i++;
    }

    printf("\nSaliendo del bloque de memoria...\n\n");
    mapping_finalize(addr);
    return 0;
}
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/