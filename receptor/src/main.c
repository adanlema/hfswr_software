/* Copyright 2024, Adan Lema <adanlema@hotmail.com> & Carcamo Mariano <mgcarcamo98@gmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "al_mapping.h"
#include "al_server.h"
#include "log_manager.h"
/*==================[macros and definitions]=================================*/
#define PHASE_CARRIER  0
#define ADDR_RESET     1
#define WRITE_EN       2
#define LAST_ADDR      3
#define BUFFER_TO_READ 4
#define LOST_DATA      5

#define EXT_ERR_CREATE_SERVER  1
#define EXT_ERR_CLIENT_CONNECT 2
#define EXT_ERR_LISTENING_SOCK 3
/*==================[internal data declaration]==============================*/
static int     server_sock, client_sock;
static addrs_t addr_buff_1 = NULL;
static addrs_t addr_buff_2 = NULL;
static addrs_t addr_ctrl_regs = NULL;
/*==================[internal functions declaration]=========================*/
static void MySignalHandler(int sig);
/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static void MySignalHandler(int sig) {
    log_add("[-]Cerrando el programa");
    mappingFinalize(addr_buff_1, FPGA_REG);
    mappingFinalize(addr_buff_2, FPGA_REG);
    mappingFinalize(addr_ctrl_regs, FPGA_REG);
    close(server_sock);
    close(client_sock);
    log_add("[SUCCESS]Programa cerrado con exito");
    exit(EXIT_SUCCESS);
}

static void serverClientManagement(int confd) {
    char *s_buff;
    int buff_leido = 0;
    int i = 0;

    s_buff = malloc(BUFTCP_SIZE);
    if (s_buff == NULL) {
        log_add("[ERROR]Error al reservar memoria");
        exit(EXIT_FAILURE);
    }
    memset(s_buff, 0, BUFTCP_SIZE);

    while(i<5){
        if(buff_leido != addr_ctrl_regs[BUFFER_TO_READ]){
            buff_leido = addr_ctrl_regs[BUFFER_TO_READ];
            switch (addr_ctrl_regs[BUFFER_TO_READ]) {
                case 1:
                    addr_ctrl_regs[WRITE_EN] = (uint32_t)(0xFFFFFFFE & (addr_ctrl_regs[WRITE_EN]));
                    sprintf(s_buff,"\nDatos buffer uno:");
                    send(confd, s_buff, BUFTCP_SIZE, 0);
                    for (addrs_t p = addr_buff_1; p < (addr_buff_1 + 200); ++p) {
                    // for (addrs_t p = addr_buff_1; p < (addr_buff_1 + (addr_ctrl_regs[LAST_ADDR] == 0xFFFFFFFF)? 4095 : addr_ctrl_regs[LAST_ADDR]); ++p) {
                        sprintf(s_buff, "\n%d", (int16_t)(0xFFFF & (*p)));
                        send(confd, s_buff, BUFTCP_SIZE, 0);
                    }
                    if (addr_ctrl_regs[LOST_DATA]) {
                        sprintf(s_buff,"\nSe Perdieron datos!!");
                        send(confd, s_buff, BUFTCP_SIZE, 0);
                    }
                    addr_ctrl_regs[WRITE_EN] = (uint32_t)(0x1 | (addr_ctrl_regs[WRITE_EN]));
                    i++;
                    break;
                case 2:
                    addr_ctrl_regs[WRITE_EN] = (uint32_t)(0xFFFFFFFD & (addr_ctrl_regs[WRITE_EN]));
                    sprintf(s_buff, "\nDatos buffer dos:");
                    send(confd, s_buff, BUFTCP_SIZE, 0);
                    // for (addrs_t p = addr_buff_2; p < (addr_buff_2 + (addr_ctrl_regs[LAST_ADDR] == 0xFFFFFFFF)? 4095 : addr_ctrl_regs[LAST_ADDR]); ++p) {
                    for (addrs_t p = addr_buff_2; p < (addr_buff_2 + 200); ++p) {
                        sprintf(s_buff, "\n%d", (int16_t)(0xFFFF & (*p)));
                        send(confd, s_buff, BUFTCP_SIZE, 0);
                    }
                    if (addr_ctrl_regs[LOST_DATA]) {
                        sprintf(s_buff, "\nSe Perdieron datos!!");
                        send(confd, s_buff, BUFTCP_SIZE, 0);
                    }
                    addr_ctrl_regs[WRITE_EN] = (uint32_t)(0x2 | (addr_ctrl_regs[WRITE_EN]));
                    i++;
                    break;
                default:
                    break;
            };
        }
    }

    free(s_buff);
}

/*==================[external functions definition]==========================*/
int main() {
    int n;
    struct sockaddr_in client;

    log_delete();

    // Mapeo de memoria...
    addrs_t addr_buff_1 = mapping_initialize(FPGA_BUFF1, FPGA_REG);
    if (addr_buff_1 == NULL) {
        return -1;
    }
    addrs_t addr_buff_2 = mapping_initialize(FPGA_BUFF2, FPGA_REG);
    if (addr_buff_2 == NULL) {
        return -1;
    }
    addrs_t addr_ctrl_regs = mapping_initialize(FPGA_CTRL, FPGA_MEM_CTRL_REG);
    if (addr_ctrl_regs == NULL) {
        return -1;
    }
    log_add("[SUCCESS]Mapeo de memoria realizo con exito");

    // Creacion del server...
    server_sock = serverInit();
    if (server_sock < 0) {
        log_add("[ERROR]Error al crear el server");
        exit(EXT_ERR_CREATE_SERVER);
    }
    if (listen(server_sock, 1) == -1) {
        log_add("[ERROR]Error al poner en escucha el socket");
        exit(EXT_ERR_LISTENING_SOCK);
    }

    // Manejo de señales de linux...
    signal(SIGABRT, MySignalHandler);
    signal(SIGINT,  MySignalHandler);
    signal(SIGTERM, MySignalHandler);
    signal(SIGKILL, MySignalHandler);

    //Valores iniciales
    // addr_ctrl_regs[PHASE_CARRIER] = 0x14d5555c; // Frecuencia de portadora en 10 MHz - No deberia tocar esto desde aqui!!! 
    addr_ctrl_regs[ADDR_RESET]    = 1;
    addr_ctrl_regs[WRITE_EN]      = 3;

    while (1) {
        // Conexion con el cliente...
        n = sizeof(client);
        client_sock = accept(server_sock, (struct sockaddr *)&client, &n);
        if (client_sock < 0) {
            log_add("[ERROR]Error al conectar el cliente");
            continue;
        }
        serverClientManagement(client_sock);
        close(client_sock);
    }

    return 0;
}
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/