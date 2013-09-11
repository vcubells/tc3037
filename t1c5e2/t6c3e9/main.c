#include <signal.h> 
#include <stdio.h> 

void gestor_ctrlc(int senial) 
{
	puts("Descansando.....");
	sleep(1); 
}

void gestor_ctrlz(int senial) 
{
	printf("Adios.");
	exit(0); 
}

int main(void) 
{
	sigset_t conjunto, pendientes; 
	struct sigaction gestor; 
	int i;

	if ( sigemptyset(&conjunto) == -1) 
	{ 
		perror("sigemptyset"); 
		exit(-1); 
	} 
	
	if ( sigaddset(&conjunto, SIGINT) == -1) 
	{ 
		perror("sigaddset"); 
		exit(-1); 
	} 
	
	if ( sigaddset(&conjunto, SIGTSTP) == -1) 
	{ 
		perror("sigaddset"); 
		exit(-1); 
	}
	
	gestor.sa_handler = gestor_ctrlc; 
	gestor.sa_flags = SA_RESTART ; 
	
	if ( sigaction(SIGINT, &gestor, NULL) ==-1)
	{
		perror("sigaction"); 
		exit(-1);
	} 
	
	gestor.sa_handler = gestor_ctrlz; 
	gestor.sa_flags = SA_RESTART ; 
	
	if ( sigaction(SIGTSTP, &gestor, NULL) ==-1)
	{
		perror("sigaction"); 
		exit(-1);
	} 
	
	while(1)
	{
		if ( sigprocmask (SIG_BLOCK, &conjunto, NULL) == -1) 
		{
			perror("sigprocmask"); 
			exit(-1); 
		}

		puts("Descansar = CTRL+C	Terminar = CTRL+Z."); 
		
		for (i=0; i < 5 ; i++)
		{
			printf("Contando %d\n", i); 
			sleep(1);
		}
		
		sigpending (&pendientes); 
		
		if (sigismember(&pendientes, SIGINT) || sigismember(&pendientes, SIGTSTP) )
		{ 
			puts("Ha pulsado CTRL+Z o CTRL+C mientras contaba.");
			sigprocmask(SIG_UNBLOCK, &conjunto, NULL);
		}
	}
	
	exit(0); 
}