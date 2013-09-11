#include <stdio.h>

int main(int argc, char **argv)
{
	
	int a = 0, b = 0, c = 0, *p1 = NULL, *p2 = NULL;
	void *p = NULL;
	
	printf("%3c %3c %3c %10s %10s %10s \n", 'a', 'b', 'c', "p1", "p2", "p");
	printf("%3d %3d %3d %10p %10p %10p \n", a, b, c, p1, p2, p);
	
	p1 = &a;
	printf("%3d %3d %3d %10p %10p %10p \n", a, b, c, p1, p2, p);
	
	*p1 = 1;
	printf("%3d %3d %3d %10p %10p %10p \n", a, b, c, p1, p2, p);
	
	p2 = &b;
	printf("%3d %3d %3d %10p %10p %10p \n", a, b, c, p1, p2, p);
	
	*p2 = 2;
	printf("%3d %3d %3d %10p %10p %10p \n", a, b, c, p1, p2, p);
	
	p1 = p2;
	printf("%3d %3d %3d %10p %10p %10p \n", a, b, c, p1, p2, p);
	
	*p1 = 0;
	printf("%3d %3d %3d %10p %10p %10p \n", a, b, c, p1, p2, p);
	
	p2 = &c;
	printf("%3d %3d %3d %10p %10p %10p \n", a, b, c, p1, p2, p);
	
	*p2 = 3;
	printf("%3d %3d %3d %10p %10p %10p \n", a, b, c, p1, p2, p);
	
	p = &p1;
	printf("%3d %3d %3d %10p %10p %10p \n", a, b, c, p1, p2, p);
	
	p1 = p2;
	printf("%3d %3d %3d %10p %10p %10p \n", a, b, c, p1, p2, p);
	
	*p1 = 1;
	printf("%3d %3d %3d %10p %10p %10p \n", a, b, c, p1, p2, p);
	
	return 0;
}

