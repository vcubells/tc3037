/*
  Solución al problema del productor-consumidor utilizando variables de condición
  - NP productores y NC consumidores
  - Se utiliza pthread_cond_broadcast()
*/

#include <stdio.h>
#include <pthread.h>

#define NHILOS 2
#define ITEMS 50
#define BSIZE 5

#define NP 2
#define NC 3

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t produce = PTHREAD_COND_INITIALIZER;
pthread_cond_t consume = PTHREAD_COND_INITIALIZER;

void *  productor(void *);
void *  consumidor(void *);

int in = 0, out = 0, count = 0;
int buffer[BSIZE];

int main(int argc, char **argv)
{
	pthread_t hilos[NP+NC];
	int result, i, nh;
	
	//Crear los hilos
	for (i = 0; i < NP; ++i)
	{
		result = pthread_create(&hilos[i], NULL, productor, (void *) i);
		if (result)
			printf("Error al crear el productor \n");
	}
	
	for (i = 0; i < NC; ++i )
	result = pthread_create(&hilos[NP+i], NULL, consumidor, (void *)i);
	if (result)
		printf("Error al crear el consumidor \n");
		
	/* Esperar a que terminen los hilos */
	nh  = NP + NC;
	for(i = 0; i < nh; ++i)
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
	int id = (int) arg;
	
	/* Producir elementos */
	printf("+++ Inicia productor %d\n", id);
	for(i = 0; i < ITEMS; ++i)
		items[i] = i;
		
	for(i = 0; i < ITEMS; ++i)
	{
		sleep(rand()%3);
		pthread_mutex_lock(&mutex);
		if (count < BSIZE)
		{
			buffer[in] = items[i];
			printf("P%d --- Se produjo el elemento %d \n", id, buffer[in]);
			++in;
			in %= BSIZE;
			++count;
			if (count == 1) pthread_cond_broadcast(&consume);
		}
		else {
			printf("-------------- Productor %d se durmió ------------\n", id);
			pthread_cond_wait(&produce, &mutex);
			printf("-------------- Productor %d se despertó ------------\n", id);
		}
		 
		pthread_mutex_unlock(&mutex);
	}
	
	pthread_exit(NULL);
}

void * consumidor(void * arg)
{
	int i;
	int id = (int) arg;
	
	printf("--- Inicia consumidor %d\n", id);
		
	for(i = 0; i < ITEMS; ++i)
	{
		sleep(rand()%3);
		pthread_mutex_lock(&mutex);
		if (count > 0)
		{
			printf("C%d --- Se consumió el elemento %d \n", id, buffer[out]);
			++out;
			out %= BSIZE;
			--count;
			if (count == (BSIZE-1)) pthread_cond_broadcast(&produce);
		}
		else {
			printf("-------------- Consumidor %d se durmió ------------\n", id);
			pthread_cond_wait(&consume, &mutex);
			printf("-------------- Consumidor %d se despertó ------------\n", id);
		}
		 
		pthread_mutex_unlock(&mutex);
	}
	
	pthread_exit(NULL);
}



