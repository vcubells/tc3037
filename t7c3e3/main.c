/*
  Demostrar el problema de bloqueos cuando se invierten los mutexes
  para proteger dos variables globales
*/

#include <stdio.h>
#include <pthread.h>

#define NHILOS 2
#define VECES 50

pthread_mutex_t mutex_c = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_p = PTHREAD_MUTEX_INITIALIZER;

void *  productor(void *);
void *  consumidor(void *);

int p, c;

int main(int argc, char **argv)
{
	pthread_t hilos[NHILOS];
	int result, i;
	
	//Crear los hilos
	result = pthread_create(&hilos[0], NULL, productor, NULL);
	if (result)
		printf("Error al crear el sumador \n");
	
	result = pthread_create(&hilos[1], NULL, consumidor, NULL);
	if (result)
		printf("Error al crear el restador \n");
		
	/* Esperar a que terminen los hilos */
	for(i = 0; i < NHILOS; ++i)
	{
		result = pthread_join(hilos[i], NULL);
		if (result)
			printf("Error al adjuntar el hilo %d \n", i);
	}
	
	/* Garantizar que se liberen los recursos */
	pthread_exit(NULL);
}

void * productor(void * arg)
{
	int i;
	
	for(i = 0; i < VECES; ++i)
	{
		 pthread_mutex_lock(&mutex_p);
		 sleep(1);
		pthread_mutex_lock(&mutex_c);
		p = c + 1;
		pthread_mutex_unlock(&mutex_c);
		pthread_mutex_unlock(&mutex_p);
	}
	
	pthread_exit(NULL);
}

void * consumidor(void * arg)
{
	int i;
	
	for(i = 0; i < VECES; ++i)
	{
		pthread_mutex_lock(&mutex_c);
		sleep(1);
		pthread_mutex_lock(&mutex_p);
		p = c + 1;
		pthread_mutex_unlock(&mutex_p);
		pthread_mutex_unlock(&mutex_c);
	}
	
	pthread_exit(NULL);
}
