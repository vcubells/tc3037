/*
  Solución al problema de la región crítica utilizando bloqueos con mutexes
   - Funciones pthread_mutex_lock() y pthread_mutex_unlock()
   - Inicialización estática de los mutexes con la macro PTHREAD_MUTEX_INITIALIZER
*/
 
#include <stdio.h>
#include <pthread.h>

#define NHILOS 2
#define VECES 100000

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *  sumar(void *);

int suma = 0;
int a; 

int main(int argc, char **argv)
{
	pthread_t hilos[NHILOS];
	int result, i;
	
	//Crear los hilos
	result = pthread_create(&hilos[0], NULL, sumar, NULL);
	if (result)
		printf("Error al crear el sumador \n");
	
	result = pthread_create(&hilos[1], NULL, sumar, NULL);
	if (result)
		printf("Error al crear el restador \n");
		
	/* Esperar a que terminen los hilos */
	for(i = 0; i < NHILOS; ++i)
	{
		result = pthread_join(hilos[i], NULL);
		if (result)
			printf("Error al adjuntar el hilo %d \n", i);
	}
	
	printf("La suma total es = %d y debía ser %d\n", suma, 2 * VECES);
	
	/* Garantizar que se liberen los recursos */
	pthread_exit(NULL);
}

void * sumar(void * arg)
{
	int i;
	
	for(i = 0; i < VECES; ++i)
	{
		/* Región crítica */
		pthread_mutex_lock(&mutex);
		a = suma ;
		++a;
		suma = a;
		pthread_mutex_unlock(&mutex);
	}
	
	pthread_exit(NULL);
}

 

