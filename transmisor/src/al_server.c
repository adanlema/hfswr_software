/* Copyright 2024, Adan Lema <adanlema@hotmail.com> & Carcamo Mariano <mgcarcamo98@gmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <math.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <json-c/json.h>

#include "al_server.h"
#include "al_mapping.h"
#include "al_params.h"
#include "log_manager.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
char log_buff[256];
/*==================[internal functions declaration]=========================*/
static int serverCreateSocket();
static int serverConnect(int sock);
/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static int serverCreateSocket() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        log_add("[ERROR]Error al crear el socket.");
        return -1;
    }
    log_add("[SUCCESS]TCP socket creado con exito");
    return sock;
}
static int serverConnect(int sock) {
    struct sockaddr_in server;
    memset(&server, '\0', sizeof(server));
    server.sin_family      = AF_INET;
    server.sin_port        = htons(PORT_TX);
    server.sin_addr.s_addr = inet_addr(IP_TX);

    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        log_add("[ERROR]Error de vinculacion (Bind error)");
        return -1;
    }
    log_add("[SUCCESS]Servidor creado con exito");
    sprintf(log_buff, "[+]IP: %s", IP_TX);
    log_add(log_buff);
    sprintf(log_buff, "[+]Vinculado al puerto numero: %d", PORT_TX);
    log_add(log_buff);
    return 0;
}

/*==================[external functions definition]==========================*/
int serverInit() {
    int sock = serverCreateSocket();
    if (sock == -1) {
        return -1;
    }
    if (serverConnect(sock) != 0) {
        return -1;
    }
    return sock;
}

void serverClientManagement(int confd, params_t params, addrs_t addr_fpga) {
    // void serverClientManagement(int confd, params_s * params) {
    char *r_buff, *s_buff;

    r_buff = malloc(BUFTCP_SIZE);
    s_buff = malloc(BUFTCP_SIZE);

    if (r_buff == NULL || s_buff == NULL) {
        log_add("[ERROR]Error al reservar memoria.");
        exit(EXIT_FAILURE);
    }

    memset(r_buff, 0, BUFTCP_SIZE);
    memset(s_buff, 0, BUFTCP_SIZE);

    sprintf(s_buff, "{\"info\":\"Configuracion actual\"}\n");
    send(confd, s_buff, BUFTCP_SIZE, 0);

    memset(s_buff, 0, BUFTCP_SIZE);
    sprintf(s_buff,
            "{\"prf\":%d, \"freq\":%d, \"ab\":%d, \"code\":%d, \"code-num\":%d, \"start\":%s}\n",
            params->prf, params->freq, params->ab, params->code, params->code_num,
            params->start ? "true" : "false");
    send(confd, s_buff, BUFTCP_SIZE, 0);

    while (1) {
        if (!(recv(confd, r_buff, BUFTCP_SIZE, 0) == 0)) {
            if (paramsStrtoJson(r_buff, params) == -1) {
                memset(s_buff, 0, BUFTCP_SIZE);
                strcpy(s_buff, "{\"error\":\"Formato JSON no identificado\"}\n");
                send(confd, s_buff, BUFTCP_SIZE, 0);
            } else {
                paramsSetConfig(addr_fpga, params);
                paramsSaveConfig(params);
                memset(s_buff, 0, BUFTCP_SIZE);
                strcpy(s_buff, "{\"info\":\"Configuracion cargada con exito\"}\n");
                send(confd, s_buff, BUFTCP_SIZE, 0);
            }
            memset(s_buff, 0, BUFTCP_SIZE);
            sprintf(s_buff,
                    "{\"prf\":%d, \"freq\":%d, \"ab\":%d, \"code\":%d, \"code-num\":%d, "
                    "\"start\":%s}\n",
                    params->prf, params->freq, params->ab, params->code, params->code_num,
                    params->start ? "true" : "false");
            send(confd, s_buff, BUFTCP_SIZE, 0);

        } else {
            break;
        }
    }

    free(r_buff);
    free(s_buff);
}

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
