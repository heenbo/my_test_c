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
static int analysis_and_write_data_to_file(char * filepath, int label_column);
static int output_buf_str_to_file(char *output_str, char * output_file_path);

int main(int argc, char **argv)
{

	analysis_dir_all_file(argv[1]);
#if 0


	strcpy(tmp_str, argv[1]);
	get_column_from_filepath(tmp_str);

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
	char * tmp_str = NULL;
	int label_column = -1;


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
//获取数据维度
			tmp_str = malloc(strlen(current_file_path)+1);
			strcpy(tmp_str, current_file_path);
			get_column_from_filepath(tmp_str);
			free(tmp_str);
//获取类标签所在列数
			tmp_str = malloc(strlen(current_file_path)+1);
			strcpy(tmp_str, current_file_path);
			
			if(-1 != (label_column = get_label_column_from_filepath(tmp_str)))
			{
//分析后写入文件
				free(tmp_str);
				tmp_str = malloc(strlen(current_file_path)+1);
				strcpy(tmp_str, current_file_path);
				analysis_and_write_data_to_file(tmp_str, label_column);
			}
			free(tmp_str);

			printf("\n\n");
		}

	}	

	return 0;
}

//相同类标签的数据写入对应的文件，类标签不再写入，只写数据，(写入完成后，需要再根据记录条数更名)
static int analysis_and_write_data_to_file(char * filepath, int label_column)
{
	FILE * fp = NULL;
	int i = 0;
	char input_buf[4096] = {0};
	char output_buf[4096] = {0};
	char output_str[4096] = {0};
	char * point_key = NULL;
	char * input_str = NULL;
	char label_column_str[100] = {0};
	char output_file_name[128] = {0};
	char output_file_path[256] = {0};


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
		memset(output_buf, 0, sizeof(output_buf));
		//		printf("result: buf:%s\n", input_str);
		while((point_key = strsep(&input_str, " \t,")))
		{
			//如果不是类标签则拼接字符串
			if(label_column != i)
			{
				if(0 != strlen(output_buf))
				{
					strcat(output_buf, "\t");
				}
				strcat(output_buf, point_key);
			}
			else//如果是类标签，则写入label_column_str
			{
				strcpy(label_column_str, point_key);
			}
			i++;
			//			printf("value = %s\n", point_key);
		}
		//输出文件的文件名
		strcpy(output_file_name, "batch1_labelAt0_c");
		strcat(output_file_name, label_column_str);
		//输入文件的路径
		getcwd(output_file_path, sizeof(output_file_path));
		strcat(output_file_path, "/output_file/");
		if(-1 == access(output_file_path, F_OK))
		{
			if(-1 == mkdir(output_file_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
			{
				printf("mkdir %s error", output_file_path);
			}
		}
		strcat(output_file_path, output_file_name);
		//需要输出的字符串
		strcpy(output_str, label_column_str);
		strcat(output_str, "\t");
		strcat(output_str, output_buf);
		//输出到对应的文件
		printf("output_str:%s, output_file_path:%s\n\n\n", output_str, output_file_path);
		output_buf_str_to_file(output_str, output_file_path);

		memset(input_buf, 0, sizeof(input_buf));
	}

	fclose(fp);
	return 0;
}

static int output_buf_str_to_file(char *output_str, char * output_file_path)
{
	FILE * fp = NULL;
	fp = fopen(output_file_path, "a+");
	if(!fp)
	{
		printf("fopen %s error\n", output_file_path);
		return -1;
	}
	
	fprintf(fp, "\n%s", output_str);
	
	fclose(fp);
	return 0;
}
