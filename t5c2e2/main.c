#include <stdio.h>
#include <stdlib.h>
     
void  write_data (FILE * stream)
{
       int i = 0;
       while(1)//for (i = 0; i < 100; i++)
         fprintf (stream, "%d\n", ++i);
       if (ferror (stream))
         {
           fprintf (stderr, "Error al escribir en el stream de salida.\n");
           exit (EXIT_FAILURE);
         }
}
     
int main (void)
{
       FILE *output;
     
       output = popen ("cat", "w");
       if (!output)
         {
           fprintf (stderr,
                    "Error al abrir el pipe.\n");
           return EXIT_FAILURE;
         } 
       
	   write_data (output);
       if (pclose (output) != 0)
         {
           fprintf (stderr,
                    "Error al ejecutar el proceso more.\n");
         }
       return EXIT_SUCCESS;
     }