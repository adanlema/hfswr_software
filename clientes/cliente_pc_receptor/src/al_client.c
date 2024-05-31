/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "al_client.h"

/*==================[macros and definitions]=================================*/
#define CANTIDAD_CLIENTES 10
#define IP_SIZE           20
/*==================[internal data declaration]==============================*/
struct client_s {
    char               ip[IP_SIZE];
    bool               ocupado;
    int                sock;
    uint32_t           port;
    struct sockaddr_in addr;
};
/*==================[internal functions declaration]=========================*/
static int clientCreateSocket();
/*==================[internal data definition]===============================*/
static struct client_s cliente[CANTIDAD_CLIENTES] = {0};
/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static int clientCreateSocket() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("[-]Socket error:");
        return -1;
    }
    return sock;
}
/*==================[external functions definition]==========================*/
client_t clientCreate(uint32_t port, char * ip) {
    uint8_t posicion = 0;
    int     i;
    for (i = 0; (i < CANTIDAD_CLIENTES) && (posicion == 0); i++) {
        if (cliente[i].ocupado == false) {
            posicion = i;
            break;
        }
    }
    if (posicion == 0 && i == CANTIDAD_CLIENTES) {
        printf("No hay espacio disponible para más clientes.\n");
        return NULL;
    }

    client_t AL = &cliente[posicion];
    AL->sock    = clientCreateSocket();
    AL->port    = port;
    AL->ocupado = true;
    strcpy(AL->ip, ip);

    memset(&AL->addr, '\0', sizeof(AL->addr));
    AL->addr.sin_family      = AF_INET;
    AL->addr.sin_port        = htons(port);
    AL->addr.sin_addr.s_addr = inet_addr(ip);
    return AL;
}

int clientConnect(client_t client) {
    client->sock = clientCreateSocket();
    if (client->sock < 0) {
        return -1;
    }
    if (connect(client->sock, (struct sockaddr *)&client->addr, sizeof(client->addr)) != 0) {
        perror("Error al conectar el cliente con el servidor");
        return -1;
    }
    return 0;
}

void clientDisconnect(client_t client) {
    close(client->sock);
    client->sock = -1;
    printf("Desconexion del cliente del server...\n");
}

int clientGetSock(client_t client) {
    return client->sock;
}

void clientGetIP(client_t client, char * destino) {
    if (destino == NULL) {
        printf("Error: buffer destino no es válido...\n");
        return;
    }
    strcpy(destino, client->ip);
}

int clientGetPort(client_t client) {
    return client->port;
}

int clientRecive(client_t client, char * buffer, uint32_t size) {
    memset(buffer, 0, size);
    return recv(client->sock, buffer, size, 0);
}
void clientSend(client_t client, char * buffer, uint32_t size) {
    send(client->sock, buffer, size, 0);
}
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/