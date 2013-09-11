#include <stdio.h>

int main(int argc, char **argv)
{
	int *p;
	p = (int *)malloc(sizeof(int)*1000000);
	
	free(p);
	
	
	return 0;
}