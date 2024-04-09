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

/*==================[internal functions declaration]=========================*/
static int client_create_socket();
static int client_connect(int sock);
/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static int client_create_socket() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("[-]Socket error:");
        return -1;
    }
    printf("[+]TCP server socket created.\n");
    return sock;
}
static int client_connect(int sock) {
    struct sockaddr_in addr;
    memset(&addr, '\0', sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_port        = PORT;
    addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);

    // Intenta conectarse al server
    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
        perror("Error al conectar el cliente con el servidor: ");
        return -1;
    } else {
        printf("Cliente conectado con exito...\n");
        return 0;
    }
}
/*==================[external functions definition]==========================*/
int client_initialize() {
    int sock = client_create_socket();
    int value;
    if (sock > 0) {
        value = client_connect(sock);
        if (value != 0) {
            return -1;
        }
    } else {
        return -1;
    }
    return sock;
}

void client_disconnect(int sock) {
    close(sock);
    printf("Desconexion del cliente del server...\n");
}

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/