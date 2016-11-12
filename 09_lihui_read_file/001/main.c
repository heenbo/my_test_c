#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	FILE * fp = NULL;
	fp = fopen("./file.txt", "r");
	char buf[2048] = {0};

	while(0 < fscanf(fp, "%[^\n]\n", buf))
	{
		printf("result: buf:%s\n", buf);
	}
	
	fclose(fp);
	return 0;
}
