#include <stdio.h>
#include <string.h>

typedef struct {
	char nombre[30];
	char apellidos [30];
	int edad;
}persona;

typedef union {
	char nombre[30];
	char apellidos [30];
	int edad;
}pers;


int main(int argc, char **argv)
{
	persona p;
	pers u;
	
	strcpy(p.nombre, "Juana");
	strcpy(p.apellidos, "Bacallao");
	p.edad = 45;
	
	printf("%s %s %d\n", p.nombre, p.apellidos, p.edad);
	
	strcpy(u.nombre, "Juana");
	strcpy(u.apellidos, "Bacallao");
	u.edad = 15;
	
	strcpy(p.nombre, "Juana");
	strcpy(p.apellidos, "Bacallao");
	
	printf("%s %s %d\n", u.nombre, u.apellidos, u.edad);
	
	return 0;
}


