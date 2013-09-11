#include <signal.h> 
#include <stdio.h>

void hijo();

int main(int argc, char **argv)
{
	int pid;
	int * estado;
	
	pid = fork();
	
	signal(SIGTSTP, SIG_IGN);
	
	if (pid == 0)
	{
		hijo();
	}
	else if (pid > 0)
	{
		printf("Soy el padre %d, si pulsas Ctrl+C solo moriré yo\n", getpid());
		
		sleep(10);
		
		waitpid(pid, estado, 0);
		
		printf("Ya terminó mi hijo %d\n", pid);
	}
	
	return 0;
}

void hijo()
{
	int i;
	
	signal(SIGINT, SIG_IGN);
		
	sleep(2);
		
	printf("Soy el hijo %d y mi padre es %d \n", getpid(), getppid());
		
	for (i = 0; i < 10; ++i)
		sleep(1);
		
	printf("Ya terminé. Soy el hijo %d y mi padre es %d \n", getpid(), getppid());
	
	exit(0);
}