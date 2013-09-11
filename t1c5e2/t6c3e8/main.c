#include <signal.h> 
#include <stdio.h> 

void gestor_alarm(int senial) 
{
	printf("Recibida señal %d\n", senial);
} 

int main(void) 
{
	sigset_t conjunto;
	printf("Proceso %d. Bloqueando SIGALRM\n", getpid() ); 
	
	if ( sigemptyset(&conjunto) == -1)	//*** crea conjunto vacio
	{ 
		perror("sigemptyset"); 
		exit(-1); 
	} 
	
	if ( sigaddset(&conjunto, SIGALRM) == -1)	//*** añade al conjunto SIGALRM
	{ 
		perror("sigaddset"); 
		exit(-1); 
	} 
	
	if ( sigprocmask (SIG_BLOCK, &conjunto, NULL) == -1)
	{
		perror("sigprocmask"); 
		exit(-1); 
	}

	puts("Se establece alarma(3), pero no actuará."); 
	puts("Espere 3 segundos (o más) y pulse CTRL+C"); 
	
	signal(SIGALRM, gestor_alarm);
	
	alarm(3); 
	pause();
	
	exit(0); 
}