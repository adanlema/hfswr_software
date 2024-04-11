/* Copyright 2023, Adan Lema <adanlema@hotmail.com> */

#ifndef AL_CLIENT_H
#define AL_CLIENT_H

/*==================[inclusions]=============================================*/
#include <stdio.h>
/*==================[macros]=================================================*/
#define PORT       5566
#define IP_ADDRESS "10.0.255.126"
/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
int  client_create_socket();
int  client_connect(int sock);
void client_disconnect(int sock);

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif
