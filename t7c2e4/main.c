#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	30

int count = 0;
pthread_mutex_t mcount;

void * worker(void *null)
{
	int i;
	double result=0.0;
	for (i=0; i<1000000; i++)
	{
		result = result + (double)random();
	}
	count ++;
	pthread_mutex_lock(&mcount);
		printf("Se incrementó count de manera segura: %d\n", count);
	pthread_mutex_unlock(&mcount);
	printf("Resultado del subproceso  = %e\n",result);
	pthread_exit((void *) 0);
}

int main(int argc, char *argv[])
{
	pthread_t thread[NUM_THREADS];
	pthread_attr_t attr;
	int rc, t;
	void *status;
	
	/* Inicializar atributos */
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	for(t=0;t<NUM_THREADS;t++)
	{
		printf("creando el subproceso %d\n", t);
		rc = pthread_create(&thread[t], &attr, worker, NULL); 
		if (rc)
		{
			printf("Error al crear el subproceso: %d\n", rc);
			exit(-1);
		}
	}
	
	/* Liberar atributos y esperar por otros subprocesos */
	pthread_attr_destroy(&attr);
	for(t=0;t<NUM_THREADS;t++)
	{
		rc = pthread_join(thread[t], &status);
		if (rc)
		{
			printf("Error al unir el subproceso. Codigo:  %d\n", rc);
			exit(-1);
		}
		printf("Union completada con el subproceso %d, estado= %ld\n",t,(long)status);
	}
	
	pthread_exit(NULL);
}


