#include <signal.h> 
#include <stdio.h> 

#define TIEMPO 5
	
int bucle = 1; 
int numcortes = 0;

void gestor_alarma (int senial)
{ 
	bucle = 0; 
	printf("Se acabo!\n");
}

void gestor_ctrlc(int senial)
{ 
	int res = alarm(TIEMPO);
	printf("Pulso CTRL + C, te quedaban %d seg\n", res); 
	++numcortes;
	
}

int main (void) 
{
	struct sigaction gestion; 
	int err;

	gestion.sa_handler = gestor_ctrlc; 
	gestion.sa_flags = SA_RESTART; 
	
	err = sigaction (SIGINT, &gestion, 0); 
	
	if (err==-1)
	{ 
		perror("SIGINT\n"); 
		exit(-1); 
	}

	gestion.sa_handler = gestor_alarma; 
	gestion.sa_flags = SA_ONESHOT;
	
	err = sigaction (SIGALRM, &gestion, 0); 
	
	if (err==-1)
	{ 
		perror("SIGALARM\n"); 
		exit(-1); 
	}

	printf("Pulse varias veces CTRL + C durante %d segundos.\n", TIEMPO);
	
	alarm(TIEMPO);
	
	while (bucle);

	gestion.sa_handler = SIG_IGN; 
	gestion.sa_flags = SA_ONESHOT; 
	
	err = sigaction (SIGINT, &gestion, 0); 
	
	if (err==-1)
	{ 
		perror("SIGINT\n"); 
		exit(-1); 
	} 
	
	printf("Has intentado cortar %d veces.\n", numcortes);
	
	exit(0); 
}