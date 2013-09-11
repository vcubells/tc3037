/* Uso de variables globales, privadas a los hilos (TSD)
 * Se usan las funciones
 * - pthread_key_create()
 * - pthread_setspecific()
 * - pthread_getspecific()
 */
#include <stdio.h>
#include <pthread.h>

void * Hilo1(void * id)
{
	pthread_key_t * var;
	var = (pthread_key_t *) id;
	pthread_setspecific(*var, "Hilo 1");
	
	/*
	int * var = (int *) id;
	*var = 50;
	sleep(2);
	printf("en hilo 1 var = %d\n", *var);
	*/
	sleep(2);
	printf("En el hilo 1 var = %s\n", (char*)pthread_getspecific(*var));
}

void * Hilo2(void * id)
{
	pthread_key_t * var;
	int valor = 50;
	var = (pthread_key_t *) id;
	pthread_setspecific(*var, &valor);
	sleep(1);
	/* int * var = (int *) id;
	*var = 100;
	sleep(1);
	printf("en hilo 2 var = %d\n", *var); */
	printf("En el hilo 2 var = %d\n", *((int *)pthread_getspecific(*var)));
}

int main(int argc, char **argv)
{
	int res;
	pthread_key_t var;
	pthread_t tid;
	
	//int temp;
	
	// Crear variable global a los hilos
	res = pthread_key_create(&var, NULL);
	
	pthread_create(&tid, NULL, Hilo1, (void*) &var);
	pthread_create(&tid, NULL, Hilo2, (void*) &var);
	
	pthread_exit(NULL);
}
