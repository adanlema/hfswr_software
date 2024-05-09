/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

#ifndef AL_SERVER_H
#define AL_SERVER_H

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
/*==================[macros]=================================================*/
#define PORT_TX     5566
#define IP_TX       "10.0.255.126"
#define BUFTCP_SIZE 1024
/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
int  serverInit();
void serverClientManagement(int confd, params_t params, addrs_t addr_fpga);

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif
