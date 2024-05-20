/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "al_client.h"

/*==================[macros and definitions]=================================*/
#define CANT_CLIENT 10
/*==================[internal data declaration]==============================*/
struct client_s {
    char               ip[20];
    uint32_t           port;
    int                sock;
    struct sockaddr_in addr;
};
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
static uint8_t         ocupacion_cl         = 0;
static struct client_s cliente[CANT_CLIENT] = {0};

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static int client_create_socket() {
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
    if (ocupacion_cl < CANT_CLIENT) {
        posicion = ocupacion_cl;
        ocupacion_cl++;
    } else {
        return NULL;
    }
    cliente[posicion].sock = client_create_socket();
    cliente[posicion].port = port;
    strcpy(cliente[posicion].ip, ip);

    memset(&cliente[posicion].addr, '\0', sizeof(cliente[posicion].addr));
    cliente[posicion].addr.sin_family      = AF_INET;
    cliente[posicion].addr.sin_port        = htons(port);
    cliente[posicion].addr.sin_addr.s_addr = inet_addr(ip);
    return &cliente[posicion];
}

int clientConnect(client_t client) {
    if (connect(client->sock, (struct sockaddr *)&client->addr, sizeof(client->addr)) != 0) {
        perror("Error al conectar el cliente con el servidor: ");
        return -1;
    }
    return 0;
}

void clientDisconnect(client_t client) {
    close(client->sock);
    printf("Desconexion del cliente del server...\n");
}

int clientGetSock(client_t client) {
    return client->sock;
}
char * clientGetIP(client_t client) {
    return client->ip;
}
int clientGetPort(client_t client) {
    return client->port;
}

void clientRecive(client_t client, char * buffer, uint32_t size) {
    memset(buffer, 0, size);
    recv(client->sock, buffer, size, 0);
    printf("\n[server] %s", buffer);
}
void clientSend(client_t client, char * buffer, uint32_t size) {
    send(client->sock, buffer, size, 0);
}
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/