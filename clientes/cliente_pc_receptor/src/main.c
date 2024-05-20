/* Copyright 2024, Adan Lema <adanlema@hotmail.com> & Carcamo Mariano <mgcarcamo98@gmail.com> */

/*==================[inclusions]=============================================*/
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
/*==================[macros and definitions]=================================*/
#define IP  "127.0.0.1"
#define PORT 8080

#define BUFF_SIZE 1024

#define FILE_PATH "./src/rxdata.txt"
/*==================[internal data declaration]==============================*/
static char *r_buff;
static int lfd;
static FILE *data_file;
/*==================[internal functions declaration]=========================*/
static void signalHandler(int sig);
/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static void signalHandler(int sig){
    fprintf(data_file,"Cerrando conexion...\n");
    fclose(data_file);
    close(lfd);
    free(r_buff);
    printf(data_file,"Conexion cerrada con exito\n");
    exit(EXIT_SUCCESS);
}
/*==================[external functions definition]==========================*/

int main() {
    struct sockaddr_in server;

    data_file = fopen(FILE_PATH,"a");

    r_buff = malloc(BUFF_SIZE);

    memset(r_buff,0,BUFF_SIZE);

    lfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(IP);

    connect(lfd, (struct sockaddr *)&server, sizeof server);

    // Manejo de señales de linux...
    signal(SIGABRT, signalHandler);
    signal(SIGINT,  signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGKILL, signalHandler);

    while (1) {
        memset(r_buff,0,BUFF_SIZE);
        if (!(recv(lfd, r_buff, BUFF_SIZE, 0) == 0)) {
            fprintf(data_file,"\n%s", r_buff);
        } else {
            signalHandler(6);
        }
    }

    return 0;
}

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/