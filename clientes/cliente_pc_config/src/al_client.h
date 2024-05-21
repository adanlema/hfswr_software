/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

#ifndef AL_CLIENT_H
#define AL_CLIENT_H

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
/*==================[macros]=================================================*/
#define IP_LOCAL "127.0.0.1"

#define PORT_TX  5566
#define PORT_RX1 2011
#define PORT_RX2 2027
#define PORT_RX3 2039
#define PORT_RX4 2063
#define PORT_RX5 2081
#define PORT_RX6 2087
#define PORT_RX7 2099

#define BUFTCP_SIZE 1024
#define IP_SIZE     20
/*==================[typedef]================================================*/
typedef struct client_s * client_t;
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
client_t clientCreate(uint32_t port, char * ip);
int      clientConnect(client_t client);
void     clientDisconnect(client_t client);
void     clientSend(client_t client, char * buffer, uint32_t size);
void     clientRecive(client_t client, char * buffer, uint32_t size);
void     clientGetIP(client_t client, char * destino);
int      clientGetPort(client_t client);
int      clientGetSock(client_t client);
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif
