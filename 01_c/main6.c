#include <stdio.h>
#define EPS 0.00000001

float bar(float n)
{
	if(((n - 1.0f) >= -EPS) && ((n - 1.0f) <= EPS))
	{
		return n;
	}
	else
	{
		return n*(bar(n));
	}
	

}

float foo(float n)
{
	if(((n - 1.0f) >= -EPS) && ((n - 1.0f) <= EPS))
	{
		return n;
	}
	else
	{
		return 1.0f/(bar(n)) + foo(n - 1.0f);
	}
}


int main(void)
{
	float n = 0;
	
	scanf("%f", &n);
	
	printf("result = %f \n", foo(n));	

	

	return 0;
}
