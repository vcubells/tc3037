/*
  Solución al problema del productor-consumidor utilizando variables de condición
  - 1 productor y 1 consumidor
*/

#include <stdio.h>
#include <pthread.h>

#define NHILOS 2
#define ITEMS 50
#define BSIZE 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t produce = PTHREAD_COND_INITIALIZER;
pthread_cond_t consume = PTHREAD_COND_INITIALIZER;

void *  productor(void *);
void *  consumidor(void *);

int in = 0, out = 0, count = 0;
int buffer[BSIZE];

int main(int argc, char **argv)
{
	pthread_t hilos[NHILOS];
	int result, i;
	
	//Crear los hilos
	result = pthread_create(&hilos[0], NULL, productor, NULL);
	if (result)
		printf("Error al crear el productor \n");
	
	result = pthread_create(&hilos[1], NULL, consumidor, NULL);
	if (result)
		printf("Error al crear el consumidor \n");
		
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
	int items[ITEMS];
	
	/* Producir elementos */
	printf("+++ Inicia productor\n");
	for(i = 0; i < ITEMS; ++i)
		items[i] = i;
		
	for(i = 0; i < ITEMS; ++i)
	{
		sleep(rand()%3);
		pthread_mutex_lock(&mutex);
		if (count < BSIZE)
		{
			buffer[in] = items[i];
			printf("--- Se produjo el elemento %d \n", buffer[in]);
			++in;
			in %= BSIZE;
			++count;
			if (count == 1) pthread_cond_signal(&consume);
		}
		else {
			printf("-------------- Productor se durmió ------------\n");
			pthread_cond_wait(&produce, &mutex);
			printf("-------------- Productor se despertó ------------\n");
		}
		 
		pthread_mutex_unlock(&mutex);
	}
	
	pthread_exit(NULL);
}

void * consumidor(void * arg)
{
	int i;
	
	printf("--- Inicia consumidor\n");
		
	for(i = 0; i < ITEMS; ++i)
	{
		sleep(rand()%3);
		pthread_mutex_lock(&mutex);
		if (count > 0)
		{
			printf("--- Se consumió el elemento %d \n", buffer[out]);
			++out;
			out %= BSIZE;
			--count;
			if (count == (BSIZE-1)) pthread_cond_signal(&produce);
		}
		else {
			printf("-------------- Consumidor se durmió ------------\n");
			pthread_cond_wait(&consume, &mutex);
			printf("-------------- Consumidor se despertó ------------\n");
		}
		 
		pthread_mutex_unlock(&mutex);
	}
	
	pthread_exit(NULL);
}


