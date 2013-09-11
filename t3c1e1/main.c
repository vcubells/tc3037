#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char **argv)
{
	DIR *dp;	/* Descriptor de directorio */
	struct dirent *ep;	/* Estructura que modela una entrada en el directorio */

	char * buffer;
	buffer = getcwd(NULL, 0);
	
	printf("El directorio actual es: %s \n", buffer);
	
	/* Cambiando de directorio */
	buffer = "/etc";
	if ( chdir(buffer) == 0)
		printf("cambiando al directorio: %s ...\n", buffer );
	
	buffer = getcwd(NULL, 0);
	
	printf("El directorio actual es: %s \n", buffer);
	
	/* Leer y visualizar el contenido de una carpeta */
	printf("Contenido del directorio:\n");
	dp = opendir("/home/alumno");		/* Abrir la carpeta */
	if (dp != NULL)				/* Si no hay error, se visualiza el contenido */
	{
		while ( ep = readdir(dp) )	/* Leer cada entrada del directorio */
		{
			printf("%s \t %d \n", ep->d_name, ep->d_type);	/* Imprimir el nombre de cada entrada */
		}
		closedir(dp);			/* Cerrar la carpeta */
	}
	else {
		perror("Error al abrir el directorio");	/* Error al abrir la carpeta */
	}
	 
	return 0;
}

