#include <stdio.h>

//#pragma pack (4)
struct AAA
{
	char a[5];
	int b;
	short int c;
};

struct BBB
{
	char *d;
	short int e;
	struct AAA f;
	char g;
};


int main(void)
{
//	unsigned long int a = sizeof(struct BBB);
	printf("sizeof=== (%lu)\n", sizeof(struct BBB));
//	printf("sizeof= %d\n", a);
	return 0;
}
