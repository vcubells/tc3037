#include <signal.h> 
#include <stdio.h> 

#define TOPE 10 

void ignorar(void); 
void restaurar(void); 
void (*gestor_viejo)(int n); 

int main (void)
{
	int i,j;
	ignorar(); 
	
	printf("CTRL + C será ignorado antes de llegar a %d\n", TOPE); 
	
	for (i=1; i< TOPE; i++)
	{ 
		sleep(1); 
		printf("%4d \n", i); 
	} 
	
	restaurar(); 
	
	printf("Si pulsa CTRL + C terminará el programa \n"); 
	
	while(1)
	{ 
		sleep(1); 
		printf("%4d \n", i++);
	}
}

void ignorar(void) 
{
	gestor_viejo = signal (SIGINT, SIG_IGN); 
	
	if (gestor_viejo == SIG_ERR )
		printf("Error en el gestor.\n");
} 

void restaurar(void) 
{
	printf("\nRestaurando gestor.\n"); 
	
	if ( signal(SIGINT, gestor_viejo) == SIG_ERR )
		printf("Error en la restauración.\n");
}