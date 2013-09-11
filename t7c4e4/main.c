/*
 * Ejemplo de utilización de señales entre hilos
 * Para ejecutarlo, compilarlo e ir oprimiendo Ctrl+C
*/
#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void * hilo2(void * null)
{
	sigset_t set;
	int sig;
	
	//Crear un conjunto de señales vacío
	sigemptyset(&set);
	
	//Adicionar la señal SIGUSR1  al conjunto
	sigaddset(&set, SIGUSR1);
	
	while(1)
	{
		// El hilo espera hasta que reciba una señal del conjunto (enviada por el Hilo 1 y regresa en signo el número de la señal recibida
		sigwait(&set, &sig);
	
		if (sig == SIGUSR1)
		{
			printf("Soy el hilo 2...\n");
		}
	}
	
	pthread_exit(NULL);
}

void * hilo1 (void * arg)
{
	sigset_t set;
	int counter = 0;
	int signo;
	
	pthread_t *tid = (pthread_t *)arg;
	
	//Crear un conjunto de señales vacío
	sigemptyset(&set);
	
	//Adicionar la señal SIGINT (Ctrl+C) al conjunto
	sigaddset(&set, SIGINT);
	
	while(1)
	{
		// El hilo espera hasta que reciba una señal del conjunto y regresa en signo el número de la señal recibida
		sigwait(&set, &signo);
		if (signo == SIGINT)
		{
			++counter;
			// Mientras no se reciban 4 Ctrl+C, se imprime  un texto que dice que se recibió un Ctrl+C
			// y le manda una señal SIGUSER1 al Hilo 2
			if (counter < 4)
			{
				printf("SIGINT %d recibida en hilo 1... \n", counter);
				pthread_kill(*tid, SIGUSR1);
			}
			else {
				printf("Señal final capturada, el próximo Ctrl+C mata al proceso \n");
				
				//Al recibir el 4to Ctrl+C, desbloqueamos la señal SIGINT para que en el siguiente Ctrl+C termine el trabajo
				pthread_sigmask(SIG_UNBLOCK, &set, NULL);
			}
		}
	}
	
	pthread_exit(NULL);
}

int main()
{
	sigset_t set;
	pthread_t tid, tid2;
	
	//Establecer máscaras para el proceso y sus threads
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGUSR1);
	
	// Bloqueamos las señales SIGINT y SIGUSR1 para que el hilo principal no las procese
	pthread_sigmask(SIG_BLOCK, &set, NULL);
	
	// Crear los hilos. Al hilo1 se le pasa el tid del hilo 2 para que le pueda mandar la señal
	pthread_create(&tid2, NULL, hilo2, NULL);
	pthread_create(&tid, NULL, hilo1, (void *)&tid2);
	
	// Ciclo solamente para ilustrar cuando estamos en el hilo principal
	while(1)
	{
		printf("Estamos en el hilo principal, oprime Ctrl+C ... \n");
		sleep(1);
	}
	
	pthread_join(tid, NULL);
	pthread_join(tid2, NULL);
	
	pthread_exit(NULL);
}


