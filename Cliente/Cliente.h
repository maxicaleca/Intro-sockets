/*
 * Cliente.h
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#ifndef TP0_H_
#define TP0_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

#include "utils.h"


t_log* iniciar_logger(void);
t_config* leer_config(void);
void leer_consola(t_log*);
void paquete(int);
void terminar_programa(int, t_log*, t_config*);
void enviar_paquete_prueba(t_log* , int , int );
void crear_y_enviar_paquete_persona();
void enviar_persona(t_log*);
int crear_conexion_servidor_prueba();
void  mostrar_menu();
void menu_principal();

#endif /* TP0_H_ */
