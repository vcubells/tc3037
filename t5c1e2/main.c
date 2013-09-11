#include <stdio.h>
#include <unistd.h>

main()
{
   printf("Archivos en el directorio son: \n");

   execl("/bin/ls","ls","-l", (char *) NULL);
}


