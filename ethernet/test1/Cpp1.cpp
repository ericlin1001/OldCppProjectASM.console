#include<winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream.h>
//
#include<sys/types.h>
//
#define DEFAULT_PORT 4000
//
int main(){
	SOCKET mysocket=socket(AF_INET,SOCK_DGRAM,0);
	sockaddr_in myaddr;
	myaddr.sin_family=AF_INET;
	myaddr.sin_port=htons(DEFAULT_PORT);
	myaddr.sin_addr=INADDR_ANY;//0
	bind(mysocket,(sockaddr*)&myaddr,sizeof(addr));
	sendto();
	accept();
	setsockopt(s,,,,);
	close(mysocket);
	return 0;
}
