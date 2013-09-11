#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

main()
{
   	int valor = 0;
	int estado;
			
  	printf("Bifurcando el proceso\n");

	valor = fork();
	
	if (valor == -1) 
	{
		printf("Error al crear el proceso hijo \n");
		abort();
	}
	else if (valor == 0)
	{
		printf("Este es el hijo %d y su padre es %d\n", getpid(), getppid());
		exit(5);
	}
	else {
		printf("Estamos en el proceso padre %d y su padre es %d\n", getpid(), getppid());
		if (waitpid(valor, &estado, 0) != -1)
		{
			printf("Ya terminó el proceso hijo %d con código %d\n", valor, WEXITSTATUS(estado));
		}
	}

	//printf("El id del proceso es %d, el proceso padre es %d  y el valor regresado es %d\n", getpid(), getppid(), valor);


}


