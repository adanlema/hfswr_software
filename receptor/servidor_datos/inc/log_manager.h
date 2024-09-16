/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

#ifndef LOG_DESCRIPTOR_H
#define LOG_DESCRIPTOR_H

/*==================[inclusions]=============================================*/

#include <stdio.h>

/*==================[macros]=================================================*/
//! Path del archivo .log
#define LOG_PATH "./src/txsyslog.log"

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/**
 * @brief Log Adder
 * Añade una cadena de texto al archivo log.
 * @param str Puntero a la cadena de texto.
 */
void log_add(char * str);
/**
 * @brief Log Delete
 * Elimina el archivo log.
 */
void log_delete();

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif
