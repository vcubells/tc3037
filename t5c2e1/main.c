#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
     
 /* Lee caracteres del pipe y los muestra en stdout. */
void read_from_pipe (int file)
{
       FILE *stream;
       int c;
       stream = fdopen (file, "r");
       while ((c = fgetc (stream)) != EOF)
	   {
		   //printf("Estoy leyendo \n");
		   putchar (c);
       }
	   
	   fclose (stream);
}
     
/* Escribe en el pipe. */
void write_to_pipe (int file)
{
       FILE *stream;
       stream = fdopen (file, "w");
       //fprintf (stream, "estoy escribiendo en el pipe...\n");
       while(1) {
		   printf("Estoy escribiendo...\n");
		   fprintf (stream, "...info en el pipe\n");
	   }
       fclose (stream);
}

/* Main */
int main (void)
{
       pid_t pid;
       int mypipe[2];
     
       /* Crear el pipe. */
       if (pipe (mypipe))
         {
           fprintf (stderr, "No se puede crear e pipe.\n");
           return EXIT_FAILURE;
         }
     
       /* Crear un proceso hijo que leerá del pipe. */
       pid = fork ();
	   
	   if (pid == (pid_t) 0)
         {
           /* Este es el proceso hijo, hay que cerrar el otro extremo antes de leer */ 
			   close (mypipe[1]);
				printf("Estoy leyendo...\n");
				read_from_pipe (mypipe[0]);
           //return EXIT_SUCCESS;
         }
       else if (pid < (pid_t) 0)
         {
           /* Error al crear el proceso hijo */
           fprintf (stderr, "No se puede crear el subproceso\n");
           return EXIT_FAILURE;
         }
       else
         {
           /* Este es el padre, hay que cerrar el otro extremo antes de escribir */
			close (mypipe[0]);
			printf("Estoy escribiendo...\n");
			write_to_pipe (mypipe[1]);
           //return EXIT_SUCCESS;
         }

}