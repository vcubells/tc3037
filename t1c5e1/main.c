#include <stdio.h>
#include <ctype.h>
#define N 20

void printStr(const char *s);
void printStr2(const char * const s);

int main(int argc, char **argv)
{
	char cadena[N] = "Esto es un texto";
	char cadena2[N] = "Esto es otro texto";
	
	printf("Caso 3. Un apuntador no constante a un dato constante: \n");
	
	printStr(cadena);
	
	printf("Caso 4. Un apuntador constante a un dato constante: \n");
	
	printStr2(cadena2);
	
	return 0;
}

// Ejemplo 3. Un apuntador no constante a un dato constante
void printStr(const char *s)
{
	while (*s != '\0') 
	{
		*s = toupper( *s );
		printf("%c", *s);
		++s;
	}
	printf("\n");
}

// Ejemplo 4. Un apuntador constante a un dato constante
void printStr2(const char * const s)
{
	 while (*s != '\0') 
	{
		*s = toupper(*s);
		printf("%c", *s);
		++s;
	} 
}

