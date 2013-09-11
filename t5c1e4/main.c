/* 
	fork.c - ejemplo de un programa de bifurcación
	El programa pide el ingreso de comandos de UNIX que son dejados en una
	cadena. La cadena es entonces "analizada" encontrando blancos, etc
	Cada comando y sus correspondientes argumentos son puestos en 
	un arreglo de argumentos, execvp es llamada para ejecutar estos comandos
	en un proceso hijo  generado por fork()
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

main()
{
	char buf[1024];
	char *args[64];

	for (;;) 
	{
		/*
		* Pide y lee un comando.
		*/
		printf("Comando: ");

		if (gets(buf) == NULL) 
		{
			printf("\n");
			exit(0);
		}

		/*
		* Dividir la cadena en argumentos.
		*/
		parse(buf, args);

		/*
		* Ejecutar el comando.
		*/
		ejecutar(args);
	}
}

/*
* parse--divide el comando que esta en buf
*        en argumentos. 
*/
parse(char *buf, char **args)
{
	while (*buf != (char) NULL) 
	{
		/*
		* Quitar blancos. Usar nulos, para que
		* el argumento previo sea terminado 
		* automaticamente.
		*/
		while ( (*buf == ' ') || (*buf == '\t') )
			*buf++ = (char) NULL;
	
		/*
		* Guardar los argumentos 
		*/
		*args++ = buf;
	
		/*
		* Brincar sobre los argumentos. 
		*/
		while ((*buf != (char) NULL) && (*buf != ' ') && (*buf != '\t'))
			buf++;
	}
	
	*args = (char) NULL;
}


/*
* ejecutar--genera un proceso hijo y ejecuta
*           el programa.
*/
ejecutar(char **args)
{
	int pid, status;

	/*
	* Obtener un proceso hijo.
	*/
	if ( (pid = fork()) < 0 ) 
	{
		perror("fork");
		exit(1);

		/* NOTA: perror() genera un mensaje de error breve en la 
		* salida de errores describiendo el ultimo error encontrado
		* durante una llamada al sistema o funcion de la biblioteca.
		*/
	}

	/*
	* El proceso hijo ejecuta el codigo dentro del if.
	*/
	if (pid == 0) 
	{
		//execvp(*args, args);
		while(1) ;
		perror(*args);
		exit(1);

	/* NOTA: las versiones execv() y execvp() de execl() son utiles cuando
	   el numero de argumentos es desconocido previamente.
		Los argumentos para execv() y execvp() son el nombre del archivo que
		sera ejecutado y un vector de cadenas que contienen los argumentos.
		El ultimo argumento de cadema debera ser un apuntador a 0 (NULL)

		execlp() y execvp() son llamados con los mismos argumentos que 
		execl() y execv(), pero duplican las acciones del shell en
		la busqueda de un archivo ejecutable en un lista de directorios.
		La lista de directorios es obtenida del PATH.
	*/

	}

	/*
	* El padre ejecuta el wait.
	*/
	while (wait(&status) != pid)
		/* vacio */ ;
}
