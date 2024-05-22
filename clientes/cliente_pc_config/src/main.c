/* Copyright 2024, Adan Lema <adanlema@hotmail.com> & Carcamo Mariano <mgcarcamo98@gmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "al_params.h"
#include "al_client.h"
/*==================[macros and definitions]=================================*/
#define RX_ON  1
#define RX_OFF 0

#define IP_LOCAL    "127.0.0.1"
#define BUFTCP_SIZE 1024

#define PORT_TX  2003
#define PORT_RX1 2011
#define PORT_RX2 2027
#define PORT_RX3 2039
#define PORT_RX4 2063
#define PORT_RX5 2081
#define PORT_RX6 2087
#define PORT_RX7 2099

/*==================[internal data declaration]==============================*/
static uint32_t freq_rx = {0};
static char     buffer[BUFTCP_SIZE];
/*==================[internal functions declaration]=========================*/
static void txConfig(client_t client, params_t params);
static void rxUpdate(client_t client);
static void rxOnOff(client_t client, uint32_t on_off);
/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static void txConfig(client_t client, params_t params) {
    memset(buffer, 0, BUFTCP_SIZE);
    if (clientConnect(client) != 0) {
        return;
    }
    printf("\n\n[+] Cliente conectado con exito...\n\
    [+] PORT: %u\n\
    [+] Escriba EXIT para salir\n\n",
           clientGetPort(client));

    clientRecive(client, buffer, BUFTCP_SIZE);
    clientRecive(client, buffer, BUFTCP_SIZE);
    paramsUpdate(buffer, params);

    while (1) {
        printf("[cliente] ");
        memset(buffer, 0, BUFTCP_SIZE);
        scanf("%s", buffer);
        if (!strcmp(buffer, "EXIT")) {
            break;
        }
        if (paramsStrtoJson(buffer, params) == -1) {
            printf("\nERROR: Se requiere una estructura JSON para enviar los datos\n");
        } else {
            memset(buffer, 0, BUFTCP_SIZE);
            sprintf(buffer,
                    "{\"prf\":%d, \"freq\":%d, \"ab\":%d, \"code\":%d, \"code-num\":%d, "
                    "\"start\":%d}\n",
                    params->prf, params->freq, params->ab, params->code, params->code_num,
                    params->start);
            clientSend(client, buffer, BUFTCP_SIZE);
            clientRecive(client, buffer, BUFTCP_SIZE);
            clientRecive(client, buffer, BUFTCP_SIZE);
        }
    }
    clientDisconnect(client);
}
static void rxUpdate(client_t client) {
    if (clientConnect(client) != 0) {
        return;
    }
    memset(buffer, 0, BUFTCP_SIZE);
    sprintf(buffer, "{\"freq\":%d}\n", freq_rx);
    clientSend(client, buffer, BUFTCP_SIZE);
    clientDisconnect(client);
}
static void rxOnOff(client_t client, uint32_t on_off) {
    if (clientConnect(client) != 0) {
        return;
    }
    memset(buffer, 0, BUFTCP_SIZE);
    sprintf(buffer, "{\"start\":%d}\n", on_off);
    clientSend(client, buffer, BUFTCP_SIZE);
    clientDisconnect(client);
}

/*==================[external functions definition]==========================*/

int main() {
    int eleccion, eleccion2;

    client_t client_tx  = clientCreate(PORT_TX, IP_LOCAL);
    client_t client_rx1 = clientCreate(PORT_RX1, IP_LOCAL);

    params_t params_tx = paramsCreate();

    while (1) {
        printf("\n\n Seleccione numericamente el comando que desea realizar:\n\
        [1] Configurar Transmisor\n\
        [2] Encender/Apagar todos los receptores\n\
        [3] Encender un receptor en particular\n\
        [4] Apagar un receptor en particular\n\
        [5] Salir\n\n-> ");
        scanf("%d", &eleccion);
        switch (eleccion) {
            case 1:
                txConfig(client_tx, params_tx);
                if (params_tx->freq != freq_rx) {
                    freq_rx = params_tx->freq;
                    rxUpdate(client_rx1);
                }
                break;
            case 2:
                printf("\n      Que desea hacer:\n\
                [1] Encender todos los receptores\n\
                [2] Apagar todos los receptores\n-> ");
                scanf("%d", &eleccion2);
                switch (eleccion2) {
                    case 1:
                        rxOnOff(client_rx1, RX_ON);
                        break;
                    case 2:
                        rxOnOff(client_rx1, RX_OFF);
                        break;
                    default:
                        break;
                }
                break;
            case 3:
                printf("Completar proximamente...\n");
                break;
            case 4:
                printf("Completar proximamente...\n");
                break;
            case 5:
                printf("Saliendo del programa...\n\n");
                return 0;
            default:
                printf("Comando invalido, vuelve a intentarlo...\n");
                break;
        }
    }
    return 0;
}

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/