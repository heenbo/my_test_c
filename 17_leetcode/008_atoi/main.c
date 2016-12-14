/*************************************************************************
 *   > File Name: main.c
 *   > Author: heenbo
 *   > Mail: 379667345@qq.com 
 *   > Created Time:  2016年12月13日 星期二 19时29分32秒
 *   > Modified Time: 2016年12月14日 星期三 13时30分31秒
 ************************************************************************/

#include <stdio.h>

//#define MY_STR "   +1234a567"
//#define MY_STR "   +-1234a567"
//#define MY_STR "1"
//#define MY_STR "2147483648"
//#define MY_STR "-2147483649"
//#define MY_STR "   - 321"
//#define MY_STR " b11228552307"
//#define MY_STR "   010"
//#define MY_STR "9223372036854775809"
//#define MY_STR "-9223372036854775809"
#define MY_STR "18446744073709551617"
#define INT_MAX 2147483647
#define INT_MIN -2147483648

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
	long long result = 0;
	int i = 0;
	int j = 0;
	long long exp = 0;
	int symbol_count = 0;

	while((!(((*str) - '0' <= 9) && ((*str) - '0' >= 0))) && (*str != '\0'))
	{
		//if((*str == '-') || (*str == '+'))
		if((!(((*str) - '0' <= 9) && ((*str) - '0' >= 0))) && (*str != ' '))
		{
			if((*str != '-') && (*str != '+'))
			{
				return 0;
			}
			symbol_count ++;
			if(symbol_count > 1)
			{
				printf("line:%d, result= %lld\n", __LINE__, result);
				return 0;
			}
			if(!(((str[1]) - '0' <= 9) && ((str[1]) - '0' >= 0)))
			{
				printf("line:%d, result= %lld\n", __LINE__, result);
				return 0;
			}
		}
		str++;
	}

	while((((*str) - '0' <= 9) && ((*str) - '0' >= 0)))
	{
		str++;
		j++;
		if(j > 10)
		{
			break;
		}
	}

	str--;
	while((((*str) - '0' <= 9) && ((*str) - '0' >= 0)))
	{
		for(j = 0, exp = 1; j < i; j++)
		{
			exp *= 10;
		}
		result += ((*str-'0')*exp);
		str--;
		i++;
	}

	printf("result= %lld\n", result);
	if('-' == *str)
	{
		if(result < 0)
		{
			result = 0 - result;
		}
		printf("line:%d, result= %lld\n", __LINE__, result);
		if((0 - result) < INT_MIN)
		{
			printf("line:%d, result= %lld\n", __LINE__, result);
			return INT_MIN;
		}
		else
		{
			printf("line:%d, result= %lld\n", __LINE__, result);
			return (0 - result);
		}
	}
	else
	{
		if(result < 0)
		{
			result = 0 - result;
		}
		printf("line:%d, result= %lld\n", __LINE__, result);
		if(result > INT_MAX)
		{
			return INT_MAX;
		}
		else
		{
			return result;
		}
	}
}
