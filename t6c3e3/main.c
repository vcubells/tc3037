#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 

void gestor_sigterm(int senial) 
{
	printf("Señal %d recibida.\n", senial); 
	printf("Terminación del proceso %d a petición del usuario.\n", getpid() ); 
	exit(-1);
}

void gestor_usr1 (int senial) 
{
	printf("Recibida señal = %d \n", senial);
	printf("Número aleatorio: %d\n", rand()%100 );
}


int main(void) 
{
	struct sigaction gestion;
	srand(time(NULL)); 
	
	printf("Proceso = %d\n", getpid()); 
	printf("Para terminar, teclee: # kill -15 pid\n"
		   "Para generar número aleatorio, teclee: # kill -10 pid \n"); 
		   
	gestion.sa_handler = gestor_sigterm; 
	gestion.sa_flags = SA_ONESHOT; 
	
	if ( sigaction (SIGTERM, &gestion, 0) ==-1) //*** señal 15 - fin software
	{ 
		printf("Error al definir gestor de SIGTERM\n"); 
		exit(-1); 
	} 
	
	gestion.sa_handler = gestor_usr1; 
	gestion.sa_flags = SA_RESTART; 
	
	if ( sigaction (SIGUSR1, &gestion, 0) == -1) //*** señal 10 - usuario
	{ 
		printf("Error al definir gestor de SIGUSR1\n"); 
		exit(-1); 
	} 

	while(1) {
		pause();
		printf("PID=%d. Esperando a que llegue cualquier señal.\n", getpid());
	}
}