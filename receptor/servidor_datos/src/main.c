/* Copyright 2024, Adan Lema <adanlema@hotmail.com> & Carcamo Mariano <mgcarcamo98@gmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#include "al_mapping.h"
#include "al_server.h"
#include "log_manager.h"
#include "fpga_redpitaya.h"
/*==================[macros and definitions]=================================*/
#define EXT_ERR_CREATE_SERVER  1
#define EXT_ERR_CLIENT_CONNECT 2
#define EXT_ERR_LISTENING_SOCK 3

#define PORT_SERVER 2011
#define IP_SERVER   "0.0.0.0"
/*==================[internal data declaration]==============================*/
static fpgabuf_t  buff_1   = NULL;
static fpgabuf_t  buff_2   = NULL;
static fpgarx_t   fpgarx   = NULL;
static server_t   server   = NULL;
static metadata_t metadata = &(struct metadata_s){0};

struct tm * sTm;
time_t      now;
/*==================[internal functions declaration]=========================*/
static void mySignalHandler(int sig);
static void initConfigRx(fpgarx_t mem);
static void sendData(server_t sv, fpgarx_t mem, addrs_t buffer);
static void dataManagement(server_t sv, fpgarx_t mem, fpgabuf_t buff1, fpgabuf_t buff2);
/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static void mySignalHandler(int sig) {
    log_add("[-]Cerrando el programa");
    mappingFinalize((addrs_t)buff_1);
    mappingFinalize((addrs_t)buff_2);
    mappingFinalize((addrs_t)fpgarx);
    serverCloseClient(server);
    serverDisconnect(server);
    log_add("[SUCCESS]Programa cerrado con exito");
    exit(EXIT_SUCCESS);
}
static void initConfigRx(fpgarx_t mem) {
    mem->start        = 0;
    mem->phaseCarrier = 0x14d5555c;
    mem->addrReset    = 0;
    mem->writeEn      = 3;
    mem->start        = 1;
    log_add("Valores inicializados");
}
static void sendData(server_t sv, fpgarx_t mem, addrs_t buffer) {
    char   buff[20];
    size_t block_size = mem->lastAddr != -1 ? mem->lastAddr : sizeof(struct fpgabuf_s);

    now = time(0);
    sTm = gmtime(&now);
    strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);

    strcpy(metadata->pulse_time, buff);
    metadata->size_data = block_size;
    metadata->lost_data = mem->lostData;

    serverSend(sv, (char *)metadata, METADATA_BYTE);
    serverSend(sv, (char *)buffer, block_size);
}
static void dataManagement(server_t sv, fpgarx_t mem, fpgabuf_t buff1, fpgabuf_t buff2) {
    uint32_t buff_leido = -1;
    int      i          = 0;

    log_add("Enviando datos...");
    while (1) {
        if (buff_leido != mem->bufferToRead) {
            switch (mem->bufferToRead) {
                case 1:
                    buff_leido     = 1;
                    mem->writeEn_1 = 0;
                    sendData(sv, mem, buff1->data);
                    mem->writeEn_1 = 1;
                    i++;
                    break;
                case 2:
                    buff_leido     = 2;
                    mem->writeEn_2 = 0;
                    sendData(sv, mem, buff2->data);
                    mem->writeEn_2 = 1;
                    i++;
                    break;
                default:
                    buff_leido = -1;
                    break;
            }
        }
    }
}

/*==================[external functions definition]==========================*/
int main() {

    log_delete();

    // Mapeo de memoria...
    buff_1 = (fpgabuf_t)mappingInit(FPGABF1_ADDR, FPGABF_REGS);
    if (buff_1 == NULL) {
        return -1;
    }
    buff_2 = (fpgabuf_t)mappingInit(FPGABF2_ADDR, FPGABF_REGS);
    if (buff_2 == NULL) {
        return -1;
    }
    fpgarx = (fpgarx_t)mappingInit(FPGARX_ADDR, FPGARX_REGS);
    if (fpgarx == NULL) {
        return -1;
    }
    log_add("[SUCCESS]Mapeo de memoria realizo con exito");

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
    signal(SIGABRT, mySignalHandler);
    signal(SIGINT, mySignalHandler);
    signal(SIGTERM, mySignalHandler);
    signal(SIGKILL, mySignalHandler);

    // Borrar esta funcion si corremos primero el servidor cfg receptor
    initConfigRx(fpgarx);

    while (1) {
        if (serverAccept(server) != 0) {
            continue;
        }
        dataManagement(server, fpgarx, buff_1, buff_2);
        serverCloseClient(server);
    }

    return 0;
}
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/