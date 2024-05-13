/* Copyright 2024, Adan Lema <adanlema@hotmail.com> & Carcamo Mariano <mgcarcamo98@gmail.com> */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <json-c/json.h>

#include "al_params.h"
#include "al_mapping.h"
#include "log_manager.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
static void paramsLoadConfig();
static paramsRestoreDefault(addrs_t addrs, params_t params);
static void paramsCommand(char * command);
/*==================[internal data definition]===============================*/
static struct params_s parametros = {0};
/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static void paramsLoadConfig() {
    FILE * file = fopen(FILE_TXT, "r");
    if (file == NULL) {
        log_add("[ERROR]Error al abrir el archivo.");
        return;
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    if (fileSize == 0) {
        parametros.prf      = DEFAULT_PRF;
        parametros.ab       = DEFAULT_AB;
        parametros.freq     = DEFAULT_FREQ;
        parametros.code     = DEFAULT_CODE;
        parametros.code_num = DEFAULT_CODE_NUM;
        parametros.start    = DEFAULT_START;

    } else {
        rewind(file);
        char texto_json[100];
        if (fgets(texto_json, sizeof(texto_json), file) != NULL) {
            paramsStrtoJson(texto_json, &parametros);
            parametros.start = DEFAULT_START;
        }
    }
    fclose(file);
}

static paramsRestoreDefault(addrs_t addrs, params_t params) {
    FILE * file = fopen(FILE_TXT, "w");
    if (file == NULL) {
        log_add("[ERROR]Error al abrir el archivo.");
        return;
    }
    fclose(file);
    paramsLoadConfig();
    paramsSetConfig(addrs, params);
}

static void paramsCommand(char * command) {
    if (!strcmp(command, "default")) {
        parametros.prf      = DEFAULT_PRF;
        parametros.ab       = DEFAULT_AB;
        parametros.freq     = DEFAULT_FREQ;
        parametros.code     = DEFAULT_CODE;
        parametros.code_num = DEFAULT_CODE_NUM;
        parametros.start    = DEFAULT_START;
    }
}

/*==================[external functions definition]==========================*/

int paramsStrtoJson(char * str, params_t params) {
    struct json_object * parsed_json;
    struct json_object * prf;
    struct json_object * freq;
    struct json_object * ab;
    struct json_object * code;
    struct json_object * code_num;
    struct json_object * start;
    struct json_object * command;

    parsed_json = json_tokener_parse(str);
    if (parsed_json != NULL) {
        json_object_object_get_ex(parsed_json, "prf", &prf);
        params->prf = prf != NULL ? json_object_get_int(prf) : params->prf;

        json_object_object_get_ex(parsed_json, "freq", &freq);
        params->freq = freq != NULL ? json_object_get_int(freq) : params->freq;

        json_object_object_get_ex(parsed_json, "ab", &ab);
        params->ab = ab != NULL ? json_object_get_int(ab) : params->ab;

        json_object_object_get_ex(parsed_json, "code", &code);
        params->code = code != NULL ? json_object_get_int(code) : params->code;

        json_object_object_get_ex(parsed_json, "code-num", &code_num);
        params->code_num = code_num != NULL ? json_object_get_int(code_num) : params->code_num;

        json_object_object_get_ex(parsed_json, "start", &start);
        params->start = start != NULL ? json_object_get_int(start) : params->start;

        json_object_object_get_ex(parsed_json, "command", &command);
        if (command != NULL) {
            paramsCommand(parajson_object_get_string(command));
        }
        return 0;

    } else {
        return -1;
    }
}

void paramsSetConfig(addrs_t mem_p, params_t config) {
    /*  Variables por defecto */
    uint32_t prt_value   = ceil(122880000 / config->prf);
    uint32_t phase_value = ceil((config->freq * 1e9) / 28610229);
    uint32_t tb          = ceil(122880000 / config->ab);
    uint32_t t_value     = ceil(config->code_num * tb);

    /* Escritura y liberacion del bloque */
    mem_p[OFFSET_START]  = 0;
    mem_p[OFFSET_PHASE]  = phase_value;
    mem_p[OFFSET_PERIOD] = t_value;
    mem_p[OFFSET_PRT]    = prt_value;
    mem_p[OFFSET_CODE]   = config->code;
    mem_p[OFFSET_NUMDIG] = config->code_num;
    mem_p[OFFSET_TB]     = tb;
    mem_p[OFFSET_START]  = config->start;
}

void paramsSaveConfig(params_t params) {
    FILE * file = fopen(FILE_TXT, "w");
    if (file == NULL) {
        log_add("[ERROR]Error al abrir el archivo.");
        return;
    }
    fprintf(file,
            "{\"prf\":%d, \"freq\":%d, \"ab\":%d, \"code\":%d, \"code-num\":%d, \"start\":%d}\n",
            params->prf, params->freq, params->ab, params->code, params->code_num, params->start);
    fclose(file);
    if (ferror(file)) {
        log_add("[ERROR]Error al cerrar el archivo.");
    }
}

params_t paramsCreate() {
    paramsLoadConfig();
    return &parametros;
}

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */