#include <stdio.h>
#include <math.h>

float input[] = {0.001202, 0.001000, 0.002089, 0.004365, 0.009120, 0.019055, 0.039811, 0.083176, 0.131826, 0.190546, 0.275432, 0.398107, 0.575440, 0.831764, 1.000000,};

int main(void)
{
	int i = 0;
	int len = sizeof(input)/sizeof(input[0]);
	for(i = 0; i < len; i ++)
	{
//		printf("log10f(%f)=%f\n", input[i], -log10f(input[i]));
		//printf("log10f(%f)=%f\n", input[i], -log2f(input[i]));
//		printf("log10f(%f)=%f\n", input[i], -logf(input[i]));
//		printf("log10f(%f)=%f\n", input[i], -log1pf(input[i]));
//		printf("%f -> %f\n", input[i], expf(input[i] / 20.0 * logf(10.0)));
//		printf("%f -> %f\n", input[i], -(20.0 * logf(input[i]) / logf(10.0)));
		printf("%f -> %f\n", input[i], -(17.0 * logf(input[i]) / logf(10.0)));
	}	

	printf("\n");
	
	for(i = 50; i < 127; i ++)
	{
		printf("i = %d  ->  %f \n", i, (float)expf((-(127.0-i))/20.0*logf(10.0)));
	}
	return 0;

}
