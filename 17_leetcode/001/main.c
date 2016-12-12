/*************************************************************************
 *   > File Name: main.c
 *   > Author: heenbo
 *   > Mail: 379667345@qq.com 
 *   > Created Time:  2016年12月12日 星期一 15时49分31秒
 *   > Modified Time: 2016年12月12日 星期一 20时34分08秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target)
{
	int * result = NULL;
	int i = 0;
	int j = 0;

	if(0 <= target)
	{
		for(i = 0; i < numsSize-1; i++)
		{
			if(nums[i] <= target)
			{
				for(j = i+1; j < numsSize; j++)
				{
					if(target == (nums[i] + nums[j]))
					{
						result = (int *)malloc(2*sizeof(int));
						result[0] = i;
						result[1] = j;
						return result;
					}
				}
			}
		}
	}
	else
	{
		for(i = 0; i < numsSize-1; i++)
		{
			if(nums[i] >= target)
			{
				for(j = i+1; j < numsSize; j++)
				{
					if(target == (nums[i] + nums[j]))
					{
						result = (int *)malloc(2*sizeof(int));
						result[0] = i;
						result[1] = j;
						return result;
					}
				}
			}
		}

	}
	return result;
}

int main(int argc, char * argv[])
{
	//int nums[] = {2, 7, 11, 15};
	int nums[] = {-1, -2, -3, -4, -5};
	//int target = 9;
	int target = -8;

	int * result = NULL;

	result = twoSum(nums, sizeof(nums)/sizeof(nums[0]), target);

	printf("%d   %d\n", result[0], result[1]);
	free(result);
	return 0;
}
