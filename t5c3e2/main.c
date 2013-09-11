#include <stdio.h>
#include <stdlib.h>

int factorial(int n)
{
	int i = 2;
	int fact = 1;
	
	for(; i <= n; ++i)
		fact *= i;
		
	return fact;
}

void read_from_pipe (int file)
{
    int c = 0, fact = 0;
	
	sleep(1);
	
	read(file, &c, sizeof(int));
	
	fact =  factorial(c);
	
	printf("El factorial de %d = %d \n", c, fact);
}
     
/* Escribe en el pipe. */
void write_to_pipe (int file)
{
	int num;
		
	sleep(1);
		
	num = rand() % 10;
	
	printf("Número en el pipe: %d\n", num);
	
	write(file, &num, sizeof(int));
}


int main(int argc, char **argv)
{
	int pid;
	
	int mypipe[2];
     
    /* Crear el pipe. */
    if (pipe (mypipe))
    {
        fprintf (stderr, "No se puede crear el pipe.\n");
         return EXIT_FAILURE;
     }
	
	pid = fork();
	
	if (pid == -1)
		{
			perror( "Error al crear el hijo ");
		}
		else if (pid == 0)
		{
			while(1)
			{
				close(mypipe[1]);
				read_from_pipe(mypipe[0]);
			}
		}
		else {
			while (1)
			{
				close(mypipe[0]);
				write_to_pipe(mypipe[1]);
			}
		}
	
	return 0;
}

