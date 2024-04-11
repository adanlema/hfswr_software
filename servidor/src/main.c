/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>

#include "al_server.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
volatile sig_atomic_t server_running = 1;
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
void handle_sigint(int sig) { // Interrupcion para SIGINT
    server_running = 0;
}

int main() {
    int                server_sock, client_sock;
    struct sockaddr_in client_addr;
    socklen_t          addr_size;

    signal(SIGINT, handle_sigint);
    // Creacion del server...
    server_sock = server_initialize();
    if (server_sock < 0) {
        printf("Error al inicializar el cliente...\n");
        return -1;
    }
    listen(server_sock, 5);
    printf("Listening...\n");

    // Creacion del buffer...
    uint32_t * buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        perror("Error allocating memory for buffer");
        return -1;
    }
    while (server_running) {
        addr_size   = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
        if (client_sock < 0) {
            perror("[-]Error al conectar el cliente:");
            continue; // Continuar esperando nuevas conexiones
        } else
            printf("[+]Cliente conectado.\n");

        while (1) {
            memset(buffer, 0, BUFFER_SIZE);
            ssize_t recv_result = recv(client_sock, buffer, BUFFER_SIZE, 0);
            if (recv_result <= 0) { // Se perdio la conexion con el cliente
                printf("[-]Cliente desconectado...\n");
                break;
            }
            printf("Datos obtenidos:\n%ls\n", buffer);
        }
        close(client_sock);
    }
    free(buffer);
    server_disconnect(server_sock);
    return 0;
}

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
