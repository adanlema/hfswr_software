/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "al_server.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

int main() {
    int                server_sock, client_sock;
    struct sockaddr_in client_addr;
    socklen_t          addr_size;

    // Creacion del buffer...
    int32_t * buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        perror("Error allocating memory for buffer");
        return -1;
    }
    // Creacion del server...
    server_sock = server_initialize();
    if (server_sock < 0) {
        printf("Error al inicializar el cliente...\n");
        return -1;
    }
    listen(server_sock, 5);
    printf("Listening...\n");

    // Conexion con el cliente..-
    addr_size   = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
    if (client_sock < 0) {
        perror("\n[-]Error al conectar el cliente:");
        return -1;
    }
    printf("[+]Cliente conectado.\n");

    char palabra[100] = 0;
    int  bandera      = 0;
    int  i            = 0;
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t recv_result = recv(client_sock, buffer, BUFFER_SIZE, 0);
        if (recv_result <= 0) { // Se perdio la conexion con el cliente
            printf("[-]Cliente desconectado...\n");
            break;
        }
        // Creacion del archivo .txt
        sprintf(palabra, "../data%d.txt", bandera);
        bandera++;
        FILE * txt = fopen(palabra, "w");
        fputs("Datos obtenidos:\n", txt);
        i = 0;
        for (int32_t * p = buffer; p < (buffer + (FPGA_REG / 4)); ++p) {
            memset(palabra, 0, sizeof(palabra));
            sprintf(palabra, "%d , %d\n", i, *p);
            i++;
            fputs(palabra, txt);
        }
        fclose(txt);
    }
    close(client_sock);

    free(buffer);
    server_disconnect(server_sock);
    return 0;
}

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
