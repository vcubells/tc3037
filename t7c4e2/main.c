/* Uso de la función pthread_self() y TSD */
#include <stdio.h>
#include <pthread.h>

void * Hilo(void * id)
{
	pthread_key_t * var;
	pthread_t tid;
	
	var = (pthread_key_t *) id;
	
	tid = pthread_self();
	
	pthread_setspecific(*var, &tid);
	
	printf("En el hilo %ld var = %ld\n", tid, *((pthread_t *)pthread_getspecific(*var)));
}

int main(int argc, char **argv)
{
	int res;
	pthread_key_t var;
	pthread_t tid;
	
	// Crear variable global a los hilos
	res = pthread_key_create(&var, NULL);
	
	pthread_create(&tid, NULL, Hilo, (void*) &var);
	pthread_create(&tid, NULL, Hilo, (void*) &var);
	
	pthread_exit(NULL);
}


