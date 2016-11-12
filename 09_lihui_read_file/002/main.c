#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)
{
	FILE * fp = NULL;

	fp = fopen(argv[1], "r");
	char input_buf[4096] = {0};
	char *point_key = NULL;
	char *input_char = NULL;

	while(0 < fscanf(fp, "%[^\n]\n", input_buf))
	{
		input_char = input_buf;
		printf("result: buf:%s\n", input_buf);
		while((point_key = strsep(&input_char, " \t,")))
		{
			printf("value = %s\n", point_key);
		}
	}
	
	fclose(fp);
	return 0;
}
