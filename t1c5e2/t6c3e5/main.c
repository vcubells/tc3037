#include <stdio.h> 
#include <signal.h> 
#include <sys/types.h> 

void funcion_hijo(void);

void gestor_usr1 (int senial) 
{
	printf("(PADRE)-. !No vuelvas tarde! . Adiós..\n");
}

int main(void) 
{
	pid_t pid; 
	struct sigaction gestion; 
	int err;
	
	gestion.sa_handler = gestor_usr1; 
	gestion.sa_flags = SA_ONESHOT; 
	
	err = sigaction (SIGUSR1, &gestion, 0); 
	
	if (err ==-1) { 
		perror("SIGUSR1\n"); 
		exit(-1); 
	} 
	
	pid = fork();
	if (pid == 0) 
		funcion_hijo();	//*** las sentencias a partir de aquí no las
						//*** ejecuta el hijo porque terminó con exit(0) 
	wait(NULL);			//*** Cuando el padre recibe SIGUSR1 se despide
	
	
	return 0; 
}

void funcion_hijo(void) 
{
	printf("(HIJO).- !Papa!, soy %d, me voy de antro.\n", getpid() );
	
	kill ( getppid(), SIGUSR1);
	
	printf("(HIJO) Adiós....%d\n", getppid() );
	
	exit(0); 
}