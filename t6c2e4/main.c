#include <stdio.h>
#include <signal.h>

void gestor1(int sid);
void gestor2(int sid);

int main(int argc, char **argv)
{
	int i;
	
	signal(SIGINT, gestor1);
	
	for (i=0; i < 10; ++i)
	{
		sleep(1);
		printf("Contando ovejita %d \n", i+1);
	}
	
	signal(SIGINT, gestor2);
	
	for (i=0; i < 10; ++i)
	{
		sleep(1);
		printf("Contando trineos %d \n", i+1);
	}
	
	signal(SIGINT, gestor1);
	
	for (i=0; i < 10; ++i)
	{
		sleep(1);
		printf("Contando cabrita %d \n", i+1);
	}
	return 0;
}

void gestor1(int sid)
{
	printf("Estoy aprendiendo a manejar señales\n");
}

void gestor2(int sid)
{
	printf("Ahora cambié de gestor...\n");
}
