#include <stdio.h>
#include <string.h>

int flag[10] = {0};

void printf_number(char num);

int main(int argc, char **argv)
{
	int i = 0;
	int len = 0;
	long long int num = 0;
	char str_num[1024] = {0};

	printf("input num:__________________\b\b\b\b\b\b\b\b\b\b\b\b");
	scanf("%lld", &num);
	sprintf(str_num, "%lld", num);	
	len = strlen(str_num);
	for(i = 0; i < len; i ++)
	{
		printf_number(str_num[i]);
	}
	printf("\n");
	
	return 0;
}
void printf_number_str(char num)
{
	if(0 == flag[num - '0'])
	{
		printf("%c", num);
		flag[num - '0'] = 1;
	}
	
}
void printf_number(char num)
{
	switch(num)
	{
		case '0':
			printf_number_str(num);
			break;
		case '1':
			printf_number_str(num);
			break;
		case '2':
			printf_number_str(num);
			break;
		case '3':
			printf_number_str(num);
			break;
		case '4':
			printf_number_str(num);
			break;
		case '5':
			printf_number_str(num);
			break;
		case '6':
			printf_number_str(num);
			break;
		case '7':
			printf_number_str(num);
			break;
		case '8':
			printf_number_str(num);
			break;
		case '9':
			printf_number_str(num);
			break;
		default:
			break;
	}
}
