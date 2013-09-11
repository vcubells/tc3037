#include <stdio.h> 
#include <signal.h> 
#include <sys/types.h> 

int main(void)
{ 
	pid_t pidret;
	if ( (pidret = fork() ) == 0)
	{
		//**** código del hijo
		while (1) {
			printf("(HIJO). PID = %d\n", getpid() );
			sleep(1); 
		}
	}
 
	sleep(4); 
	printf("(PADRE). Terminación de mi hijo %d.\n", pidret); 
	
	kill(pidret, SIGTERM); 
	
	return 0;
}