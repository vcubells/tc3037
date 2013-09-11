#include <signal.h>
#include <stdio.h>

#define N 21

char * seniales[N] = { "No definida", "SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP", "SIGABRT", "SIGBUS", "SIGFPE", "SIGKILL", "SIGUSR1", 
					"SIGSEGV", "SIGUSR2", "SIGPIPE", "SIGALRM", "SIGTERM", "SIGSTKFLT", "SIGCHLD", "SIGCONT", "SIGSTOP", "SIGTSTP"};
					
void gestor(int senial)
{
	if (senial < 21)
		printf("Recibi la señal: %d = %s \n", senial, seniales[senial]);
	else
		printf("Recibi la señal: %d pero no la estoy gestionando \n", senial);
}

int main()
{
	int i = 1;
	
	printf("Mi PID = %d \n\n", getpid());
	
	for(; i < N; ++i)
	{
		if (i == 9  || i == 19) continue;
		if ( signal (i, gestor) == SIG_ERR ) { 
			printf("Error en el gestor de señales para la señal %d\n", i); 
			exit(-1);
		}
	}
	
	while(1);
	
	return 0;
}

