/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

#ifndef FPGA_DRIVER_H
#define FPGA_DRIVER_H
/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
/*==================[macros]=================================================*/
#define BARKER7_CODE  0x72
#define BARKER7_NUM   0x7
#define BARKER11_CODE 0x0712
#define BARKER11_NUM  0xB
#define BARKER13_CODE 0x1F35
#define BARKER13_NUM  0xD

#define FPGA_BASE_ADDRESS 0x43C00000
#define FPGA_OFFSET_START 0
#define FPGA_OFFSET_PHASE 1
#define FPGA_OFFSET_T     2
#define FPGA_OFFSET_PRT   3
#define FPGA_OFFSET_CODE  4
#define FPGA_OFFSET_NUMD  5
#define FPGA_OFFSET_TB    6

#define FPGA_REG 7
/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
int  fpga_initialize();
void fpga_finalize();
void fpga_write_registers(uint32_t freq, uint32_t bw, uint32_t prf, uint32_t code,
                          uint32_t num_code);

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif