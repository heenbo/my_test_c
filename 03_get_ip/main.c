#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	struct ifaddrs *ifaddr, *ifa;
	int family, ret;
	char host[NI_MAXHOST];

	if (getifaddrs(&ifaddr) == -1)
	{
		perror("getifaddrs");
	}

	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
	{
		if (ifa->ifa_addr == NULL)
		{
			continue;
		}
		family = ifa->ifa_addr->sa_family;

	//	if ((0 == strcmp(ifa->ifa_name, "eth0")) && (family == AF_INET))
		if ((0 == strcmp(ifa->ifa_name, "wlan0")) && (family == AF_INET))
	//	if ((0 == strcmp(ifa->ifa_name, "lo")) && (family == AF_INET))
		{
			ret = getnameinfo(ifa->ifa_addr,
					(family == AF_INET) ? sizeof(struct sockaddr_in) :
					sizeof(struct sockaddr_in6),
					host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
			if (ret != 0)
			{
				printf("getnameinfo() failed: %s\n", gai_strerror(ret));
			}
			printf("get IP address: %s\n", host);
		}
	}
	if(0 == strncmp(host, "192.168.0.1", 11))
	{
		printf("===========\n");	
	}


	freeifaddrs(ifaddr);
}

