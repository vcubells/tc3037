/*
  Solución al problema de los bloqueos utilizando pthread_mutex_trylock()
  - Mala solución porque tiene espera activa
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
		printf(" --- Es el productor\n"); 
		pthread_mutex_lock(&mutex_p);
		 sleep(rand() % 5);
		pthread_mutex_lock(&mutex_c);
		p = c + 1;
		printf("(Productor) %3d\n", p);
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
		printf(" --- Es el consumidor\n"); 
		pthread_mutex_lock(&mutex_c);
		sleep(1);
		while (pthread_mutex_trylock(&mutex_p) )
		{
			pthread_mutex_unlock(&mutex_c);
			sleep(1);
			pthread_mutex_lock(&mutex_c);
		}
		
		p = c + 1;
		printf("(Consumidor) %3d\n", p);
		pthread_mutex_unlock(&mutex_p);
		pthread_mutex_unlock(&mutex_c);
	}
	
	pthread_exit(NULL);
}
