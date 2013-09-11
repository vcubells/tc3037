#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
     
int main (int argc, char **argv)
{
       int aflag = 0;
       int bflag = 0;
       char *cvalue = NULL;
       int index;
       int c;
     
       opterr = 0;
     
       while ((c = getopt (argc, argv, "abc:")) != -1)
         switch (c)
           {
           case 'a':
             aflag = 1;
             break;
           case 'b':
             bflag = 1;
             break;
           case 'c':
             cvalue = optarg;
             break;
           case '?':
             if (optopt == 'c')
               fprintf (stderr, "Opción -%c requiere un argumento.\n", optopt);
             else if (isprint (optopt))
               fprintf (stderr, "Opción desconocida '-%c'.\n", optopt);
             else
               fprintf (stderr,
                        "Opción desconocida '\\x%x'.\n",
                        optopt);
             return 1;
           default:
             abort ();
           }
     
       printf ("aflag = %d, bflag = %d, cvalue = %s\n",
               aflag, bflag, cvalue);
     
       for (index = optind; index < argc; index++)
         printf ("El argumento no es una opción válida %s\n", argv[index]);
		 
       return 0;

}