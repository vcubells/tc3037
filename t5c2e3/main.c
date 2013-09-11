#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
     
 /* Lee caracteres del fifo y los muestra en stdout. */
void read_from_fifo (char* file)
{
       FILE *stream;
       int c;
       stream = fopen (file, "r");
       while ((c = fgetc (stream)) != EOF)
	   {
		   //printf("Estoy leyendo \n");
		   putchar (c);
       }
	   
	   //fclose (stream);
}
     
/* Escribe en el pipe. */
void write_to_fifo (char* file)
{
       FILE *stream;
       stream = fopen (file, "w");
       //fprintf (stream, "estoy escribiendo en el pipe...\n");
     //  while(1) {
		   printf("Estoy escribiendo...\n");
		   fprintf (stream, "...info en el fifo\n");
	  // }
      // fclose (stream);
}

/* Main */
int main (void)
{
       pid_t pid;
       char * file = "/tmp/fifo";
	   
     
       /* Crear el fifo. */
       if (mkfifo(file, 777))
	   {
		   puts("Bien");
		}
      
	  /* Crear un proceso hijo que leerá del pipe. */
       pid = fork ();
	   
	   if (pid == (pid_t) 0)
         {
           /* Este es el proceso hijo, hay que cerrar el otro extremo antes de leer */ 
				read_from_fifo (file);
           //return EXIT_SUCCESS;
         }
       else if (pid < (pid_t) 0)
         {
           /* Error al crear el proceso hijo */
           fprintf (stderr, "No se puede crear el subrpoceso\n");
           return EXIT_FAILURE;
         }
       else
         {
           /* Este es el padre, hay que cerrar el otro extremo antes de escribir */
			write_to_fifo (file);
           //return EXIT_SUCCESS;
         }

}