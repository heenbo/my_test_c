#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int get_label_column_from_filepath(char * filepath);

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
	
	printf("label column at: %d\n", get_label_column_from_filepath(argv[1]));

	fclose(fp);
	return 0;
}

static int get_label_column_from_filepath(char * filepath)
{
	int label_column = -1;
	char *point_key = NULL;

	while((point_key = strsep(&filepath, "/._")))
	{
		if(0 == strncmp("labelAt", point_key, strlen("labelAt")))
		{
			label_column = atoi((point_key+strlen("labelAt")));
			return label_column;
			break;
		}
	}
	return -1;//error
}
