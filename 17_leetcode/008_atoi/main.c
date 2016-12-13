/*************************************************************************
 *   > File Name: main.c
 *   > Author: heenbo
 *   > Mail: 379667345@qq.com 
 *   > Created Time:  2016年12月13日 星期二 15时29分32秒
 *   > Modified Time: 2016年12月13日 星期二 16时28分56秒
 ************************************************************************/

#include <stdio.h>

#define MY_STR "-234214"

extern int myAtoi(char* str);

int main(int argc, char * argv[])
{

	int result = 0;

	result = myAtoi(MY_STR);

	printf("line:%d, result:%d\n", __LINE__, result);
	return 0;
}


int myAtoi(char * str)
{
	int result = 0;
	int str_len = 0;
	int i = 0;	
	int j = 0;
	int exp = 0;

	while('\0' != str[i])
	{
		i++;
	}
	str_len = i;
	i--;
	
	for(;i >= 0; i--)
	{
		if('-' == str[i])
		{
			return (0-result);
		}
		else if('+' == str[i])
		{
			return result;
		}

		for(j = 0, exp = 1; j < str_len-i-1; j++)
		{
			exp *= 10;	
		}
		result += ((str[i]-'0')*exp);
	}
	return result;
}
