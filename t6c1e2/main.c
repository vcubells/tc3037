#include <signal.h> 
#include <stdio.h> 

void gestor_ctrlc (int); 

int main (int argc, char *argv[] ) 
{
	int k =10;
	void (*ret_signal)();
	
	if (argc<2) {
		printf("Uso correcto: # %s [I|D|M] \n", argv[0]);
		printf("\t\t( I=Ignorar	D=Defecto	M=Manejador programado )\n");
		exit(-1); 
	}

	switch ( toupper(argv[1][0]) ) {
		case 'I' : ret_signal = signal(SIGINT, SIG_IGN ) ; break; 
		case 'D' : ret_signal = signal(SIGINT, SIG_DFL ) ; break;
		case 'M' : ret_signal = signal(SIGINT, gestor_ctrlc ) ; break; 
		default :
			printf("Opción no válida. Debe ser I, D o M .\n"); 
			exit(-1);
	} 
	
	if (ret_signal == SIG_ERR )
	{ 
		printf("Error en el gestor de señales.\n"); 
		exit(-1);
	} 
	
	while(k-- > 0)
	{ 
		printf("(%d) PID=%d. En espera de CTRL + C\n", k, getpid() );
		sleep(2); 
	}
}
		
void gestor_ctrlc (int senial)
{
	printf("***** Ha pulsado CTRL + C (señal número %d) \n", senial);
}