/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */
/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#include "dbSQL.h"
#include "fpga_redpitaya.h"
/*==================[macros and definitions]=================================*/
#define TEXTSQL_SIZE 10000

#define CREATE_TABLE                                                                               \
    "CREATE TABLE IF NOT EXISTS data_radar("                                                       \
    "ID           INTEGER PRIMARY    KEY AUTOINCREMENT NOT NULL, "                                 \
    "PULSE_TIME   TEXT              NOT NULL, "                                                    \
    "ORIGIN       TEXT              NOT NULL, "                                                    \
    "FC           INTEGER           NOT NULL, "                                                    \
    "FS           INTEGER           NOT NULL, "                                                    \
    "FORMAT       TEXT              NOT NULL, "                                                    \
    "DATA         BLOB              NOT NULL)"

/*==================[internal data declaration]==============================*/
static datadb_t data_base = NULL;
static char     text_sql[TEXTSQL_SIZE];

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static int gestionError(sqlite3 * db) {
    fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
    return sqlite3_errcode(db);
}
/*==================[external functions definition]==========================*/
datadb_t datadbCreate(const char * filename) {
    if (sqlite3_open(filename, &data_base) != SQLITE_OK) {
        gestionError(data_base);
        return NULL;
    }
    if (sqlite3_exec(data_base, CREATE_TABLE, NULL, NULL, NULL) != SQLITE_OK) {
        gestionError(data_base);
        return NULL;
    }
    return data_base;
}

int datadbStore(datadb_t db, metadata_t md) {
    sqlite3_stmt * stmt;
    const char *   sql = "INSERT INTO data_radar (PULSE_TIME, ORIGIN, FC, FS, FORMAT, DATA) VALUES "
                         "(?, ?, ?, ?, ?, ?)";

    // Prepara la consulta SQL
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Error preparando la consulta: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    sqlite3_bind_text(stmt, 1, md->pulse_time, DATATYPE_SIZE, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, md->origin, DATATYPE_SIZE, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, md->fc);
    sqlite3_bind_int(stmt, 4, md->fs);
    sqlite3_bind_text(stmt, 5, md->format, DATATYPE_SIZE, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 6, md->data, md->size_data, SQLITE_STATIC);

    // Ejecuta la consulta
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("Error al ejecutar la consulta...\n");
        gestionError(db);
        return -1;
    }
    sqlite3_finalize(stmt);
    return 0;
}

void datadbFinalize(datadb_t db) {
    sqlite3_close(db);
}

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/