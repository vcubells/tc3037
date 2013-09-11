/*
  Solución al problema anterior utilizando variables de condición
  - Buena solución porque no tiene espera activa
  - Además brinda sincronización (a quien le corresponde el turno)
  - Funciones pthread_cond_wait() y pthread_cond_signal()
*/ 

#include <stdio.h>
#include <pthread.h>

#define NHILOS 2
#define VECES 50

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *  productor(void *);
void *  consumidor(void *);

int p, c, turno = 0;

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
		pthread_mutex_lock(&mutex);
		
		if (turno == 0)
		{
			p = c + turno;
			turno = 1;
			pthread_cond_signal(&cond);
			printf("Estoy en el productor, turno = %d \n", turno);
		}
		else {
			pthread_cond_wait(&cond, &mutex);
		}
		 
		pthread_mutex_unlock(&mutex);
	}
	
	pthread_exit(NULL);
}

void * consumidor(void * arg)
{
	int i;
	
	for(i = 0; i < VECES; ++i)
	{
		printf(" --- Es el consumidor\n"); 
		pthread_mutex_lock(&mutex);
		
		if (turno == 1)
		{
			p = c + turno;
			turno = 0;
			pthread_cond_signal(&cond);
			printf("Estoy en el consumidor, turno = %d \n", turno);
		}
		else {
			pthread_cond_wait(&cond, &mutex);
		}
		 
		pthread_mutex_unlock(&mutex);
	}
	
	pthread_exit(NULL);
}

