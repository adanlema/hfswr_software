/* Copyright 2024, Adan Lema <adanlema@hotmail.com> & Carcamo Mariano <mgcarcamo98@gmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <signal.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <json-c/json.h>

#include "al_mapping.h"
#include "al_server.h"
#include "al_params.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
void MySignalHandler(int sig);
/*==================[external functions definition]==========================*/

int main() {
    int                n, server_sock, client_sock;
    struct sockaddr_in client;

    // Mapeo de memoria...
    addrs_t addr_fpga = mappingInit(FPGA_ADDRS, FPGA_REG);
    if (addr_fpga == NULL) {
        return -1;
    }
    params_t params = paramsCreate();
    paramsSetConfig(addr_fpga, params);

    // Creacion del server...
    server_sock = serverInit();
    if (server_sock < 0) {
        perror("Error al crear el server...");
        exit(EXIT_FAILURE);
    }

    // Manejo de señales de linux...
    signal(SIGINT, &MySignalHandler);

    if (listen(server_sock, 2) == -1) {
        perror("Error al poner en escucha el socket");
    }

    while (1) {
        // Conexion con el cliente...
        n           = sizeof(client);
        client_sock = accept(server_sock, (struct sockaddr *)&client, &n);
        if (client_sock < 0) {
            perror("\n[-]Error al conectar el cliente:");
            exit(0);
        }
        serverClientManagement(client_sock, params, addr_fpga);
        close(client_sock);
    }

    mappingFinalize(addr_fpga, FPGA_REG);
    close(server_sock);
    close(client_sock);
    return 0;
}

void MySignalHandler(int sig) {
    printf("\nCerrando el programa...\n");
    exit(0);
}
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/