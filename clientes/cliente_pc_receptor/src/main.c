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
#define IP_LOCAL  "127.0.0.1"
#define BUFF_SIZE 4096 * sizeof(uint32_t)

#define PORT_RX1D 2011
#define PORT_RX2D 2039
#define PORT_RX3D 2081
#define FILE_PATH "src/rxdata.bin"
/*==================[internal data declaration]==============================*/
static client_t    rx1 = NULL;
static datadb_t    db  = NULL;
static char *      r_buff;
static dataradar_t metadata = &(struct dataradar_s){0};
static FILE *      data_file;
/*==================[internal functions declaration]=========================*/
static void signalHandler(int sig);
/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static void signalHandler(int sig) {
    free(r_buff);
    clientDisconnect(rx1);
    datadbFinalize(db);
    exit(EXIT_SUCCESS);
}
/*==================[external functions definition]==========================*/

int main() {
    int          recive;
    const char * filedatabase = "radar_database.db";

    db = datadbCreate(filedatabase);
    if (db == NULL) {
        printf("Error al crear la base de datos...\n");
        return -1;
    }

    data_file = fopen(FILE_PATH, "w");
    r_buff    = malloc(BUFF_SIZE);

    rx1 = clientCreate(PORT_RX1D, IP_LOCAL);
    if (clientConnect(rx1) != 0) {
        return -1;
    }
    // Manejo de señales de linux...
    signal(SIGABRT, signalHandler);
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGKILL, signalHandler);

    while (1) {
        recive = clientRecive(rx1, r_buff, BUFF_SIZE);
        if (!(recive == 0 || recive == -1)) {
            fwrite(r_buff, 1, recive, data_file);
        } else {
            FILE *   bin_data;
            uint32_t data[4096];
            size_t   bin_data_size;

            fclose(data_file);
            bin_data = fopen("src/rxdata.bin", "r");

            fseek(bin_data, 0, SEEK_END);
            bin_data_size = ftell(bin_data);
            rewind(bin_data);

            while (ftell(bin_data) < bin_data_size) {
                fread(metadata, sizeof(*metadata), 1, bin_data);
                fread(data, 1, metadata->size_data, bin_data);
                metadata->data = data;
                if (datadbStore(db, metadata, metadata->size_data) != 0) {
                    printf("Error al almacenar los datos..\n");
                }
            }
            signalHandler(6);
        }
    }
    free(r_buff);
    clientDisconnect(rx1);
    datadbFinalize(db);
    return 0;
}

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/