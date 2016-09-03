#ifndef CServer_h
#define CServer_h 
#include<winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream.h>
#define DEFAULT_PORT 5150
#define DEFAULT_BUFFER 400
typedef void (*pFilterFun)(char *,int);
struct NetAddr{
	char *ip;
	int port;
};
typedef int ClientID;
class SockInfo{
public:
	int id;
	sockaddr_in addr;
	SOCKET socket;
	char ip[100];
	int port;
	void addrToa(){
		port=ntohs(addr.sin_port);
		strcpy(ip,inet_ntoa(addr.sin_addr));
	}
	void aToAddr(){
		addr.sin_family=AF_INET;
		addr.sin_port=htons(port);
		addr.sin_addr.s_addr=inet_addr(ip);
	}
	SockInfo(){}
	~SockInfo(){}
	SockInfo(SockInfo &s){
		port=s.port;
		strcpy(ip,s.ip);
		socket=s.socket;
		aToAddr();
	}
	SockInfo & operator=(SockInfo &s){
		port=s.port;
		strcpy(ip,s.ip);
		socket=s.socket;
		aToAddr();
		return *this;
	}
};

class CServer{
public:
	CServer(){}
	static bool startWait();
	static void stopWait();
	static void error(int t);
	static int  init(int iport=DEFAULT_PORT);
	~CServer();
	static unsigned long WINAPI waitThread(LPVOID pParma);
	bool addListener(ClientID clientID,pFilterFun filter){
		filters[clientID]=filter;
	}
protected:
	static int maxClient;
	static SOCKET listenSock;
	static sockaddr_in localAddr;
	static HANDLE hWaitThread;
	static bool bWait;
	static unsigned short port;
	static SockInfo *clientArr;
	static HANDLE *clientThreads;
	static ClientID pCurClient;
	static pFilterFun *filters;
private:
	static bool waitForLogin(SockInfo *pClientInfo);
	static unsigned long WINAPI ClientThread(LPVOID pParma);
};

#endif