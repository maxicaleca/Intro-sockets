/*
 * servidor.c
 *
 *  Created on: 3 mar. 2019
 *      Author: utnso
 */

#include "servidor.h"

int main(void)
{
	void iterator(char* value)
	{
		printf("%s\n", value);
	}

	logger = log_create("log.log", "Servidor", 1, LOG_LEVEL_DEBUG);

	int server_fd = iniciar_servidor();
	log_info(logger, "Servidor listo para recibir al cliente");

	int cliente_fd = esperar_cliente(server_fd);

	t_list* lista;
	while(1)
	{
		int resultado = atender_conexion(cliente_fd);

		if(resultado == EXIT_SUCCESS)
		{
			break;
		}

	}

	close(cliente_fd);
	return EXIT_SUCCESS;
}




int atender_conexion(int unSocket)
{

	t_paquete* paquete = malloc(sizeof(t_paquete));
	paquete->buffer = malloc(sizeof(t_buffer));
	// Primero recibimos el codigo de operacion
	recv(unSocket, &(paquete->codigo_operacion), sizeof(uint8_t), 0);


	switch(paquete->codigo_operacion)
	{
		case PERSONA:
			// Después ya podemos recibir el buffer. Primero su tamaño
			recv(unSocket, &(paquete->buffer->size), sizeof(uint32_t), 0);
			//luego el contenido
			paquete->buffer->stream = malloc(paquete->buffer->size);
			recv(unSocket, paquete->buffer->stream, paquete->buffer->size, 0);
			deserializar_persona(paquete->buffer,logger);
			return EXIT_SUCCESS;
			break;

		case -1:
			log_error(logger, "el cliente se desconecto. Terminando servidor");
			return EXIT_FAILURE;

		default:
			log_warning(logger, "Operacion desconocida. No quieras meter la pata");
			return EXIT_FAILURE;
			break;

	}

	free(paquete->buffer);
	free(paquete);



}





void deserializar_persona(t_buffer* buffer, t_log* logger)
{
	t_persona* persona = malloc(sizeof(t_persona));
	void* stream = buffer->stream;

	  // Deserializamos los campos que tenemos en el buffer
	memcpy(&(persona->dni), stream, sizeof(uint32_t));
	stream += sizeof(uint32_t);
	memcpy(&(persona->edad), stream, sizeof(uint8_t));
	stream += sizeof(uint8_t);
	memcpy(&(persona->pasaporte), stream, sizeof(uint32_t));
	stream += sizeof(uint32_t);

   // Por último, para obtener el nombre, primero recibimos el tamaño y luego el texto en sí:
	memcpy(&(persona->nombre_length), stream, sizeof(uint32_t));
	stream += sizeof(uint32_t);
	persona->nombre = malloc(persona->nombre_length);
	memcpy(persona->nombre, stream, persona->nombre_length);

	printf("Edad de la persona %d \n", (persona->edad));
	printf("Nombre de la persona %s \n", (persona->nombre));
	log_info(logger, "Persona recibida y deserializada");


}





















