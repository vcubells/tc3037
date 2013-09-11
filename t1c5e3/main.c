#include <stdio.h>

void burbuja(int numeros[], const int N, int(*compara)(int a, int b));
int asc(int a, int b);
int desc(int a, int b);
void printArray(int numeros[], const int N);

int main(int argc, char **argv)
{
	int numeros[8] = { 20, 35, 2, 8, 19, 21, 58, 5 };
	printArray(numeros, 8);
	burbuja(numeros, 8, desc);
	printArray(numeros, 8);
	burbuja(numeros, 8, asc);
	printArray(numeros, 8);
	
	return 0;
}

void printArray(int numeros[], const int N)
{
	int *q;
	for(q = &numeros[0]; q < &numeros[N-1]; ++q)
		printf("%3d", *q);
	printf("\n");
}

void burbuja(int numeros[], const int N, int(*compara)(int a, int b))
{
	void intercambia(int *e1, int *e2);
	int i, j;
	
	for( i=1; i < N; ++i)
	{
		for( j=0; j < N-1; ++j)
		{
			if ((*compara)(numeros[j], numeros[j+1]))
				intercambia(&numeros[j], &numeros[j+1]);
		}
	}
}

void intercambia(int *e1, int *e2)
{
	int temp;
	
	temp = *e1;
	*e1 = *e2;
	*e2 = temp;
}

int asc(int a, int b)
{
	return a > b;
}

int desc(int a, int b)
{
	return a < b;
}

