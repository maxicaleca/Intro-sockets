/*
 * servidor.h
 *
 *  Created on: 3 mar. 2019
 *      Author: utnso
 */

#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<commons/log.h>
#include "utils.h"

int crear_conexion_servidor_prueba();
int atender_conexion(int);
void deserializar_persona(t_buffer* , t_log*);
int recibir_operacion_new(int);
#endif /* SERVIDOR_H_ */
