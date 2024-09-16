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
#include "fpga_redpitaya.h"
/*==================[macros and definitions]=================================*/
#define EXT_ERR_CREATE_SERVER  1
#define EXT_ERR_CLIENT_CONNECT 2
#define EXT_ERR_LISTENING_SOCK 3

#define ID          "tx_rpf089d4"
#define PORT_SERVER 2003
#define IP_SERVER   "0.0.0.0"
#define BUFTCP_SIZE 1024
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
void        MySignalHandler(int sig);
static void setConfigTx(fpgatx_t mem, params_t config);

// static void dataManagement(server_t sv, params_t params, fpgatx_t addrtx);
static void dataManagement(server_t sv, params_t params);
/*==================[internal data definition]===============================*/
static server_t server = NULL;
static fpgatx_t fpgatx = NULL;
/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static void setConfigTx(fpgatx_t mem, params_t config) {
    uint32_t prt_value   = ceil(122880000 / config->prf);
    uint32_t phase_value = ceil((config->freq * 1e9) / 28610229);
    uint32_t tb          = ceil(122880000 / config->ab);
    uint32_t t_value     = ceil(config->code_num * tb);

    mem->start  = 0;
    mem->phase  = phase_value;
    mem->period = t_value;
    mem->prt    = prt_value;
    mem->code   = config->code;
    mem->numdig = config->code_num;
    mem->tb     = tb;
    mem->start  = config->start;
}
static void dataManagement(server_t sv, params_t params) {
// static void dataManagement(server_t sv, params_t params, fpgatx_t addrtx) {
    char *r_buff, *s_buff;
    r_buff = malloc(BUFTCP_SIZE);
    s_buff = malloc(BUFTCP_SIZE);
    if (r_buff == NULL || s_buff == NULL) {
        log_add("[ERROR]Error al reservar memoria.");
        exit(EXIT_FAILURE);
    }
    memset(r_buff, 0, BUFTCP_SIZE);
    memset(s_buff, 0, BUFTCP_SIZE);

    sprintf(s_buff, "{\"%s\"}", ID);
    serverSend(sv, s_buff, BUFTCP_SIZE);
    memset(s_buff, 0, BUFTCP_SIZE);
    sprintf(s_buff,
            "{\"prf\":%d, \"freq\":%d, \"ab\":%d, \"code\":%d, \"code-num\":%d, \"start\":%s}\n",
            params->prf, params->freq, params->ab, params->code, params->code_num,
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
                // setConfigTx(addrtx, params);
                paramsSaveConfig(params);
                memset(s_buff, 0, BUFTCP_SIZE);
                strcpy(s_buff, "{\"info\":\"Configuracion cargada con exito\"}");
                serverSend(server, s_buff, BUFTCP_SIZE);

                memset(s_buff, 0, BUFTCP_SIZE);
                sprintf(s_buff,
                        "{\"prf\":%d, \"freq\":%d, \"ab\":%d, \"code\":%d, \"code-num\":%d, "
                        "\"start\":%s}\n",
                        params->prf, params->freq, params->ab, params->code, params->code_num,
                        params->start ? "true" : "false");
                serverSend(server, s_buff, BUFTCP_SIZE);
            }

        } else {
            break;
        }
    }
    free(r_buff);
    free(s_buff);
}

void MySignalHandler(int sig) {
    log_add("[-]Cerrando el programa");
    // mappingFinalize((addrs_t)fpgatx);
    serverCloseClient(server);
    serverDisconnect(server);
    log_add("[SUCCESS]Programa cerrado con exito");
    exit(EXIT_SUCCESS);
}
/*==================[external functions definition]==========================*/
int main() {
    log_delete();

    // Mapeo de memoria...
    // fpgatx = (fpgatx_t)mappingInit(FPGATX_ADDR, FPGATX_REGS);
    // if (fpgatx == NULL) {
    //     return -1;
    // }
    params_t params = paramsCreate();
    // setConfigTx(fpgatx, params);

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
        dataManagement(server, params);
        // dataManagement(server, params, fpgatx);
        serverCloseClient(server);
    }
    // mappingFinalize((addrs_t)fpgatx);
    serverDisconnect(server);
    return 0;
}

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/