#include <signal.h> 
#include <unistd.h>
#include <stdio.h>

void gestor_ctrlc (int senial) 
{
	printf("***(%d)*** Pulsó CTRL + C (señal número %d) \n", getpid(), senial);
}

int main (void)
{
	int i,j, k=10;
	
	if ( signal (SIGINT, SIG_DFL) == SIG_ERR ) { 
		printf("Error en el gestor de señales.\n"); 
		exit(-1);
	}
	
	while ( k-- > 0)
	{ 
		printf("(%d)PID=%d. En espera de CTRL + C\n", k, getpid() ); 
		sleep(1);
	}
}