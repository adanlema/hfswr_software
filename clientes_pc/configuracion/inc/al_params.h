/* Copyright 2024, Adan Lema <adanlema@hotmail.com> & Carcamo Mariano <mgcarcamo98@gmail.com> */

#ifndef AL_PARAMS_H
#define AL_PARAMS_H

/*==================[inclusions]=============================================*/
#include <stdint.h>
#include <stdio.h>
/*==================[macros]=================================================*/
#define BARKER7_CODE  0x72
#define BARKER7_NUM   0x7
#define BARKER11_CODE 0x0712
#define BARKER11_NUM  0xB
#define BARKER13_CODE 0x1F35
#define BARKER13_NUM  0xD
/*==================[typedef]================================================*/
//! Estructura para los parámetros del radar
typedef struct params_s {
    uint32_t prf;
    uint32_t ab;
    uint32_t freq;
    uint32_t code;
    uint32_t code_num;
    uint32_t start;
} * params_t;
//! Thread para manejar los módulos.
typedef struct thread_args_s {
    int *    soc;
    params_t params;
    char *   r_buff;
    char *   s_buff;
} * thread_args_t;

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
 * @brief Parameters Update
 * Función que actualiza los parámetros de los módulos.
 * @param str 
 * @param params 
 * @return int 
 */
int      paramsUpdate(char * str, params_t params);
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
