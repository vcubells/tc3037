#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define TCP_PORT 5000

int main(int argc, char **argv)
{
	int server, cliente;
	struct sockaddr_in addr;
	socklen_t longitud;
	char buffer[2000];
	size_t l, e;
	
	//Recibe como argumento IP server	
	if (argc != 2)
	{
		printf("Usage: %s IP_server\n", argv[0]);
		exit(-1);
	}

	//Crear socket
	server = socket(PF_INET, SOCK_STREAM, 0);
	if(server == -1)
	{
		perror("Error al crear el socket");
		exit(-1);
	}
	
	// Inicializar estructura
	longitud = sizeof(addr);
	memset(&addr, 0, longitud);
	inet_aton(argv[1], &addr.sin_addr);
	addr.sin_port = htons(TCP_PORT);
	addr.sin_family = AF_INET;
	
	if(bind(server, (struct sockaddr *) &addr, longitud) < 0)
	{
		perror("No se puede hacer el bind");
		exit(-1);
	}
	
	if (listen(server, 5) < 0)
	{
		perror("No se puede hacer el listen");
		exit(-1);
	}
	
	cliente = accept(server, (struct sockaddr *) &addr, &longitud);
	if(cliente >= 0)
	{
		printf("Aceptando conexiones en %s : %d \n", 
				inet_ntoa(addr.sin_addr), 
				ntohs(addr.sin_port));
	}
	
	
		// Leer del socket y mostrar en pantalla
		while( (l = read(cliente, &buffer, sizeof(buffer))) > 0)
		{
			e = write(fileno(stdout), &buffer, l);
			if(e != l)
			{
				perror("Error al escribir en pantalla");
				exit (-1);
			}
		
		
		// Leer de teclado y escribir en el socket
		l = read(fileno(stdin), &buffer, sizeof(buffer));

			e = write(cliente, &buffer, l);
			if(e != l)
			{
				perror("Error al escribir en el socket");
				exit (-1);
			}
		
	}
	
	// Cerramos el socket
	close(server);
	close(cliente);
	
	return 0;
}
