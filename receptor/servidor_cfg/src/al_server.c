/* Copyright 2024, Adan Lema <adanlema@hotmail.com> & Carcamo Mariano <mgcarcamo98@gmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "al_server.h"
#include "log_manager.h"

/*==================[macros and definitions]=================================*/
#define IP_SIZE 20
/*==================[internal data declaration]==============================*/
struct server_s {
    char               ip[IP_SIZE];
    int                sock;
    uint32_t           port;
    struct sockaddr_in addr;
    struct sockaddr_in client;
    int                client_sock;
};
/*==================[internal functions declaration]=========================*/
static int serverCreateSocket();
/*==================[internal data definition]===============================*/
char                   log_buff[256];
static struct server_s servidor = {0};
/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static int serverCreateSocket() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        log_add("[ERROR]Error al crear el socket.");
        return -1;
    }
    log_add("[SUCCESS]TCP socket server creado con exito");
    return sock;
}
/*==================[external functions definition]==========================*/
server_t serverCreate(uint32_t port, char * ip) {
    server_t AL = &servidor;
    AL->sock    = serverCreateSocket();
    if (AL->sock == -1) {
        return NULL;
    }

    AL->port = port;
    strcpy(AL->ip, ip);
    memset(&AL->addr, '\0', sizeof(AL->addr));
    AL->addr.sin_family      = AF_INET;
    AL->addr.sin_port        = htons(port);
    AL->addr.sin_addr.s_addr = inet_addr(ip);
    return AL;
}

int serverConnect(server_t server) {
    server->sock = serverCreateSocket();
    if (server->sock < 0) {
        return -1;
    }

    if (bind(server->sock, (struct sockaddr *)&server->addr, sizeof(server->addr)) != 0) {
        log_add("[ERROR]Error de vinculacion (Bind error)");
        return -1;
    }
    log_add("[SUCCESS]Servidor creado con exito");
    sprintf(log_buff, "[+]IP: %s", server->ip);
    log_add(log_buff);
    sprintf(log_buff, "[+]Vinculado al puerto numero: %u", server->port);
    log_add(log_buff);
    return 0;
}
void serverDisconnect(server_t server) {
    close(server->sock);
    server->sock = -1;
    log_add("[SUCCESS]Servidor desconectado...");
}

int serverAccept(server_t server) {
    int n               = sizeof(server->client);
    server->client_sock = accept(server->sock, (struct sockaddr *)&server->client, &n);
    if (server->client_sock < 0) {
        log_add("[ERROR]Error al conectar el cliente.");
        return -1;
    }
    return 0;
}
void serverCloseClient(server_t server) {
    close(server->client_sock);
    server->client_sock = -1;
}

int serverListen(server_t server, int n) {
    return listen(server->sock, n);
}

void serverSend(server_t server, char * buffer, uint32_t size) {
    send(server->client_sock, buffer, size, 0);
}

int serverRecive(server_t server, char * buffer, uint32_t size) {
    return recv(server->client_sock, buffer, size, 0);
}

void serverGetIP(server_t server, char * destino) {
    if (destino == NULL) {
        printf("Error: buffer destino no es válido...\n");
        return;
    }
    strcpy(destino, server->ip);
}

int serverGetPort(server_t server) {
    return server->port;
}

int serverGetSock(server_t server) {
    return server->sock;
}

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
