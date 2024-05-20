/* Copyright 2024, Adan Lema <adanlema@hotmail.com> & Carcamo Mariano <mgcarcamo98@gmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "al_params.h"
#include "al_client.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
static void conection_server(client_t client, params_t params);
/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static void conection_server(client_t client, params_t params) {
    char buffer[BUFTCP_SIZE];
    memset(buffer, 0, BUFTCP_SIZE);
    if (clientConnect(client) != 0) {
        printf("\n\nError al conectar el cliente...\n");
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

/*==================[external functions definition]==========================*/

int main() {
    int eleccion;

    client_t client_tx = clientCreate(PORT_TX, IP_TX);
    client_t client_rx = clientCreate(PORT_RX1, IP_RX1);

    params_t params_tx = paramsCreate();
    params_t params_rx = paramsCreate();

    while (1) {
        printf("\n\n Seleccione numericamente el comando que desea realizar:\n\
        [1] Conectar TX\n\
        [2] Conectar RX\n\
        [3] Salir\n\n");
        scanf("%d", &eleccion);
        switch (eleccion) {
            case 1:
                conection_server(client_tx, params_tx);
                break;
            case 2:
                conection_server(client_rx, params_rx);
                break;
            case 3:
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