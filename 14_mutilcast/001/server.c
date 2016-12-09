/*
 *dcast_server.c - 多播服务程序
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>


#define MCAST_PORT 8789
//#define MCAST_ADDR "224.0.0.1"    /*一个局部连接多播地址，路由器不进行转发*/
#define MCAST_ADDR "239.255.255.250"    /*一个局部连接多播地址，路由器不进行转发*/
#define MCAST_DATA "hahahah BROADCAST TEST DATA"            /*多播发送的数据*/
#define MCAST_INTERVAL 5                            /*发送间隔时间*/

int main(int argc, char * argv[])
{
	int s;
	struct sockaddr_in mcast_addr;
	s = socket(AF_INET, SOCK_DGRAM, 0);         /*建立套接字*/
	if (s == -1)
	{
		perror("socket()");
		return -1;
	}

	memset(&mcast_addr, 0, sizeof(mcast_addr));/*初始化IP多播地址为0*/
	mcast_addr.sin_family = AF_INET;                /*设置协议族类行为AF*/
	mcast_addr.sin_addr.s_addr = inet_addr(MCAST_ADDR);/*设置多播IP地址*/
	mcast_addr.sin_port = htons(MCAST_PORT);        /*设置多播端口*/

	int iii = 0;
	char buf[100] = {0};
	/*向多播地址发送数据*/
	while(1) {
		iii++;
		sprintf(buf, "hahahaha %d\n", iii);
		int n = sendto(s,                           /*套接字描述符*/
				buf,     /*数据*/
				strlen(buf),    /*长度*/
				0,
				(struct sockaddr*)&mcast_addr,
				sizeof(mcast_addr)) ;
		if( n < 0)
		{
			perror("sendto()");
			return -2;
		}      

		sleep(MCAST_INTERVAL);                          /*等待一段时间*/
	}

	return 0;
}
