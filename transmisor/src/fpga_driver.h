/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

#ifndef FPGA_DRIVER_H
#define FPGA_DRIVER_H
/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
/*==================[macros]=================================================*/
#define CODE_BARKER7  0x72
#define CODE_BARKER11 0x0712
#define CODE_BARKER13 0x1F35

#define FPGA_BASE_ADDRESS       0x43C00000
#define FPGA_OFFSET_CODE        0
#define FPGA_OFFSET_PRT         1
#define FPGA_OFFSET_T           2
#define FPGA_OFFSET_PHASE       3
#define FPGA_OFFSET_PHASE_VALID 4
#define FPGA_REG                5
/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
int  fpga_initialize();
void fpga_finalize();
void fpga_write_registers(uint32_t code, uint32_t prt, uint32_t t, uint32_t phase);

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif