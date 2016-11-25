#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
//#include "Utility.h"
//多播接收 使用例子 ./sender 224.0.0.2 8888 hehae 5
int main(int argc, char** argv) {
    //参数判断
    if (argc != 3)
        DieWithUserMessage("param", "<multicast address> <port>");
    char * multicastAddrString = argv[1];
    char* service = argv[2];
    //配置想要的地址结构
    struct addrinfo addr_criteria;
    memset(&addr_criteria, 0, sizeof (addr_criteria));
    addr_criteria.ai_family = AF_UNSPEC;
    addr_criteria.ai_socktype = SOCK_DGRAM;
    addr_criteria.ai_protocol = IPPROTO_UDP;
    addr_criteria.ai_flags = AI_NUMERICHOST;

    struct addrinfo *multicastAddr;
    //获取多播地址
    int ret = getaddrinfo(multicastAddrString, service, &addr_criteria, &multicastAddr);
    if (ret != 0)
        DieWithUserMessage("getaddrinfo() failed!", gai_strerror(ret));
    //建立sockset
    int sock = socket(multicastAddr->ai_family, multicastAddr->ai_socktype, multicastAddr->ai_protocol);
    if (sock < 0)
        DieWithSystemMessage("socket() failed!");
    //绑定端口
    if (bind(sock, multicastAddr->ai_addr, multicastAddr->ai_addrlen) < 0) {
        DieWithSystemMessage("bind() failed!");
    }
    if (multicastAddr->ai_family == AF_INET6) {
        //如果时IPV6，则加入IPV6多播组
        struct ipv6_mreq joinRequest;
        //拷贝
        memcpy(&joinRequest.ipv6mr_multiaddr, &((struct sockaddr_in6*) multicastAddr->ai_addr)->sin6_addr, sizeof (struct in6_addr));
        joinRequest.ipv6mr_interface = 0;
        puts("Joining ipv6 mulicast group..");
        //设置socket信息
        if (setsockopt(sock, IPPROTO_IPV6, IPV6_JOIN_GROUP, &joinRequest, sizeof (joinRequest)) < 0) {
            DieWithSystemMessage("setsockopt() failed!");
        }
    } else if (multicastAddr->ai_family == AF_INET) {
        //如果时ipv4,则加入多播组
        struct ip_mreq ip_joinRequest;
        ip_joinRequest.imr_multiaddr = ((struct sockaddr_in *) multicastAddr->ai_addr)->sin_addr;
        ip_joinRequest.imr_interface.s_addr = 0;
        printf("Joining ipv4 multicast group...\n");
        //设置socket信息　
        if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &ip_joinRequest, sizeof (ip_joinRequest)) < 0) {
            DieWithSystemMessage("setsockopt() failed!");
        }
    } else {
        DieWithSystemMessage("unknown address family!");
    }
    //清理
    freeaddrinfo(multicastAddr);
    char* recvString[MAXSTRINGLENGTH + 1];
    //接收数据
    int recvStringLen = recvfrom(sock, recvString, MAXSTRINGLENGTH, 0, NULL,0);
    if (recvStringLen < 0)
        DieWithSystemMessage("recvfrom() failed!");
    recvString[recvStringLen] = '\0';
    printf("Received:%s\n", recvString);
    close(sock);
    return (EXIT_SUCCESS);
}
