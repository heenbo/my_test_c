#include <stdio.h>
#include <time.h>

union
{
	unsigned char time_char[4];
	unsigned int time_int;
}Segment_time;

int main(void)
{
	time_t t = time(NULL);
	struct tm * current_time = localtime(&t);
	sprintf(Segment_time.time_char, "%d%d%d%d", (current_time->tm_hour)/10, (current_time->tm_hour)%10, (current_time->tm_min)/10, (current_time->tm_min)%10);	

	printf("hour:%d ,min: %d\n", current_time->tm_hour, current_time->tm_min);
	printf("time int = %u\n", Segment_time.time_int);
	printf("time char = %s\n", Segment_time.time_char);
	printf("h1:%c h2:%c m1:%c m2:%c\n", Segment_time.time_char[0], Segment_time.time_char[1], Segment_time.time_char[2], Segment_time.time_char[3]);
	return 0;
}
