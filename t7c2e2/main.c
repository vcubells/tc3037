
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	8

char *messages[NUM_THREADS];

struct thread_data
{
	int	thread_id;
	int  sum;
	char *message;
};

struct thread_data thread_data_array[NUM_THREADS];

void * Run(void *threadarg)
{
	int tid, sum;
	char * msg;
	struct thread_data *my_data;
	
	my_data = (struct thread_data *) threadarg;
	tid = my_data->thread_id;
	sum = my_data->sum;
	msg = my_data->message;
	printf("Subproceso %d: %s  Suma=%d\n", tid, msg, sum);
	
	pthread_exit(NULL);
}



int main(int argc, char *argv[])
{
	pthread_t threads[NUM_THREADS];
	int *taskids[NUM_THREADS];
	int rc, t, sum;
	
	sum=0;
	messages[0] = "Mensaje 1";
	messages[1] = "Mensaje 2";
	messages[2] = "Mensaje 3";
	messages[3] = "Mensaje 4";
	messages[4] = "Mensaje 5"; 
	messages[5] = "Mensaje 6";
	messages[6] = "Mensaje 7";
	messages[7] = "Mensaje 8";
	
	for(t=0;t<NUM_THREADS;t++) {
		sum = sum + t;
		thread_data_array[t].thread_id = t;
		thread_data_array[t].sum = sum;
		thread_data_array[t].message = messages[t];
		printf("Subproceso %d creado\n", t);
		rc = pthread_create(&threads[t], NULL, Run, (void *) 
							&thread_data_array[t]);
		if (rc) {
			printf("Error al crear el subproceso:  %d\n", rc);
			exit(-1);
		}
	}
	pthread_exit(NULL);
}
