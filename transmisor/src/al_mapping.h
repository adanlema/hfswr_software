/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

#ifndef AL_MAPPING_H
#define AL_MAPPING_H

/*==================[inclusions]=============================================*/
#include <stdint.h>
/*==================[macros]=================================================*/
#define FPGA_ADDRS  0x43C00000
#define FPGA_REG    10
#define BUFFER_SIZE FPGA_REG * sizeof(int32_t)

#define OFFSET_START  0
#define OFFSET_PHASE  1
#define OFFSET_PERIOD 2
#define OFFSET_PRT    3
#define OFFSET_CODE   4
#define OFFSET_NUMDIG 5
#define OFFSET_TB     6
/*==================[typedef]================================================*/
typedef volatile uint32_t * addrs_t;
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
addrs_t mapping_initialize(uint32_t addrs, uint32_t cant_reg);
void    mapping_finalize(addrs_t addr, uint32_t cant_reg);
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif
