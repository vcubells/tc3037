#include <stdio.h>
#include <stdlib.h>


int longitud(const char * const s);
void invertir(char *);
void copiar(char *, char *);

int main(int argc, char **argv)
{
	char *s = "cadena";
    char *d = (char *) malloc(sizeof(char) * strlen(s));
	
	printf("La longitud es : %d \n", longitud(s));
	
	copiar(s, d);
	printf("Despues de copiar d = '%s' \n", d);
	
	invertir(s);
	printf("Despues de invertir s = '%s' \n", s);
	
	free(d);
	
	return 0;
}


int longitud(const char * const s)
{
	char *t = s;
	while (*t != '\0')
		t++;
	return (t-s);	
}

void invertir(char * s)
{
	char *f = s + longitud(s) - 1;
	char t, l;
	char *d = s;
	
	
	while(d < f)
	{
		t = *d;
		*d = *f;
		*f = t;
		++d;
		--f;
	}
}

void copiar(char *o, char *d)
{
	while ( (*d++ = *o++) != '\0' ); 
}
