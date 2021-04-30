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

	printf("Menú:\n\n1-Mandar PERSONA.\n\n"/*3-Mandar paquete CREAR_PROCESO\n"*/);

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
								log_info(logger, "Opción mandar PERSONA");
								crear_y_enviar_paquete_persona(logger);
								break;

						default:
								log_warning(logger, "Opción no codeada. Volver a intentar más tarde.");
								break;

				}


			leido_string = readline(">");
			leido = atoi(leido_string);

		}

	free(leido_string);
	free(mensaje);


}




void crear_y_enviar_paquete_persona(t_log* logger)
{

	t_persona* persona = malloc(sizeof(t_persona));

		persona->dni=34887744;
		persona->edad=25;
		persona->nombre="Maxi";
		persona->nombre_length = sizeof(persona->nombre);
		persona->pasaporte=1024;


	t_buffer* buffer = malloc(sizeof(t_buffer));

	//Armamos el buffer (size y el stream)

	buffer->size = sizeof(uint32_t) * 3 // DNI, Pasaporte y longitud del nombre
	             + sizeof(uint8_t) // Edad
	             + strlen(persona->nombre) + 1;

	void* stream = malloc(buffer->size);


	int offset = 0; // Desplazamiento

	memcpy(stream + offset, &persona->dni, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, &persona->edad, sizeof(uint8_t));
	offset += sizeof(uint8_t);
	memcpy(stream + offset, &persona->pasaporte, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(stream + offset, &persona->nombre_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, persona->nombre, strlen(persona->nombre));


	buffer->stream = stream;



	//Armamos el paquete
	t_paquete* paquete = malloc(sizeof(t_paquete));
	paquete->buffer=buffer;
	paquete->codigo_operacion= PERSONA;



	void* a_enviar = malloc(buffer->size + sizeof(uint8_t) + sizeof(uint32_t));
	int offset2 = 0;

	memcpy(a_enviar + offset2, &(paquete->codigo_operacion), sizeof(uint8_t));
	offset2 += sizeof(uint8_t);
	memcpy(a_enviar + offset2, &(paquete->buffer->size), sizeof(uint32_t));
	offset2 += sizeof(uint32_t);
	memcpy(a_enviar + offset2, paquete->buffer->stream, paquete->buffer->size);

	int conexion =crear_conexion_servidor_prueba();

	// Por último enviamos
	send(conexion, a_enviar, buffer->size + sizeof(uint8_t) + sizeof(uint32_t), 0);

	// No nos olvidamos de liberar la memoria que ya no usaremos
	free(a_enviar);
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);



}



int crear_conexion_servidor_prueba()
{
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





void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado

	log_info(logger,"Conexión Terminada");
	free(logger);
	free(config);
	liberar_conexion(conexion);


}
