/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

#ifndef AL_SERVER_H
#define AL_SERVER_H

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
typedef struct server_s * server_t;
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
server_t serverCreate(uint32_t port, char * ip);
int      serverConnect(server_t server);
void     serverDisconnect(server_t server);
int      serverAccept(server_t server);
void     serverCloseClient(server_t server);
int      serverListen(server_t server, int n);
void     serverSend(server_t server, char * buffer, uint32_t size);
int      serverRecive(server_t server, char * buffer, uint32_t size);
void     serverGetIP(server_t server, char * destino);
int      serverGetPort(server_t server);
int      serverGetSock(server_t server);

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif
