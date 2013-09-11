#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 10
#define M 5

int main(int argc, char **argv)
{
	int numeros[N][M];
	int *q = &numeros[0][0];
	int columna, i, j;
	
	//Inicializa la semilla de generación de números aleatorios
	srand(time(NULL));
	
	// Inicializar matriz
	for( i=0; i < N; ++i)
		for( j=0; j < M; ++j)
		{
			numeros[i][j] = rand() % 100;
		}
		
	// Imprimir matriz con dos ciclos
	printf("Matriz impresa con dos ciclos:\n");
	for( i=0; i < N; ++i)
	{
		for( j=0; j < M; ++j)
		{
			printf("%3d", *(q + M*i + j));
		}
		
		printf("\n");
	}
	
	
	// Imprimir matriz con dos ciclos
	printf("Matriz impresa con un ciclo y aritmética de apuntadores:\n");
	for(columna=1; q < &numeros[N-1][M]; ++q, ++columna)
	{
		printf("%3d", *q);

		if (columna == M)
		{
			printf("\n");
			columna = 0;
		}
	}
	
	return 0;
}

