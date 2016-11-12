#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>

static int get_label_column_from_filepath(char * filepath);
static int get_column_from_filepath(char * filepath);
static int analysis_dir_all_file(char * dir_path);

int main(int argc, char **argv)
{

	analysis_dir_all_file(argv[1]);
#if 0
	char * tmp_str = NULL;
	int label_column = -1;

	tmp_str = malloc(strlen(argv[1])+1);
	strcpy(tmp_str, argv[1]);
	if(-1 == (label_column = get_label_column_from_filepath(tmp_str)))
	{
		printf("file name error\n");	
		return(-1);
	}

	strcpy(tmp_str, argv[1]);
	get_column_from_filepath(tmp_str);

	free(tmp_str);
#endif
	return 0;
}

//通过文件名获取类标签所在的列数，注意：列从0开始计数
static int get_label_column_from_filepath(char * filepath)
{
	int label_column = -1;
	char * point_key = NULL;

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

//通过文件内容获取数据维度，先取得最大列数，减1（类标签占用一列）就是维度数，不知道对不对？
static int get_column_from_filepath(char * filepath)
{
	int column_max = -1;
	FILE * fp = NULL;
	int i = 0;
	char input_buf[4096] = {0};
	char * point_key = NULL;
	char * input_str = NULL;

	fp = fopen(filepath, "r");
	if(!fp)
	{
		printf("fopen %s error\n", filepath);
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
	printf("%s 的数据维度: %d\n", filepath, column_max-1);	

	fclose(fp);
	return column_max;
}

//遍历目录，获取目录下所有文件的文件名，用于分析
static int analysis_dir_all_file(char * dir_path)
{
	DIR *dp = NULL;
	struct dirent *entry = NULL;
	struct stat statbuf;
	char current_file_path[1024] = {0};	


	if((dp = opendir(dir_path)) == NULL)
	{
		printf("cannot open directory: %s\n", dir_path);
		return -1;
	}

	chdir(dir_path);
	while((entry = readdir(dp)) != NULL)
	{
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode))
		{
			//                        if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
			{
				continue;
			}
		}
		else
		{
			memset(current_file_path, 0, sizeof(current_file_path));
			getcwd(current_file_path, sizeof(current_file_path));
			strcat(current_file_path, "/");
			strcat(current_file_path, entry->d_name);
			printf("current_file_path: %s\n", current_file_path);
		}

	}	

	return 0;
}
