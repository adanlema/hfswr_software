/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

#ifndef METADATA_H
#define METADATA_H
/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>

/*==================[macros]=================================================*/
#define DATATYPE_SIZE 50
/*==================[typedef]================================================*/
typedef struct dataradar_s * dataradar_t;

struct dataradar_s {
    int    fc;
    int    fs;
    int    size_data;
    int    lost_data;
    char   pulse_time[DATATYPE_SIZE];
    char   origin[DATATYPE_SIZE];
    char   format[DATATYPE_SIZE];
    void * data;
};
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif