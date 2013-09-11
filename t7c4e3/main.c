/*
 * Ejemplo que muestra el uso de los parámetros de calendarización
 * y como un hilo cede el procesador al cumplirse una condición
 * Para poder cambiar la prioridad de un hilo debe ejecutarse el programa con privilegios de administración
 * En Ubuntu: sudo nombre_ejecutable
 * En otras distros: Ejecutarlo bajo la identidad del usuario root
*/
#include <stdio.h>
#include <pthread.h>
#include <sched.h>

#define NHILOS 1

// Hilo que cede el procesador
void * Hilo1(void * id)
{
	int num = 0;
	
	while (1)
	{
		if ((num % 2) != 0)
			printf("%d \n", num);
		
		if (num % 1000 == 0)
		{
			//Cede el procesador
			printf("Cedo el procesador ... \n");
			sched_yield();
			
		}
			
		++num;
	}
	
	pthread_exit(NULL);
}

void * Hilo2(void * id)
{
	while (1)
		printf("Soy el hilo 2 \n");
		
	pthread_exit(NULL);
}

//Hilo donde se cambian las políticas de planificación
void * Prioridad(void * null)
{
 	int politica;
	int res;
	
	// Se obtiene el tid del hilo
	pthread_t tid = pthread_self();
		
	struct sched_param param;
	
	//Se cambia la prioridad del hilo
	param.__sched_priority = 5;
	res = pthread_setschedparam(tid, SCHED_FIFO, &param);
	if(res)
		printf("Hay un error: %d \n", res);
		
	// Se obtiene la prioridad del hilo y se imprime
	pthread_getschedparam(tid, &politica, &param);
	
	printf("La prioridad del hilo es: %d \n", param.__sched_priority);
	
	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	int i;

	pthread_t tid[NHILOS];
	
	//pthread_create(&tid[0], NULL, Hilo1, NULL);
	//pthread_create(&tid[1], NULL, Hilo2, NULL);
	pthread_create(&tid[0], NULL, Prioridad, NULL);
	
	for (i = 0 ; i < NHILOS; ++i )
		pthread_join(tid[i], NULL);
	
	pthread_exit(NULL);
}