/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

#ifndef AL_CLIENT_H
#define AL_CLIENT_H

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
/*==================[macros]=================================================*/
#define PORT_TX 5566
#define IP_TX   "10.0.255.126"
#define PORT_RX 2000
#define IP_RX   "10.0.0.0"

#define BUFTCP_SIZE 1024

/*==================[typedef]================================================*/
typedef struct client_s {
    char               ip[20];
    uint32_t           port;
    int                sock;
    struct sockaddr_in addr;
} * client_t;
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
client_t clientCreate(uint32_t port, char * ip);
int      clientConnect(client_t client);
void     clientDisconnect(client_t client);
void     clientRemove(client_t client);
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif
