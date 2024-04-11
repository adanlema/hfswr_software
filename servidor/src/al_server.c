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
static int server_create_socket();
static int server_connect(int sock);
/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static int server_create_socket() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("[-]Socket error:");
        return -1;
    }
    printf("[+]TCP server socket created.\n");
    return sock;
}
static int server_connect(int sock) {
    struct sockaddr_in addr;
    memset(&addr, '\0', sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_port        = PORT;
    addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);

    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("[-]Bind error");
        return -1;
    }
    printf("[+]Servidor creado con exito...\n[+]Bind to the port number: %d\n", PORT);
    return 0;
}

/*==================[external functions definition]==========================*/
int server_initialize() {
    int sock = server_create_socket();
    if (sock <= 0) {
        return -1;
    }
    if (server_connect(sock) != 0) {
        return -1;
    }
    return sock;
}

void server_disconnect(int sock) {
    close(sock);
    printf("Server desconectado...\n");
}
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
