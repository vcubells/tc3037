#include <stdio.h>

void f1(int a);
void f2(int a);
void f3(int a);

int main(int argc, char **argv)
{
	void (*f[3])(int) = { f1, f2, f3 };
	int opc = 0;
	do {
		printf("Entre un número del 1 al 3, 4 para terminar: ");
		scanf("%d", &opc);
	
		--opc;
		
		if (opc >= 0 && opc < 3) 
			(*f[opc])(opc);
		
	} while (opc != 3);
	
	return 0;
}

void f1(int a)
{
	printf("Usted invocó a la función 1 con valor %d \n", a);
}

void f2(int a)
{
	printf("Usted invocó a la función 2 con valor %d \n", a);
}

void f3(int a)
{
	printf("Usted invocó a la función 3 con valor %d \n", a);
}

