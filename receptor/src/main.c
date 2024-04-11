/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "al_client.h"
#include "al_mapping.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
int main() {

    volatile uint32_t * addr_fpga = mapping_initialize();
    printf("Mapeo de memoria realizo con exito...\n");

    int sock = client_create_socket();
    if (sock < 0) {
        printf("Error al inicializar el cliente...\n");
        return -1;
    }

    int32_t * buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        perror("Error allocating memory for buffer");
        return -1;
    }

    while (1) {
        if (addr_fpga[FPGA_OFFSET_VALID] == 1) {
            if (client_connect(sock) == 0) {
                memset(buffer, 0, BUFFER_SIZE);
                memcpy(buffer, (const void *)addr_fpga, BUFFER_SIZE);
                send(sock, buffer, BUFFER_SIZE, 0);
                printf("\nDatos enviados...\n");
                addr_fpga[FPGA_OFFSET_VALID] = 0;
                client_disconnect(sock);
            }
        }
    };
    free(buffer);
    mapping_finalize(addr_fpga);
    return 0;
}
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/