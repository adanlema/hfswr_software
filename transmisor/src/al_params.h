/* Copyright 2024, Adan Lema <adanlema@hotmail.com> & Carcamo Mariano <mgcarcamo98@gmail.com> */

#ifndef AL_PARAMS_H
#define AL_PARAMS_H

/*==================[inclusions]=============================================*/
#include <stdint.h>
#include <stdio.h>

#include "al_mapping.h"
/*==================[macros]=================================================*/
#define DEFAULT_AB       5000
#define DEFAULT_CODE     1810
#define DEFAULT_CODE_NUM 11
#define DEFAULT_FREQ     10000000
#define DEFAULT_PRF      50
#define DEFAULT_START    0

/*==================[typedef]================================================*/
// typedef struct params_s * params_t;
typedef struct params_s {
    uint32_t prf;
    uint32_t ab;
    uint32_t freq;
    uint32_t code;
    uint32_t code_num;
    uint32_t start;
} * params_t;
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

int      paramsStrtoJson(char * str, params_t params);
void     paramsSetConfig(addrs_t mem_p, params_t config);
void     paramsSaveConfig(params_t params);
void     paramsRestoreDefault(addrs_t addrs, params_t params);
params_t paramsCreate();

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif
