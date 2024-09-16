/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

#ifndef FPGA_REDPITAYA_H
#define FPGA_REDPITAYA_H

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
/*==================[macros]=================================================*/
//! Dirección de memoria de los registros de control del transmisor.
#define FPGATX_ADDR 0x43C00000
//! Dirección de memoria de los registros de control del receptor.
#define FPGARX_ADDR 0x40008000
//! Dirección de memoria del buffer 1 del receptor.
#define FPGABF1_ADDR 0x40000000
//! Dirección de memoria del buffer 2 del receptor.
#define FPGABF2_ADDR 0x40004000
//! Cantidad de registros de 32bits para cada buffer.
#define FPGABF_REGS 4096
//! Tamaño de los datos de las estructuras.
#define DATATYPE_SIZE 50

/*==================[typedef]================================================*/

//! Estructura encargada del manejo de los registros de control del transmisor.
typedef struct fpgatx_s {
    volatile uint32_t start;
    volatile uint32_t phase;
    volatile uint32_t period;
    volatile uint32_t prt;
    volatile uint32_t code;
    volatile uint32_t numdig;
    volatile uint32_t tb;
} * fpgatx_t;

//! Estructura para el buffer de memoria del receptor.
typedef struct fpgabuf_s {
    volatile uint32_t data[FPGABF_REGS];
} * fpgabuf_t;

//! Estructura encargada del manejo de los registros de control del receptor.
typedef struct fpgarx_s {
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
} * fpgarx_t;

//! Estructura que contiene los metadatos de los lote de datos.
typedef struct metadata_s {
    int    fc;
    int    fs;
    int    size_data;
    int    lost_data;
    char   pulse_time[DATATYPE_SIZE];
    char   origin[DATATYPE_SIZE];
    char   format[DATATYPE_SIZE];
    void * data;
} * metadata_t;

/*==================[external data declaration]==============================*/
//! Cantidad de registros para los registros de control del transmisor.
#define FPGATX_REGS sizeof(struct fpgatx_s) / sizeof(volatile uint32_t)
//! Cantidad de registros para los registros de control del receptor.
#define FPGARX_REGS sizeof(struct fpgarx_s) / sizeof(volatile uint32_t)

#define FPGATX_BYTE   sizeof(struct fpgatx_s)
#define FPGARX_BYTE   sizeof(struct fpgarx_s)
#define METADATA_BYTE sizeof(struct metadata_s)
#define FPGABUF_BYTE  sizeof(struct fpgabuf_s)
/*==================[external functions declaration]=========================*/

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif