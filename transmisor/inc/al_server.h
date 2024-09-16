/* Copyright 2024, Adan Lema <adanlema@hotmail.com> */

#ifndef AL_SERVER_H
#define AL_SERVER_H

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
//! Puntero a la estructura de un server.
typedef struct server_s * server_t;
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/**
 * @brief Server Create
 * Crea un server al pasarle como parámetro el puerto y la IP.
 * @param port Puerto
 * @param ip IP
 * @return server_t Puntero al server.
 */
server_t serverCreate(uint32_t port, char * ip);
/**
 * @brief Server Connect
 * Levanta el server para que los clientes se puedan conectar.
 * @param server Es el puntero a la estructura del server.
 * @return Retorna un 0 si se levanto correctamente, o un -1 si fallo.
 */
int      serverConnect(server_t server);
/**
 * @brief Server Disconnect
 * Desconecta el server.
 * @param server Es el puntero a la estructura del server
 */
void     serverDisconnect(server_t server);
/**
 * @brief Server Accept
 * Duerme el server hasta que se conecte algún cliente.
 * @param server Es el puntero a la estructura del server
 * @return Retorna un 0 si se conecto el cliente con el server, o un -1 si fallo.
 */
int      serverAccept(server_t server);
/**
 * @brief Server Close Client
 * Desconecta el cliente del server.
 * @param server Es el puntero a la estructura del server
 */
void     serverCloseClient(server_t server);
/**
 * @brief Server Listen
 * @param server Puntero a la estructura del server.
 * @param n Cantidad de clientes a conectar.
 * @return Retorna un 0 si es correcto, o -1 si fallo.
 */
int      serverListen(server_t server, int n);
/**
 * @brief Server Send 
 * Función para enviar un mensaje desde el server hacia el cliente, recibe como parámetros
 * el puntero a la cadena de texto y su tamaño.
 * @param server Puntero a la estructura del server.
 * @param buffer Puntero a la cadena de texto.
 * @param size   Tamaño de la cadena de texto.
 */
void     serverSend(server_t server, char * buffer, uint32_t size);
/**
 * @brief Server Recive 
 * Función para recibir un mensaje de un cliente al servidor, recibe como parámetros
 * el puntero a la cadena de texto donde se guardara el mensaje y su tamaño.
 * @param server Puntero a la estructura del server.
 * @param buffer Puntero a la cadena de texto.
 * @param size   Tamaño de la cadena de texto.
 * @return int   Retorna un 0 si se recibió con éxito el mensaje, o -1 si fallo.
 */
int      serverRecive(server_t server, char * buffer, uint32_t size);
/**
 * @brief Server Get IP
 * Función que retorna la IP del server.
 * @param server Puntero a la estructura del server.
 * @param destino Puntero a la cadena de texto donde se guardará la IP.
 */
void     serverGetIP(server_t server, char * destino);
/**
 * @brief Server Get Port
 * Función que retorna el puerto del server.
 * @param server Puntero a la estructura del server.
 * @return int Retorna el puerto del server.
 */
int      serverGetPort(server_t server);
/**
 * @brief Server Get Sock
 * Función que retorna el sock que esta usando el server.
 * @param server Puntero a la estructura del server.
 * @return int Retorna el sock del server.
 */
int      serverGetSock(server_t server);

/** @ doxygen end group definition */
/** @ doxygen end group definition */
/** @ doxygen end group definition */
/*==================[end of file]============================================*/
#endif
