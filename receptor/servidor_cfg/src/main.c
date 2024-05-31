/* Copyright 2024, Adan Lema <adanlema@hotmail.com> & Carcamo Mariano <mgcarcamo98@gmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <signal.h>

#include "al_mapping.h"
#include "al_server.h"
#include "al_params.h"
#include "log_manager.h"
/*==================[macros and definitions]=================================*/
#define EXT_ERR_CREATE_SERVER  1
#define EXT_ERR_CLIENT_CONNECT 2
#define EXT_ERR_LISTENING_SOCK 3

#define PORT_SERVER 2027
#define IP_SERVER   "0.0.0.0"
#define BUFTCP_SIZE 1024

#define FPGA_CTRL 0x40008000
#define FPGA_REG  10
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
static void MySignalHandler(int sig);
static void dataManagement(server_t sv, params_t params, addrs_t addr_fpga);
/*==================[internal data definition]===============================*/
addrs_t  addr_fpga = NULL;
server_t server    = NULL;
/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static void dataManagement(server_t sv, params_t params, addrs_t addr) {
    char *r_buff, *s_buff;
    r_buff = malloc(BUFTCP_SIZE);
    s_buff = malloc(BUFTCP_SIZE);
    if (r_buff == NULL || s_buff == NULL) {
        log_add("[ERROR]Error al reservar memoria.");
        exit(EXIT_FAILURE);
    }
    memset(r_buff, 0, BUFTCP_SIZE);
    memset(s_buff, 0, BUFTCP_SIZE);

    sprintf(s_buff, "{\"info\":\"Configuracion actual\"}");
    serverSend(sv, s_buff, BUFTCP_SIZE);
    memset(s_buff, 0, BUFTCP_SIZE);
    sprintf(s_buff, "{\"freq\":%d, \"start\":%s}\n", params->freq,
            params->start ? "true" : "false");
    serverSend(sv, s_buff, BUFTCP_SIZE);

    while (1) {
        memset(r_buff, 0, BUFTCP_SIZE);
        if (!(serverRecive(server, r_buff, BUFTCP_SIZE) == 0)) {
            if (paramsStrtoJson(r_buff, params) == -1) {
                memset(s_buff, 0, BUFTCP_SIZE);
                strcpy(s_buff, "{\"error\":\"Formato JSON no identificado\"}\n");
                serverSend(server, s_buff, BUFTCP_SIZE);
            } else {
                paramsSetConfig(addr, params);
                paramsSaveConfig(params);
                memset(s_buff, 0, BUFTCP_SIZE);
                strcpy(s_buff, "{\"info\":\"Configuracion cargada con exito\"}");
                serverSend(server, s_buff, BUFTCP_SIZE);
            }
            memset(s_buff, 0, BUFTCP_SIZE);
            sprintf(s_buff, "{\"freq\":%d, \"start\":%s}\n", params->freq,
                    params->start ? "true" : "false");
            serverSend(server, s_buff, BUFTCP_SIZE);
        } else {
            break;
        }
    }
    free(r_buff);
    free(s_buff);
}

static void MySignalHandler(int sig) {
    log_add("[-]Cerrando el programa");
    mappingFinalize(addr_fpga);
    serverCloseClient(server);
    serverDisconnect(server);
    log_add("[SUCCESS]Programa cerrado con exito");
    exit(EXIT_SUCCESS);
}

/*==================[external functions definition]==========================*/
int main() {
    log_delete();

    // Mapeo de memoria...
    addr_fpga = mappingInit(FPGA_CTRL, FPGA_REG);
    if (addr_fpga == NULL) {
        return -1;
    }
    params_t params = paramsCreate();
    paramsSetConfig(addr_fpga, params);

    // Creacion del server...
    server = serverCreate(PORT_SERVER, IP_SERVER);
    if (server == NULL) {
        log_add("[ERROR]Error al crear el server...");
        exit(EXT_ERR_CREATE_SERVER);
    }
    if (serverConnect(server) != 0) {
        log_add("[ERROR]Error al conectar el server...");
        exit(EXT_ERR_CREATE_SERVER);
    }
    if (serverListen(server, 2) == -1) {
        log_add("[ERROR]Error al poner en escucha el socket.");
        exit(EXT_ERR_LISTENING_SOCK);
    }

    // Manejo de señales de linux...
    signal(SIGABRT, MySignalHandler);
    signal(SIGINT, MySignalHandler);
    signal(SIGTERM, MySignalHandler);
    signal(SIGKILL, MySignalHandler);

    while (1) {
        if (serverAccept(server) != 0) {
            continue;
        }
        dataManagement(server, params, addr_fpga);
        serverCloseClient(server);
    }

    mappingFinalize(addr_fpga);
    serverDisconnect(server);
    return 0;
}

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/