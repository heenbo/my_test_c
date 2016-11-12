#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum _VIDEO_CODE_TYPE
{
        VIDEO_CODE_TYPE_DLNA_HTTP,
        VIDEO_CODE_TYPE_WEBVIEW,
        VIDEO_CODE_TYPE_FILE,
}VIDEO_CODE_TYPE;

typedef struct _VIDEO_CODE_URL_
{
        int code;
        int type;
        char *url;
}VIDEO_CODE_URL;

int main(void)
{
	FILE * fp = NULL;
	fp = fopen("./file.txt", "r");
	int int1 = 0;
	char buf1[1024] = {0};
	char buf2[1024] = {0};
	char buf3[1024] = {0};
	char *endptr;

#if 1
	while(0 < fscanf(fp, "%s %s %s\n", buf1, buf2, buf3))
	{
		printf("result: buf1:%s buf2:%s buf3%s\n", buf1, buf2, buf3);
		//printf("result:buf1:%f\n", atof(buf1));
		printf(">>>>>>>>>>>>>>>>>>result:buf1:%f\n", strtof(buf1, &endptr));
		printf("endptr:%s\n", endptr);
	}
#elif 0
	while(0 < fscanf(fp, "%s %s\n", buf1, buf2))
	{
		printf("result: buf1:%s buf2:%s \n", buf1, buf2);
	}
#elif 0
	while(0 < fscanf(fp, "%d %s %s\n", &int1, buf2, buf3))
	{
		printf("result: int1:%d buf2:%s buf3%s\n", int1, buf2, buf3);
	}
#endif
	
	fclose(fp);
	return 0;
}
