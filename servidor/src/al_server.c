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
    struct sockaddr_in server_addr, client_addr;
    socklen_t          addr_size;
    char               buffer[BUFFER_SIZE];
    int                n;

    // Creacion del Socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+]TCP Socket Server creado con exito...\n");

    // Inicializa en cero y luego lo carga
    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = PORT;
    server_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);

    // Creacion del server
    n = bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (n < 0) {
        perror("[-]Bind error");
        exit(1);
    }
    printf("[+]Bind to the port number: %d\n", port);

    listen(server_sock, 5);
    printf("Listening...\n");
    addr_size   = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
    printf("[+]Cliente conectado.\n");

    while (1) {
        bzero(buffer, BUFFER_SIZE);
        recv(client_sock, buffer, sizeof(buffer), 0);
        printf("Client: %s\n", buffer);
    }
    close(client_sock);
    printf("[+]Cliente desconectado...\n");
    close(server_sock);
    printf("Server desconectado...\n");

    return 0;
}

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
