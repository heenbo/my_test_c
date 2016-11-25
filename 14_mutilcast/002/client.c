#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
//#include "Utility.h"
//多播发送者 使用例子 ./Sender 224.0.0.2 8888 hehe你好 5
int main(int argc, char** argv) {
  
    if(argc<4||argc>5)
    {
        //接收多播地址和端口
        DieWithUserMessage("param","<multicast address> <port> <send string><TTL>");       
    }
    char * multicastIPString=argv[1];
    char* service=argv[2];
    char* sendString=argv[3];
    size_t senStringLen=strlen(sendString);
    if(senStringLen>MAXSTRINGLENGTH)
    {
        DieWithUserMessage("string too long ",sendString);
    }
    //生命周期
    int multicastTTL=(argc==5)?atoi(argv[4]):1;
    //配置想要的地址结构
    struct addrinfo addr_criteria;
    memset(&addr_criteria,0,sizeof(addr_criteria));
    addr_criteria.ai_socktype=SOCK_DGRAM;
    addr_criteria.ai_family=AF_UNSPEC;
    addr_criteria.ai_protocol=IPPROTO_UDP; //
    addr_criteria.ai_flags |=AI_NUMERICHOST;
    
    struct addrinfo*multicastAddr;
    //获取地址信息
    int ret=getaddrinfo(multicastIPString,service,&addr_criteria,&multicastAddr);
    if(ret!=0)
        DieWithUserMessage("getaddrinfo() failed!",gai_strerror(ret));
    //建立socket
    int sock=socket(multicastAddr->ai_family,multicastAddr->ai_socktype,multicastAddr->ai_protocol);
    if(sock<0)
        DieWithSystemMessage("socket() failed!");
    if(multicastAddr->ai_family==AF_INET6)
    {
        //如果是ip6,设置socket，允许发送多播和设置生命周期
        if(setsockopt(sock,IPPROTO_IPV6,IPV6_MULTICAST_HOPS,&multicastTTL,sizeof(multicastTTL))<0)
        {
            DieWithSystemMessage("setsockopt() failed!");
        }
    }else if(multicastAddr->ai_family=AF_INET)
    {
        //如果时ip4,设置socket，允许发送多播和设置生命周期
        u_char mcTTL=(u_char)multicastTTL;
        if(setsockopt(sock,IPPROTO_IP,IP_MULTICAST_TTL,&mcTTL,sizeof(mcTTL))<0)
        {
            DieWithSystemMessage("setsockopt() failed!");
        }     
    }else{
        DieWithUserMessage("unable to set TTL","invalid address family");
    }
    printf("multicastIPString:%s  service:%s  sendString:%s \n",multicastIPString,service,sendString);
    for(;;)
    {
        //循环发送数据
        ssize_t numBytes=sendto(sock,sendString,senStringLen,0,multicastAddr->ai_addr,multicastAddr->ai_addrlen);
        if(numBytes<0)
        {
            DieWithSystemMessage("sendto() failed!");
        }else if(numBytes!=senStringLen)
        {
            DieWithUserMessage("sendto()","sent unexpected number of bytes");
                    
        }
        sleep(3);
    }
    return (EXIT_SUCCESS);
}
