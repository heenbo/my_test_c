#include <stdio.h>
#include <string.h>


int main(void)
{
	int ret = 0;
	char buf[10] = {0};
	char buf2[10] = {0};
	
	printf("ret: %d\n", ret);
	strcpy(buf, buf2);

	printf("ret: %d\n", ret);
	ret = strncmp("192.168.0.1", buf2, 11);	
	printf("ret: %d\n", ret);

	ret = strncmp("192.168.0.1", "192.168.0.1", 11);	
	printf("ret: %d\n", ret);

	ret = strncmp("192.168.0.101", "192.168.0.1", 11);	
	printf("ret: %d\n", ret);

	ret = strncmp("192.168.0.1", "192.168.0.101", 11);	
	printf("ret: %d\n", ret);

	return 0;
}
