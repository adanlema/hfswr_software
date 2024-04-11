/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

#ifndef AL_MAPPING_H
#define AL_MAPPING_H

/*==================[inclusions]=============================================*/
#include <stdint.h>
/*==================[macros]=================================================*/
#define FPGA_BASE_ADDRESS 0x40000000
#define FPGA_REG          4096
#define BUFFER_SIZE       FPGA_REG * sizeof(int32_t)
#define FPGA_OFFSET_VALID 0
/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
volatile uint32_t * mapping_initialize();
void                mapping_finalize(volatile uint32_t * addr);
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif
