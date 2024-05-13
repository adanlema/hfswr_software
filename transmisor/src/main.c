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
#include "log_manager.h"
/*==================[macros and definitions]=================================*/
#define EXT_ERR_CREATE_SERVER  1
#define EXT_ERR_CLIENT_CONNECT 2
#define EXT_ERR_LISTENING_SOCK 3
/*==================[internal data declaration]==============================*/
int     server_sock, client_sock;
addrs_t addr_fpga = NULL;
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
void MySignalHandler(int sig);
/*==================[external functions definition]==========================*/

int main() {
    int                n;
    struct sockaddr_in client;

    log_delete();

    // Mapeo de memoria...
    addr_fpga = mappingInit(FPGA_ADDRS, FPGA_REG);
    if (addr_fpga == NULL) {
        return -1;
    }
    params_t params = paramsCreate();
    paramsSetConfig(addr_fpga, params);

    // Creacion del server...
    server_sock = serverInit();
    if (server_sock < 0) {
        log_add("[ERROR]Error al crear el server...");
        exit(EXT_ERR_CREATE_SERVER);
    }
    if (listen(server_sock, 2) == -1) {
        log_add("[ERROR]Error al poner en escucha el socket.");
        exit(EXT_ERR_LISTENING_SOCK);
    }

    // Manejo de señales de linux...
    signal(SIGABRT, MySignalHandler);
    signal(SIGINT, MySignalHandler);
    signal(SIGTERM, MySignalHandler);
    signal(SIGKILL, MySignalHandler);

    while (1) {
        // Conexion con el cliente...
        n           = sizeof(client);
        client_sock = accept(server_sock, (struct sockaddr *)&client, &n);
        if (client_sock < 0) {
            log_add("[ERROR]Error al conectar el cliente.");
            exit(EXT_ERR_CLIENT_CONNECT);
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
    log_add("[-]Cerrando el programa");
    mappingFinalize(addr_fpga, FPGA_REG);
    close(server_sock);
    close(client_sock);
    log_add("[SUCCESS]Programa cerrado con exito");
    exit(EXIT_SUCCESS);
}
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/