#include <stdio.h>
#include <string.h>

int flag0 = 0;
int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
int flag4 = 0;
int flag5 = 0;
int flag6 = 0;
int flag7 = 0;
int flag8 = 0;
int flag9 = 0;
void printf_number(char num);

int main(int argc, char **argv)
{
	int len = 0;
	long long int num = 0;
	char str_num[1024] = {0};
	int i = 0;
	printf("input num:__________________\b\b\b\b\b\b\b\b\b\b\b\b");
	scanf("%lld", &num);
	sprintf(str_num, "%lld", num);	
	len = strlen(str_num);
	for(i = 0; i < len; i ++)
	{
//		printf("str_num[%d]: %c \n", i, str_num[i]);
		printf_number(str_num[i]);
	}
	printf("\n");
	
	return 0;
}

void printf_number(char num)
{
	switch(num)
	{
		case '0':
			if(0 == flag0)
			{
				printf("0");
				flag0 = 1;
			}
			break;
		case '1':
			if(0 == flag1)
			{
				printf("1");
				flag1 = 1;
			}
			break;
		case '2':
			if(0 == flag2)
			{
				printf("2");
				flag2 = 1;
			}
			break;
		case '3':
			if(0 == flag3)
			{
				printf("3");
				flag3 = 1;
			}
			break;
		case '4':
			if(0 == flag4)
			{
				printf("4");
				flag4 = 1;
			}
			break;
		case '5':
			if(0 == flag5)
			{
				printf("5");
				flag5 = 1;
			}
			break;
		case '6':
			if(0 == flag6)
			{
				printf("6");
				flag6 = 1;
			}
			break;
		case '7':
			if(0 == flag7)
			{
				printf("7");
				flag7 = 1;
			}
			break;
		case '8':
			if(0 == flag8)
			{
				printf("8");
				flag8 = 1;
			}
			break;
		case '9':
			if(0 == flag9)
			{
				printf("9");
				flag9 = 1;
			}
			break;
		default:
			break;
	}
}
