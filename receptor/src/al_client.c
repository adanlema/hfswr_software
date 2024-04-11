/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include "al_client.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
static struct sockaddr_in addr;
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
int client_create_socket() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("[-]Socket error:");
        return -1;
    }
    printf("[+]TCP server socket created.\n");
    memset(&addr, '\0', sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_port        = PORT;
    addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    return sock;
}
int client_connect(int sock) {
    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
        perror("Error al conectar el cliente con el servidor: ");
        return -1;
    } else {
        printf("Cliente conectado con exito...\n");
        return 0;
    }
}

void client_disconnect(int sock) {
    close(sock);
    printf("Desconexion del cliente del server...\n");
}

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/