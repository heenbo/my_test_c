/*************************************************************************
 *   > File Name: main.c
 *   > Author: heenbo
 *   > Mail: 379667345@qq.com 
 *   > Created Time:  2016年12月13日 星期二 19时29分32秒
 *   > Modified Time: 2016年12月14日 星期三 13时44分51秒
 ************************************************************************/

#include <stdio.h>

//#define MY_STR "   +1234a567"
//#define MY_STR "   +-1234a567"
#define MY_STR "1"
//#define MY_STR "2147483648"
//#define MY_STR "-2147483649"
//#define MY_STR "   - 321"
//#define MY_STR " b11228552307"
//#define MY_STR "   010"
//#define MY_STR "9223372036854775809"
//#define MY_STR "-9223372036854775809"
//#define MY_STR "18446744073709551617"
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

int myAtoi(char* str) 
{
    long result = 0;
    int i = 0;
    long exp = 1;
    
    while((!(((*str) - '0' <= 9) && ((*str) - '0' >= 0))) && (*str != '\0'))
    {
        if(*str != ' ')
        {
            if((*str != '-') && (*str != '+'))
            {
                return 0;
            }
            else
            {
                i ++;
                if(i > 1)
                {
                    return 0;
                }
                if(!(((str[1]) - '0' <= 9) && ((str[1]) - '0' >= 0)))
                {
                    return 0;
                }
            }
        }
        str++;
    }

    i = 0;
    while((((*str) - '0' <= 9) && ((*str) - '0' >= 0)))
    {
        str++;
        i++;
        if(i > 10)
        {
            break;
        }

    }

    str--;
    while((((*str) - '0' <= 9) && ((*str) - '0' >= 0)))
    {
        result += ((*str-'0')*exp);
        exp *= 10;
        str--;
    }


    if('-' == *str)
    {
        if((0 - result) < INT_MIN)
        {
            return INT_MIN;
        }
        else
        {
            return (0 - result);
        }
    }
    else
    {
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
