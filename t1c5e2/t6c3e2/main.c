#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 

void espera_pulsa(char); 

void gestor_ctrlc(int senial) 
{
	printf("Señal %d recibida.\n", senial);
} 

int main (int argc, char *argv[] ) 
{
	if (argc<2) {
		printf("Uso correcto: # %s [D|I|M]\n", argv[0]);
		printf("	(D=Defecto	I=Ignorar	M=Manejador) \n");
		exit(-1); 
	}
	
	printf("PID= %d . Esperando la pulsacion de CTRL + C\n", getpid() );
	espera_pulsa( toupper(argv[1][0])); 
}

void espera_pulsa(char letra) 
{
	struct sigaction gestion, ant_gestion;

	switch (letra) {
		case 'D': gestion.sa_handler = SIG_DFL; break;
		case 'I': gestion.sa_handler = SIG_IGN; printf("Tendrás que matarme; suavemente, por favor.\n"); break;
		case 'M': gestion.sa_handler = gestor_ctrlc; printf("Tendrás que matarme; suavemente, por favor.\n"); break;
	} 
	
	gestion.sa_flags = SA_RESTART; //Restablece la accion corresp. a la señal
	
	if ( sigaction (SIGINT, &gestion, 0) == -1 )
	{ 
		perror("Error al definir el gestor de SIGINT\n"); 
		exit(-1);
	}
	else { 
		sigaction (SIGINT, 0, &ant_gestion); //comprueba el manejador instalado
		if (ant_gestion.sa_handler == SIG_DFL) 
			printf("Instalado handler por defecto.\n");
		else if (ant_gestion.sa_handler == SIG_IGN) 
			printf("La señal SIGINT sera ignorada.\n");
	} 
	
	while (1);
}