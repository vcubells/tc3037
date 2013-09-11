#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int n, m, *p, *q, t = 0;
	
	// Entrar número de filas y columnas
	printf("No. filas? : ");
	scanf("%d", &n);
	
	printf("No. columnas? : ");
	scanf("%d", &m);
	
	// Reservar memoria para almacenar elementos de la matriz
	t = n * m;
	
	p = (int *) malloc(sizeof(int) * t );
	
	// Leer los valores de la matriz
	q = p;
	
	while (q != (p + t))
	{
		printf("[%d, %d]: ", (q-p)/m, (q-p)%m );
		scanf("%d", q);
		++q;
	}
	
	// Imprimir la matriz en formato tabular
	q = p;
	
	while (q != (p + t))
	{
		printf("%3d", *q);
		if ((q-p)%m  == m-1)
			printf("\n");
		++q;
	}
	
	// Liberar memoria
	free(p);
	
	return 0;
}

