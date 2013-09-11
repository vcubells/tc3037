#include <stdio.h>
#include <sys/wait.h>

int factorial(int n)
{
	int i = 2;
	int fact = 1;
	
	for(; i <= n; ++i)
		fact *= i;
		
	return fact;
}

int main(int argc, char **argv)
{
	int num = 0;
	int pid;
	int cod = 0;
	
	do {
		printf("Entra un número entero: ");
		scanf("%d", &num);
		
		pid = fork();
		
		if (pid == -1)
		{
			perror( "No se puede crear el proceso hijo" );
		}
		else if (pid == 0)
		{
			num = factorial(num);
			printf("El factorial en el hijo es : %d\n", num);
			exit(num);
		}
		else {
			pid = wait(&cod);
			if ( WIFEXITED(cod) != 0 )
				printf("El factorial de %d = %d \n", num, WEXITSTATUS(cod));
		}
		
	} while (num != 0);
	
	return 0;
}
