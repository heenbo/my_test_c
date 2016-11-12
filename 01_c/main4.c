#include <stdio.h>

int main(void)
{
	int a[10],*m=a,*n=&a[4];
	printf("%d\n", n-m);

	return 0;
}
