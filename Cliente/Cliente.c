/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "Cliente.h"
#include "utils.h"
#include <string.h>
#include <readline/readline.h>


int main(void)
{
	menu_principal();

}


void menu_principal(){
		t_log* logger;
		logger = iniciar_logger();
		mostrar_menu();
		leer_consola(logger);
}


void  mostrar_menu(){

	printf("Menú:\n\n1-Mandar un valor guardado en Cliente.config\n2-Mandar un Mensaje\n\n"/*3-Mandar paquete CREAR_PROCESO\n"*/);

}


void leer_consola(t_log* logger)
{

	int leido;
	char *leido_string;
	char *mensaje = malloc(sizeof(char));
	leido_string = readline(">");
	leido = atoi(leido_string);

		while(leido != 0)
		{
				switch(leido)
				{
						case 1:
								log_info(logger, "Opción mandar un valor");
								mandar_valor(logger);
								break;
					 	case 2:
					 			log_info(logger, "Opción mandar un mensaje");
					 			printf("Ingrese un mensaje para enviar: \n\n");
					 			scanf("%s", mensaje);
					 			mandar_mensaje(logger,mensaje);
					 			break;
						default:
								log_warning(logger, "Opción no codeada. Volver a intentar más tarde.");
								break;

				}


			leido_string = readline(">");
			leido = atoi(leido_string);

		}

	free(leido_string);
	free(leido);
	free(mensaje);


}



/*void enviar_paquete_prueba(t_log* logger, int accion, int id_modulo)
{
	t_paquete* paquete = crear_paquete_segun_accion(accion);
	paquete->id_modulo = id_modulo;


	int conexion = crear_conexion_servidor_prueba();

	agregar_a_paquete(paquete,valor,(strlen(valor)+1));
	enviar_paquete(paquete, conexion);
	eliminar_paquete(paquete);
	terminar_programa(conexion, logger, NULL);
}*/





void mandar_mensaje(t_log* logger,char *mensaje)
{
	int conexion = crear_conexion_servidor_prueba();
	enviar_mensaje(mensaje,conexion);
	terminar_programa(conexion, logger, NULL);

}



void mandar_valor(t_log* logger)
{
	t_paquete* paquete = crear_paquete();
	t_config* config = leer_config();

	char* valor = config_get_string_value(config, "CLAVE");
	int conexion = crear_conexion_servidor_prueba();

	agregar_a_paquete(paquete,valor,(strlen(valor)+1));

	enviar_paquete(paquete, conexion);
	eliminar_paquete(paquete);
	terminar_programa(conexion, logger, config);
}



int crear_conexion_servidor_prueba()
{
	int conexion;
	char* ip;
	char* puerto;

	ip = config_get_string_value(leer_config(), "IP_PRUEBA");
	puerto= config_get_string_value(leer_config(), "PUERTO_PRUEBA");


	return crear_conexion(ip, puerto);

}


t_log* iniciar_logger(void)
{

	return log_create("Cliente.log","TP Integrador",1,0);
}

t_config* leer_config(void)
{

	return config_create("Cliente.config");


}



/*void paquete(int conexion)
{
	//Ahora toca lo divertido! -> Esto es para enviar lo que escribis por consola, lo empaquetas y lo envias

	char* leido;
	t_paquete* paquete;




}*/

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado

	log_info(logger,"Conexión Terminada");
	free(logger);
	free(config);
	liberar_conexion(conexion);


}
