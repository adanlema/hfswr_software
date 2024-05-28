/* Copyright 2024, Adan Lema <adanlema@hotmail.com> & Carcamo Mariano <mgcarcamo98@gmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>

#include "al_client.h"
#include "metadata.h"
#include "dataradarSQL.h"
/*==================[macros and definitions]=================================*/
#define IP_LOCAL    "127.0.0.1"
#define BUFTCP_SIZE 4096 * sizeof(uint32_t)

#define PORT_RX1 2011
#define PORT_RX2 2027
#define PORT_RX3 2039
#define PORT_RX4 2063
#define PORT_RX5 2081
#define PORT_RX6 2087
#define PORT_RX7 2099
/*==================[internal data declaration]==============================*/
static client_t rx1 = NULL;
static datadb_t db  = NULL;
static char *   r_buff;
/*==================[internal functions declaration]=========================*/
static void signalHandler(int sig);
/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static void signalHandler(int sig) {
    free(r_buff);
    datadbFinalize(db);
    exit(EXIT_SUCCESS);
}
/*==================[external functions definition]==========================*/

int main() {

    const char * filedatabase = "radar_database.db";
    db                        = datadbCreate(filedatabase);
    if (db == NULL) {
        printf("Error al crear la base de datos...\n");
        return -1;
    }

    rx1 = clientCreate(PORT_RX1, IP_LOCAL);

    // Manejo de señales de linux...
    signal(SIGABRT, signalHandler);
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGKILL, signalHandler);

    datadbFinalize(db);
    return 0;
}

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/