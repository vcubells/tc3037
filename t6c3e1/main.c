#include <signal.h> 
#include <stdio.h> 

void gestor_ctrlc(int senial) 
{
	printf("Señal SIGINT (%d) recibida.\n", senial); 
}

int main(void) 
{
	struct sigaction gestion;
	printf("PID=%d. Esperando pulsación de CTRL+C\n", getpid() ); 
	
	gestion.sa_handler = gestor_ctrlc; 
	gestion.sa_flags = SA_ONESHOT;	 
	
	if ( sigaction (SIGINT, &gestion, 0) == -1)
	{ 
		printf("Error al definir gestor de SIGINT\n"); 
		exit(-1); 
	}
	
	while(1);
}