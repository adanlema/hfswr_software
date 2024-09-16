/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

#ifndef DBSQL_H
#define DBSQL_H

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <sqlite3.h>

#include "fpga_redpitaya.h"
/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
typedef sqlite3 * datadb_t;
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
datadb_t datadbCreate(const char * filename);
int      datadbStore(datadb_t db, metadata_t md);
void     datadbFinalize(datadb_t db);
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif