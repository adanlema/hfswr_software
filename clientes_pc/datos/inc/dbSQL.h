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
//! Puntero a la base de datos
typedef sqlite3 * datadb_t;
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/**
 * @brief Data Base Create
 * Función para crear la base de datos.
 * @param filename nombre del archivo de base de datos que se creará.
 * @return datadb_t Puntero a la base de datos.
 */
datadb_t datadbCreate(const char * filename);
/**
 * @brief Data Base Store
 * Función para almacenar los valores en la base de datos.
 * @param db Puntero a la base de datos.
 * @param md Puntero a los metadatos.
 * @return int Retorna un 0 si fue correcto, o -1 si fallo.
 */
int      datadbStore(datadb_t db, metadata_t md);
/**
 * @brief Data Base Finalize
 * Función para cerrar la base de datos.
 * @param db Puntero a la base de datos.
 */
void     datadbFinalize(datadb_t db);

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif