#pragma comment(lib,"ws2_32.lib")
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<winsock2.h>

#ifndef INADDR_NONE 
#define INADDR_NONE 0xffffffff
#endif

void errexit(const char *,...){
}

SOCKET connectSock(const char *host,const char *service,const char *transport){
	hostent *phe;
	servent *pse;
	protoent *ppe;
sockaddr_in sin;
int s,type;
memset(&sin,0,sizeof(sin));
sin.sin_family=AF_INET;

if(pse=getservbyname(service,transport))
sin.sin_port=pse->s_port;
else if((sin.sin_port=htons((u_short)atoi(service)))==0)
errexit("cant't get \"%s\" service entry\n",service);
return 0;
}