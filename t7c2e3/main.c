#include <stdio.h>
#include <pthread.h>

#define HILOS 50

void * hilo(void * param)
{
	int id = (int) param; 
	int espera = rand() % 20;
	
	printf("Soy el hilo %d y voy a esperar %d segundos\n", id, espera);
	sleep(espera);
	printf("Ya desperté soy el hilo %d...me voy\n", id);

	pthread_exit(0);	
}

int main(int argc, char **argv)
{
	pthread_t hilos[HILOS];
	int result, i = 0;
	
	for(; i < HILOS; ++i)
	{
		result = pthread_create(&hilos[i], NULL, hilo, (void *) i);
		if (result) {
			printf("Error al crear el hilo %d \n", i);	
		}
		else {
			printf("Creado el hilo %d....\n", i);	
		}
	}
	
	//Esperar a que todos los hilos terminen de trabajar
	
	for(i=0; i < HILOS; ++i)
	{
		result = pthread_join(hilos[i], NULL);
		if (!result) {
			printf("Uniendo el hilo %d ------------ \n", i);
		}
	}
	
}
