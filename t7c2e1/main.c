#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	50   

void * ejecutaHilo(void *threadid)
{
	int tid;
	tid = (int)threadid;
	printf("Estamos en el subproceso #%d\n", tid);
	pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
	pthread_t threads[NUM_THREADS];
	int rc, t;
	for(t = 0; t < NUM_THREADS; ++t)
	{
		printf("Ahora creamos el subproceso %d\n", t);
		
		rc = pthread_create(&threads[t], NULL, ejecutaHilo, (void *)t);

		if (rc){
			printf("Error al crear el subproceso: %d\n", rc);
			exit(-1);
		}
	}
	pthread_exit(NULL);
}

