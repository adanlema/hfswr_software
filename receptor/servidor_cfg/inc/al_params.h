/* Copyright 2024, Adan Lema <adanlema@hotmail.com> & Carcamo Mariano <mgcarcamo98@gmail.com> */

#ifndef AL_PARAMS_H
#define AL_PARAMS_H

/*==================[inclusions]=============================================*/
#include <stdint.h>
#include <stdio.h>

#include "al_mapping.h"
/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
//! Estructura para guardar los parámetros del módulo receptor.
typedef struct params_s {
    uint32_t freq;
    uint32_t start;
} * params_t;
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/**
 * @brief Parameters String To Json
 * Almacena en la estructura un string con los parámetros 
 * @param str       Puntero al string con los datos.
 * @param params    Puntero a la estructura.
 * @return int      Retorna un 0 si es correcto, -1 si fallo.
 */
int      paramsStrtoJson(char * str, params_t params);
/**
 * @brief Parameters Save Configure
 * Guarda los parámetros de la estructura en los registros de control
 * del hardware.
 * @param params Puntero a la estructura. 
 */
void     paramsSaveConfig(params_t params);
/**
 * @brief Parameters Create
 * Crea una estructura para los parámetros y devuelve el puntero de esta.
 * @return params_t Puntero a la estructura.
 */
params_t paramsCreate();





/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif
