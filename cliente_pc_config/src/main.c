/* Copyright 2024, Adan Lema <adanlema@hotmail.com> & Carcamo Mariano <mgcarcamo98@gmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <json-c/json.h>
#include <pthread.h>

#include "al_params.h"
#include "al_client.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
void * recive_msg(void * args) {
    thread_args_t arg    = args;
    char *        buff   = arg->r_buff;
    int           soc_d  = *(arg->soc);
    params_t      params = arg->params;

    while (1) {
        memset(buff, 0, BUFTCP_SIZE);
        recv(soc_d, buff, BUFTCP_SIZE, 0);
        paramsUpdate(buff, params);
        printf("\n[server] %s", buff);
    }
}

void * send_msg(void * args) {
    thread_args_t arg    = args;
    char *        buff   = arg->s_buff;
    params_t      params = arg->params;
    int           soc_d  = *(arg->soc);

    while (1) {
        memset(buff, 0, BUFTCP_SIZE);
        scanf("%s", buff);
        if (!strcmp(buff, "EXIT")) {
            break;
        }
        if (paramsStrtoJson(buff, params) == -1) {
            printf("\nERROR: Se requiere una estructura JSON para enviar los datos\n");
        } else {
            memset(buff, 0, BUFTCP_SIZE);
            sprintf(buff,
                    "{\"prf\":%d, \"freq\":%d, \"ab\":%d, \"code\":%d, \"code-num\":%d, "
                    "\"start\":%d}\n",
                    params->prf, params->freq, params->ab, params->code, params->code_num,
                    params->start);
            send(soc_d, buff, BUFTCP_SIZE, 0);
        }
    }
}
/*==================[external functions definition]==========================*/

int main() {
    int err;

    client_t client_tx = clientCreate(PORT_TX, IP_TX);
    if (clientConnect(client_tx) != 0) {
        printf("\nError al conectar el cliente...\n");
        return 1;
    }

    params_t      usr_params_p = paramsCreate();
    thread_args_t thread_tx    = threadCreate(clientGetDirSock(client_tx), usr_params_p);

    pthread_t thread_recv, thread_send;
    err = pthread_create(&thread_recv, NULL, recive_msg, thread_tx);
    if (err) {
        printf("An error occured: %d", err);
        return 1;
    }
    err = pthread_create(&thread_send, NULL, send_msg, thread_tx);
    if (err) {
        printf("An error occured: %d", err);
        return 1;
    }

    while (1) {
        if (!strcmp(thread_tx->s_buff, "EXIT")) {
            printf("Cerrando conexion...\n");
            clientDisconnect(client_tx);
            threadFinalize(thread_tx);
            pthread_cancel(thread_recv);
            pthread_cancel(thread_send);
            printf("Conexion cerrada con exito...\n");
            break;
        }
    }

    return 0;
}

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/