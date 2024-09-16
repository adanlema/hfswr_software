/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

#ifndef AL_CLIENT_H
#define AL_CLIENT_H

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
/*==================[macros]=================================================*/

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
