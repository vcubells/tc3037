#include <stdio.h>
#include <string.h>

#define N 5

typedef struct {
	char nombre[30];
	char apellidos[30];
	int edad;
} persona;

int edadPromedio(persona p[]);
int masJoven(persona p[]);
int masVieja(persona p[]);
void imprimeRango(persona p[], int ei, int ef);

int main(int argc, char **argv)
{
	persona personas[N];
	int i, opc = 0, edadI, edadF;
	char n[30];
	for(i=0; i < N; i++)
	{
		printf("Datos de la persona %d\n", i);
		
		printf("Entre el nombre: ");
		scanf("%s",&n);
		strcpy(personas[i].nombre, n);
		
		printf("Entre el apellido: ");
		scanf("%s",&n);
		strcpy(personas[i].apellidos, n);
		
		printf("Entre la edad: ");
		scanf("%d",&personas[i].edad);
	}
	
	do {
		printf("1-Edad promedio\n2-Personas mas joven\n3-Persona mas vieja\n4-Rango de edades");
		scanf("%d",&opc);
		
		switch(opc) {
			case 1: 
				printf("La edad promedio es: %d\n", edadPromedio(personas));
				break;
			case 2:
				printf("La persona más joven es:\n");
				i = masJoven(personas);
				printf("%s %s (%d)\n", personas[i].nombre, personas[i].apellidos, personas[i].edad);
				break;
			case 3:
				printf("La persona más vieja es:\n");
				i = masVieja(personas);
				printf("%s %s (%d)\n", personas[i].nombre, personas[i].apellidos, personas[i].edad);
				break;
			case 4:
				printf("Entre la edad inicial: ");
				scanf("%d",&edadI);
				
				printf("Entre la edad final: ");
				scanf("%d",&edadF);
				
				imprimeRango(personas, edadI, edadF);
				break;
				
			default:
				printf("Opción no válida\n");
		}
		
	} while (opc != 0);
	
	return 0;
}

int edadPromedio(persona p[])
{
	int i, suma=0;
	for(i=0; i<N; i++)
	{
		suma += p[i].edad;
	}
	
	return suma/N;
}

int masJoven(persona p[])
{
	int i, menor=0;
	for(i=1; i<N; i++)
	{
		if (p[i].edad < p[menor].edad)
			menor = i;
	}
	
	return menor;
}

int masVieja(persona p[])
{
	int i, mayor=0;
	for(i=1; i<N; i++)
	{
		if (p[i].edad > p[mayor].edad)
			mayor = i;
	}
	
	return mayor;
}

void imprimeRango(persona p[], int ei, int ef)
{
	int i;
	printf("Personas con edades en el rango %d-%d\n\n", ei, ef);
	for(i=0; i<N; i++)
	{
		if (p[i].edad >= ei && p[i].edad <= ef)
			printf("%-30s %-30s (%3d)\n", p[i].nombre, p[i].apellidos, p[i].edad);
	}
}

