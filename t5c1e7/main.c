#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv, char **environ)
{
	// Obtener valor de una variable
	
	 char **p;
	 char *opt, *dest;
	 
	 dest = malloc(30*sizeof(char));
	 opt = malloc(30*sizeof(char));
	 
	 p = environ;
	 
	putenv("NUEVA=VAR");
	opt = getenv("NUEVA");	
	printf("NUEVA = %s \n", opt);
	
	dest = sprintf("%s;%s", opt, "TEXT");
	setenv("NUEVA", dest, 1);
	
	printf("NUEVA = %s \n", getenv("NUEVA") );
		
	while (*p++ != NULL)
	{
		printf("%s \n", *p);
	}		
	
	
	
	return 0;
}
