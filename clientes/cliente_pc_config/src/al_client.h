/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

#ifndef AL_CLIENT_H
#define AL_CLIENT_H

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
/*==================[macros]=================================================*/
#define PORT_TX  5566
#define PORT_RX1 2000
#define IP_TX    "10.0.255.71"
#define IP_RX1   "10.0.255.0"

#define BUFTCP_SIZE 1024
/*==================[typedef]================================================*/
typedef struct client_s * client_t;
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
client_t clientCreate(uint32_t port, char * ip);
int      clientConnect(client_t client);
void     clientDisconnect(client_t client);
void     clientSend(client_t client, char * buffer, uint32_t size);
void     clientRecive(client_t client, char * buffer, uint32_t size);
int      clientGetPort(client_t client);
int      clientGetSock(client_t client);
char *   clientGetIP(client_t client);
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif
