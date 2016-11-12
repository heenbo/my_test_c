#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int get_label_column_from_filepath(char * filepath);

int main(int argc, char **argv)
{
	FILE * fp = NULL;
	int i = 0;
	char input_buf[4096] = {0};
	char *point_key = NULL;
	char *input_str = NULL;
	int column_max = -1;
	int label_column = -1;
	char *tmp_str = NULL;

	tmp_str = malloc(strlen(argv[1])+1);
	strcpy(tmp_str, argv[1]);
	if(-1 == (label_column = get_label_column_from_filepath(tmp_str)))
	{
		printf("file name error\n");	
		return(-1);
	}
	free(tmp_str);

	printf("label column at: %d\n", label_column);

	fp = fopen(argv[1], "r");
	if(!fp)
	{
		printf("fopen %s error\n", argv[1]);
		return -1;
	}
	while(0 < fscanf(fp, "%[^\n]\n", input_buf))
	{
		i = 0;
		input_str = input_buf;
//		printf("result: buf:%s\n", input_str);
		while((point_key = strsep(&input_str, " \t,")))
		{
				i++;
//			printf("value = %s\n", point_key);
		}

		if(i > column_max)
		{
			column_max = i;
		}
	}
	printf("数据维度: %d\n", column_max);	

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
