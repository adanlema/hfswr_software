/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

#ifndef AL_MAPPING_H
#define AL_MAPPING_H

/*==================[inclusions]=============================================*/
#include <stdint.h>
/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
typedef volatile uint32_t * addrs_t;
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
addrs_t mappingInit(uint32_t addrs, uint32_t cant_reg);
void    mappingFinalize(addrs_t addr);
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif
