/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

#ifndef AL_CLIENT_H
#define AL_CLIENT_H

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
//! Puntero a la estructura del cliente
typedef struct client_s * client_t;
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/**
 * @brief Client Create
 * Función para crear una estructura de un cliente, devuelve el puntero a la estructura.
 * @param port Puerto a conectar.
 * @param ip   IP a conectar.
 * @return client_t Puntero a la estructura.
 */
client_t clientCreate(uint32_t port, char * ip);
/**
 * @brief Client Connect
 * Función para conectar un cliente con un server
 * @param client Puntero a la estructura del cliente.
 * @return int Retorna 0 si se conecto correctamente, o -1 si fallo.
 */
int      clientConnect(client_t client);
/**
 * @brief Client Disconnect
 * Función para desconectar un cliente con el server.
 * @param client Puntero a la estructura del cliente.
 */
void     clientDisconnect(client_t client);
/**
 * @brief Client Send
 * Función para enviar un mensaje desde el cliente para el server.
 * @param client Puntero a la estructura del cliente.
 * @param buffer Puntero a la cadena de texto.
 * @param size   Tamaño de la cadena de texto.
 */
void     clientSend(client_t client, char * buffer, uint32_t size);
/**
 * @brief Client Recive
 * Función para recibir un mensaje desde el server.
 * @param client Puntero a la estructura del cliente.
 * @param buffer Puntero a la cadena de texto.
 * @param size   Tamaño de la cadena de texto.
 * @return int Retorna 0 si se recibió datos, -1 si fallo.
 */
int      clientRecive(client_t client, char * buffer, uint32_t size);
/**
 * @brief Client Get IP
 * Función que retorna la IP seleccionada.
 * @param client Puntero a la estructura del cliente.
 * @param destino Cadena de texto para almacenar la IP.
 */
void     clientGetIP(client_t client, char * destino);
/**
 * @brief Client Get Port
 * Función que retorna el puerto.
 * @param client Puntero a la estructura del cliente.
 * @return int Puerto.
 */
int      clientGetPort(client_t client);
/**
 * @brief Client Get Sock
 * Función que retorna el sock.
 * @param client Puntero a la estructura del cliente.
 * @return int Sock.
 */
int      clientGetSock(client_t client);
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif
