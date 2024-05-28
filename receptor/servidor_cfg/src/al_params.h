/* Copyright 2024, Adan Lema <adanlema@hotmail.com> & Carcamo Mariano <mgcarcamo98@gmail.com> */

#ifndef AL_PARAMS_H
#define AL_PARAMS_H

/*==================[inclusions]=============================================*/
#include <stdint.h>
#include <stdio.h>

#include "al_mapping.h"
/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
// typedef struct params_s * params_t;
typedef struct params_s {
    uint32_t freq;
    uint32_t start;
} * params_t;
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
int      paramsStrtoJson(char * str, params_t params);
void     paramsSetConfig(addrs_t mem_p, params_t config);
void     paramsSaveConfig(params_t params);
params_t paramsCreate();

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif
