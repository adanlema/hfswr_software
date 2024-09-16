
/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

#ifndef AL_MAPPING_H
#define AL_MAPPING_H

/*==================[inclusions]=============================================*/
#include <stdint.h>
/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
//! Puntero a un bloque de memoria
typedef volatile uint32_t * addrs_t;
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/**
 * @brief Mapping Init
 * Puntero al bloque de memoria. Realiza un mapeo virtual del bloque de memoria
 * deseado, para ello se solicita la dirección de memoria y la cantidad de registros
 * de 32 bits deseados.
 * @param addrs Dirección de memoria.
 * @param cant_reg Cantidad de registros de 32 bits.
 * @return addrs_t Retorna un puntero al bloque de memoria virtual.
 */
addrs_t mappingInit(uint32_t addrs, uint32_t cant_reg);
/**
 * @brief Mapping Finalize
 * Libera el bloque de memoria virtual creado.
 * @param addr Puntero al bloque de memoria virtual.
 */
void    mappingFinalize(addrs_t addr);

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif
