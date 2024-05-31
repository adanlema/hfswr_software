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
#include "metadata.h"
/*==================[macros and definitions]=================================*/

#define EXT_ERR_CREATE_SERVER  1
#define EXT_ERR_CLIENT_CONNECT 2
#define EXT_ERR_LISTENING_SOCK 3

#define FPGA_BUFF1        0x40000000
#define FPGA_BUFF2        0x40004000
#define FPGA_CTRL         0x40008000
#define FPGA_REG          4096
#define FPGA_MEM_CTRL_REG 6
#define BUFFER_SIZE       FPGA_REG * sizeof(int32_t)
#define FPGA_OFFSET_VALID 0

#define PORT_SERVER 2011
#define IP_SERVER   "0.0.0.0"
/*==================[internal data declaration]==============================*/
typedef struct bufferfpga_s {
    volatile uint32_t data[FPGA_REG];
} * bufferfpga_t;

static bufferfpga_t addr_buff_1 = NULL;
static bufferfpga_t addr_buff_2 = NULL;

static struct registerctrl {
    volatile uint32_t phaseCarrier;
    volatile uint32_t addrReset;
    volatile union {
        uint32_t writeEn;
        struct {
            unsigned writeEn_1 : 1;
            unsigned writeEn_2 : 1;
            unsigned : 30;
        };
    };
    volatile uint32_t lastAddr;
    volatile uint32_t bufferToRead;
    volatile uint32_t lostData;
    volatile uint32_t start;
} * ctrl_regs;

static dataradar_t metadata = &(struct dataradar_s){0};
server_t           server   = NULL;

struct tm * sTm;
time_t      now;
/*==================[internal functions declaration]=========================*/
static void mySignalHandler(int sig);
/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static void mySignalHandler(int sig) {
    log_add("[-]Cerrando el programa");
    mappingFinalize((addrs_t)addr_buff_1);
    mappingFinalize((addrs_t)addr_buff_2);
    mappingFinalize((addrs_t)ctrl_regs);
    serverCloseClient(server);
    serverDisconnect(server);
    log_add("[SUCCESS]Programa cerrado con exito");
    exit(EXIT_SUCCESS);
}

static void sendData(server_t sv, addrs_t data) {
    char   buff[20];
    size_t block_size =
        ctrl_regs->lastAddr != -1 ? ctrl_regs->lastAddr : sizeof(struct bufferfpga_s);

    now = time(0);
    sTm = gmtime(&now);
    strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);

    strcpy(metadata->pulse_time, buff);
    metadata->size_data = block_size;
    metadata->lost_data = ctrl_regs->lostData;

    serverSend(sv, (char *)metadata, sizeof(*metadata));
    serverSend(sv, (char *)data, block_size);
}
static void dataManagement(server_t sv) {
    uint32_t buff_leido = -1;
    int      i          = 0;

    log_add("Enviando datos...");
    while (true) {
        if (buff_leido != ctrl_regs->bufferToRead) {
            switch (ctrl_regs->bufferToRead) {
                case 1:
                    buff_leido           = 1;
                    ctrl_regs->writeEn_1 = 0;
                    sendData(sv, addr_buff_1->data);
                    ctrl_regs->writeEn_1 = 1;
                    i++;
                    break;
                case 2:
                    buff_leido           = 2;
                    ctrl_regs->writeEn_2 = 0;
                    sendData(sv, addr_buff_2->data);
                    ctrl_regs->writeEn_2 = 1;
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
    addr_buff_1 = (bufferfpga_t)mappingInit(FPGA_BUFF1, FPGA_REG);
    if (addr_buff_1 == NULL) {
        return -1;
    }
    addr_buff_2 = (bufferfpga_t)mappingInit(FPGA_BUFF2, FPGA_REG);
    if (addr_buff_2 == NULL) {
        return -1;
    }
    ctrl_regs = (struct registerctrl *)mappingInit(FPGA_CTRL,
                                                   sizeof(*ctrl_regs) / sizeof(*((addrs_t)NULL)));
    if (ctrl_regs == NULL) {
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

    // Borrar todo esto si primero corremos el receptor servidor cfg
    ctrl_regs->start        = 0;
    ctrl_regs->phaseCarrier = 0x14d5555c; // FC=10MHz
    ctrl_regs->addrReset    = 0;
    ctrl_regs->writeEn      = 3;
    ctrl_regs->start        = 1;
    log_add("Valores inicializados");

    while (1) {
        if (serverAccept(server) != 0) {
            continue;
        }
        dataManagement(server);
        serverCloseClient(server);
    }

    return 0;
}
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/