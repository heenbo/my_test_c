#include <stdio.h>

void ex(char acHello[])
{
	printf("%d\n", sizeof(acHello));
	return;
}


int main(void)
{
	char acHello[] = "hello";
	ex(acHello);
	return 0;
}
