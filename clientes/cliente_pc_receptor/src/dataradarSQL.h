/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

#ifndef DATARADARSQL_H
#define DATARADARSQL_H

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>

#include "metadata.h"
#include "sqlite3.h"
/*==================[macros]=================================================*/
#define DATATYPE_SIZE 50
/*==================[typedef]================================================*/
typedef sqlite3 * datadb_t;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
datadb_t datadbCreate(const char * filename);
int      datadbStore(datadb_t db, dataradar_t dr, int size_blob);
void     datadbFinalize(datadb_t db);
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif