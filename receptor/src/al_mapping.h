/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

#ifndef AL_MAPPING_H
#define AL_MAPPING_H

/*==================[inclusions]=============================================*/
#include <stdint.h>
/*==================[macros]=================================================*/
#define FPGA_MEM1         0x40000000
#define FPGA_MEM2         0x42000000
#define FPGA_REG          2048
#define BUFFER_SIZE       FPGA_REG * sizeof(int32_t)
#define FPGA_OFFSET_VALID 0
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
