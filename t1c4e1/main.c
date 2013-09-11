#include <stdio.h>
#define N 10

int main(int argc, char **argv)
{
	int a[N], suma, i, *p;
	
	// Inicializar arreglo
	for(i=0; i < N; i++)
	{
		a[i] = rand() % 100;
		printf("%3d", a[i]);
	}
	
	printf("\n");
	
	// Arreglos en forma tradicional
	for(i=0, suma = 0; i < N; ++i)
	{
		suma += a[i];
	}
	
	printf("Suma con arreglo tradiconal = %5d\n", suma);
	
	// Arreglos con aritmética de punteros utilizando el nombre del arreglo
	for(i=0, suma = 0; i < N; ++i)
	{
		suma += *(a+i);
	}
	
	printf("Suma con aritmética de punteros utilizando nombre de arreglo = %5d\n", suma);
	
	// Arreglos con aritmética de punteros utilizando un puntero auxiliar p
	for(p=a, suma = 0; i < N; ++i)
	{
		suma += p[i];
	}
	
	printf("Suma con aritmética de punteros utilizando puntero auxiliar = %5d\n", suma);
	
	// Arreglos con aritmética de punteros
	for(p=a, suma = 0; p < &a[N]; ++p)
	{
		suma += *p;
	}
	
	printf("Suma con aritmética de punteros = %5d\n", suma);
	
	return 0;
}
