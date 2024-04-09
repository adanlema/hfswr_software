/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <arpa/inet.h>
/*==================[macros and definitions]=================================*/
#define FPGA_BASE_ADDRESS 0x40000000
#define FPGA_REG          4096
#define BUFFER_SIZE       FPGA_REG * sizeof(uint32_t)
#define FPGA_OFFSET_VALID 0
/*==================[internal data declaration]==============================*/
// Variables de Mapeo
static volatile uint32_t * fpga_addr = NULL;
// Variables para el Servidor/Cliente
static int                sock;
static struct sockaddr_in addr;
static socklen_t          addr_size;
char                      buffer[BUFFER_SIZE];
char *                    ip   = "127.0.0.1";
int                       port = 5566;
/*==================[internal functions declaration]=========================*/
// Funciones de Mapeo
static int  fpga_initialize();
static void fpga_finalize();
// Funciones para el servidor/cliente
static int  client_initialize();
static void client_connect();
static void client_desconnect();
/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static int fpga_initialize() {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        perror("Error opening /dev/mem");
        return -1;
    }

    fpga_addr = mmap(NULL, FPGA_REG * sizeof(uint32_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd,
                     FPGA_BASE_ADDRESS);
    if (fpga_addr == MAP_FAILED) {
        perror("Error mapping FPGA register");
        close(fd);
        return -1;
    }

    return 0;
}
static void fpga_finalize() {
    if (fpga_addr != NULL) {
        munmap(fpga_addr, FPGA_REG * sizeof(uint32_t));
        fpga_addr = NULL;
    }
}
static int client_initialize() {

    // Creacion del socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("[-]Socket error");
        return -1;
    }
    printf("[+]TCP server socket created.\n");
    return 0;
}
static void client_connect() {
    // Inicializa en cero y luego lo carga
    memset(&addr, '\0', sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_port        = port;
    addr.sin_addr.s_addr = inet_addr(ip);

    // Intenta conectarse al server
    connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    printf("Connected to the server.\n");
}
static void client_desconnect() {
    close(sock);
    printf("Disconnected from the server.\n");
}
/*==================[external functions definition]==========================*/
int main() {
    // Inicializacion
    if (fpga_initialize() != 0) {
        fprintf(stderr, "Error al inicializar el bloque de memoria de la FPGA\n");
        return 1;
    }
    printf("Bienvenido al programa de extracion de datos en la FPGA.\n");
    if (client_initialize() != 0) {
        printf("Error al inicializar el Socket");
        return 1;
    }
    client_connect();

    // Area de trabajo
    while (true) {
        uint32_t value = *(fpga_addr + FPGA_OFFSET_VALID);
        if (value == 1) {
            bzero(buffer, BUFFER_SIZE);
            memcpy(buffer, fpga_addr, FPGA_REG * sizeof(uint32_t));
            send(sock, buffer, strlen(buffer), 0);
        }
    };
    // Desconexion
    client_desconnect();
    fpga_finalize();
    return 0;
}
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/