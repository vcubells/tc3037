#include <stdio.h>
#include <ctype.h>
#define N 20

void strToUpper(char *s);
void strToUpper2(char * const s);

int main(int argc, char **argv)
{
	char cadena[N] = "Esto es un texto";
	char cadena2[N] = "Esto es otro texto";
	
	printf("Caso 1. Un apuntador no constante a un dato no constante: \n");
	
	printf("Original: %s\n", cadena);
	
	strToUpper(cadena);
	
	printf("Mayúsculas: %s\n", cadena);
	
	printf("Caso 2. Un apuntador constante a un dato no constante: \n");
	
	printf("Original 2: %s\n", cadena2);
	
	strToUpper2(cadena2);
	
	printf("Mayúsculas 2: %s\n", cadena2);
	
	return 0;
}

// Ejemplo 1. Un apuntador no constante a un dato no constante
void strToUpper(char *s)
{
	while (*s != '\0') 
	{
		if (islower( *s ))
			*s = toupper( *s );
		++s;
	}
}

// Ejemplo 2. Un apuntador constante a un dato no constante
void strToUpper2(char * const s)
{
	while (*s != '\0') 
	{
		if (islower( *s ))
			*s = toupper( *s );
		++s;
	}
}

