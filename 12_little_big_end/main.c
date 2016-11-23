/*************************************************************************
 *   > File Name: main.c
 *   > Author: heenbo
 *   > Mail: 379667345@qq.com 
 *   > Created Time:  2016年11月16日 星期三 09时53分53秒
 *   > Modified Time: 2016年11月16日 星期三 09时55分16秒
 ************************************************************************/

#include <stdio.h>

int main(void)
{

	static union
	{
		char c[4];
		unsigned long l;
	} endian_test = { 'l', '?', '?', 'b'};

#define ENDIANNESS ((char)endian_test.l)
	printf("ENDIANNESS:%c\n", ENDIANNESS); // Output "ENDIANNESS:l"

	return 0;
}
