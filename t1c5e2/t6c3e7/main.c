#include <signal.h> 

int main(void) 
{
	sigset_t conjunto1, conjunto2;

	puts("Creando Conjunto 1 de señales vacio."); 
	if ( sigemptyset(&conjunto1) == -1)	//*** crea conjunto vacío
	{ 
		perror("sigemptyset"); 
		exit(-1); 
	} 
	
	if ( sigaddset(&conjunto1, SIGCHLD) == -1) //*** añade SIGCHLD
	{ 
		perror("sigaddset"); 
		exit(-1); 
	}
	else
		puts ("Añado SIGCHLD"); 
		
	if ( sigismember (&conjunto1, SIGCHLD) )	//*** lo verifica
		puts ("\tSIGCHLD esta en el conjunto 1"); 
	else	
		puts ("\tSIGCHLD NO esta en el conjunto 1"); 
		
	if ( sigismember (&conjunto1, SIGTERM) )	//*** verifica otra
		puts ("\tSIGTERM esta en el conjunto 1"); 
	else	
		puts ("\tSIGTERM NO esta en el conjunto 1");
		
	puts("Creando Conjunto 2 de señales lleno."); 
	if ( sigfillset(&conjunto2) == -1)	//*** crea conjunto lleno
	{ 
		perror("sigfillset"); 
		exit(-1);
	} 
	
	if ( sigdelset(&conjunto2, SIGALRM) == -1) //*** quita SIGALRM
	{ 
		perror("sigdelset"); 
		exit(-1); 
	}
	else
		puts("Elimino SIGALRM"); 
		
	if ( sigismember (&conjunto2, SIGALRM) )	//*** lo verifica
		puts ("\tSIGALRM esta en el conjunto 2"); 
	else	
		puts ("\tSIGALRM NO esta en el conjunto 2"); 
		
	if ( sigismember (&conjunto2, SIGTERM) )	//*** verifica otra
		puts ("\tSIGTERM esta en el conjunto 2"); 
	else	
		puts ("\tSIGTERM NO esta en el conjunto 2");
}