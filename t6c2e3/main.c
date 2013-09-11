#include <stdio.h>
#include <signal.h>

void gestor(int sid);

int main(int argc, char **argv)
{
	
	int i = 10;
	
	signal(SIGINT, gestor);
	signal(SIGTSTP, gestor);
	
	while (i > 0)
	{
		sleep(1);
		--i;
	}	
	return 0;
}

void gestor(int sid)
{
	if(sid == SIGINT)
		printf("Oprimiste Ctrl+C \n");
	else if (sid == SIGTSTP)
		printf("Oprimiste Ctrl+Z \n");
	else
		printf("Enviaste otra señal\n");
}
