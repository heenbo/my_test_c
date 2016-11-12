#include <stdio.h>

float bar(float n)
{
	if(n == 1)
	{
		return n;
	}
	else
	{
		return n*(bar(n - 1));
	}
}

float foo(float n)
{
	if(n == 1)
	{
		return n;
	}
	else
	{
		return 1.0f/(bar(n)) + foo(n - 1);
	}
}

int main(void)
{
	float n = 0;
	printf("输入一个整数：____________\b\b\b\b\b\b\b\b\b");
	scanf("%f", &n);
	printf("1+1/2!+1/3!+...+1/n! = %f \n", foo(n));	

	return 0;
}
