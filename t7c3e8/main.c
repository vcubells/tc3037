/*
  Solución al problema del productor-consumidor utilizando semáphoros POSIX (no son parte de Pthreads)
  - 1 productor y 1 consumidor
  - Se utiliza:
   * sem_get() - Es el DOWN, 
   * sem_post() - Es el UP
   * sem_init() - Inicializa un semáforo
   * sem_destroy() - Libera la memoria ocupada por el semáforo
   * sem_getvalue() - Devuelve el valor de un semáforo
*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NHILOS 2
#define ITEMS 50
#define BSIZE 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

sem_t vacio, lleno;

void *  productor(void *);
void *  consumidor(void *);

int in = 0, out = 0, count = 0;
int buffer[BSIZE];

int main(int argc, char **argv)
{
	pthread_t hilos[NHILOS];
	int result, i;
	
	/* Inicializar semáforos */
	sem_init(&vacio, 0, BSIZE);
	sem_init(&lleno, 0, 0);
	
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
	sem_destroy(&vacio);
	sem_destroy(&lleno);
	pthread_exit(NULL);
}

void * productor(void * arg)
{
	int i;
	int items[ITEMS];
	int valor; 
	
	/* Producir elementos */
	printf("+++ Inicia productor\n");
	for(i = 0; i < ITEMS; ++i)
		items[i] = i;
		
	for(i = 0; i < ITEMS; ++i)
	{	
		sem_wait(&vacio);
		printf("El productor está trabajando...\n");
		sleep(rand()%3);
		pthread_mutex_lock(&mutex);
		
		buffer[in] = items[i];
		printf("--- Se produjo el elemento %d \n", buffer[in]);
		++in;
		in %= BSIZE;
		sem_post(&lleno);
		sem_getvalue(&vacio, &valor);
		if (valor == 0) 
			printf("El buffer ya está lleno, productor tiene que esperar\n");
		 
		pthread_mutex_unlock(&mutex);
	}
	
	printf("El productor ya terminó\n");
	
	pthread_exit(NULL);
}

void * consumidor(void * arg)
{
	int i, valor;
	
	printf("--- Inicia consumidor\n");
		
	for(i = 0; i < ITEMS; ++i)
	{
		sem_wait(&lleno);
		printf("El consumidor está trabajando...\n");
		sleep(rand()%3);
		pthread_mutex_lock(&mutex);
	
		printf("--- Se consumió el elemento %d \n", buffer[out]);
		++out;
		out %= BSIZE;
		sem_post(&vacio);
		sem_getvalue(&lleno, &valor);
		if (valor == 0) 
			printf("El búffer está vacío, consumidor tienen que esperar\n");
		 
		pthread_mutex_unlock(&mutex);
	}
	
	printf("El consumidor ya terminó\n");
	
	pthread_exit(NULL);
}


