#include <stdio.h>

int main(void)
{
	char buf_send_to_nd[1024] = {0};
	sprintf(buf_send_to_nd, "ubus send ubus_nd_listen \"{\\\"sender\\\":\\\"wpa_supplicant\\\", \\\"cmd\\\":\\\"wrong_key\\\"}\"");
	system(buf_send_to_nd);
	printf("buf_send_to_nd:%s\n", buf_send_to_nd);



	return 0;
}

