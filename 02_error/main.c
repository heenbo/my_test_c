#include <stdio.h>

int main(void)
{
	if(0 == ~0xffffffff)
	{
		printf("==\n");
	}
	else
	{
		printf("!=\n");
	}

	return 0;
}
