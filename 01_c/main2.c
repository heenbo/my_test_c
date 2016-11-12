#include <stdio.h>

#define N 4
#define Y(n) ((N+1)*n)

int main(void)
{
	int a = Y(6+1);
	printf("a = %d\n", a);
	return 0;
}
