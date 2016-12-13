/*************************************************************************
 *   > File Name: main.c
 *   > Author: heenbo
 *   > Mail: 379667345@qq.com 
 *   > Created Time:  2016年12月13日 星期二 15时29分32秒
 *   > Modified Time: 2016年12月13日 星期二 20时14分30秒
 ************************************************************************/

#include <stdio.h>

#define MY_STR "+--1234567"
//#define MY_STR "1"

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
	int exp = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int symbol = 0;

	while('\0' != *str)
	{
		if('-' == *str)
		{
			symbol++;
		}
		str++;
		i++;
	}
	
	str--;
	i--;

	printf("i = %d, *str = %c\n", i, *str);

	while(('-' != *str) && ('+' != *str) && (0 <= i))
	{
		for(k = 0, exp = 1; k < j; k++)
		{
			exp *= 10;	
		}
		printf("exp = %d\n", exp);
		result += ((*str-'0')*exp);

		str--;
		i--;
		j++;
	}

	if(symbol%2)
	{
		return (0-result);
	}
	else
	{
		return (result);
	}
}
