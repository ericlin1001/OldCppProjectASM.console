#include "CServer.h"
#include "CServer.h"
#include "CServer.h"
//
int CServer::maxClient=8;
SOCKET CServer::listenSock=NULL;
sockaddr_in CServer::localAddr={0};
HANDLE CServer::hWaitThread=NULL;
bool CServer::bWait=true;
unsigned short CServer::port=DEFAULT_PORT;
SockInfo *CServer::clientArr=NULL;
HANDLE *CServer::clientThreads=NULL;
ClientID CServer::pCurClient=-1;
pFilterFun *CServer::filters=NULL;
bool CServer::startWait(){
	bWait=true;
	DWORD dwThread;
	if(hWaitThread==NULL){
		hWaitThread=CreateThread(NULL,0,&waitThread,(LPVOID)0,0,&dwThread);
		if(hWaitThread==NULL){
			cout<<"CreateThread()in startWait() failed!"<<endl;
			return false;
		}
		cout<<"create waitThread for waitforLogin."<<endl;
	}
	return true;
}
 int  CServer::init(int iport){
	port=iport;
	clientArr=new SockInfo[maxClient];
	clientThreads=new HANDLE[maxClient];
	filters=new pFilterFun[maxClient];
	for(int i=0;i<maxClient;i++){
		filters[i]=NULL;
	}
	pCurClient=-1;
	hWaitThread=NULL;
	bWait=true;
	//
	WSADATA wsd;
	if(WSAStartup(MAKEWORD(2,2),&wsd)!=0){
		printf("Failed to load WinSock!\n");return 1;
	}
	listenSock=socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
	if(listenSock==SOCKET_ERROR){
		cout<<"socket() failed! can't create listenSock."<<endl;
		return 1;
	}
	//
	localAddr.sin_family=AF_INET;
	localAddr.sin_port=htons(port);
	localAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	//
	if(bind(listenSock,(struct sockaddr *)&localAddr,sizeof(localAddr))==-1){
		cout<<"bind() failed:"<<WSAGetLastError()<<endl;
	}
	listen(listenSock,maxClient);
	return 0;
}
void CServer::stopWait(){
	bWait=false;
	if(hWaitThread!=NULL){
		//???
		CloseHandle(hWaitThread);
		TerminateThread(hWaitThread,0);
	}
}
void CServer::error(int t){
	cout<<"error:"<<t<<endl;
	exit(t);
}
CServer::~CServer(){
	closesocket(listenSock);
	WSACleanup();
	cout<<"exiting...server."<<endl;
}
unsigned long WINAPI CServer::waitThread(LPVOID pParma){
	while(bWait){
		if(pCurClient<maxClient-1){
			SockInfo clientInfo;
			if(waitForLogin(&clientInfo)){
				clientArr[pCurClient]=clientInfo;
				DWORD dwThread;
				clientThreads[pCurClient]=CreateThread(NULL,0,&ClientThread,(LPVOID)&clientInfo,0,&dwThread);
				if(clientThreads[pCurClient]==NULL){
					continue;
				}
				cout<<"Create a new thread for clinet"<<endl;
				CloseHandle(clientThreads[pCurClient]);
				
			}
		}
	}
	return 0;
}
bool CServer::waitForLogin(SockInfo *pClientInfo){
	int lenClientAddr=sizeof(pClientInfo->addr);
	pClientInfo->socket=accept(listenSock,(struct sockaddr *)&(pClientInfo->addr),&lenClientAddr);
	if(pClientInfo->socket==INVALID_SOCKET){
		cout<<"accept() failed:"<<endl;
		return false;
	}
	pClientInfo->addrToa();
	pCurClient++;
	pClientInfo->id=pCurClient;
	return true;
}
unsigned long WINAPI CServer::ClientThread(LPVOID pParma){
	SockInfo *pClientInfo=(SockInfo *)pParma;
	SOCKET clientSock=pClientInfo->socket;
	ClientID clientID=pClientInfo->id;
	int lenRec;
	char buffer[DEFAULT_BUFFER+1];
	while(1){
		lenRec=recv(clientSock,buffer,DEFAULT_BUFFER,0);//×èÈû.
		if(lenRec==0) break;
		else if(lenRec==SOCKET_ERROR){
			cout<<"recv() fialed:"<<WSAGetLastError()<<endl;
			break;
		}else if(lenRec>0){
			//buffer[lenRec]='\0';
			//cout<<"reveive from client: "<<buffer<<endl;
			if(filters[clientID]!=NULL){
				filters[clientID](buffer,lenRec);
			}
			//Beep(5000,175);
		}else{
			cout<<"Error:in recv():lenRec <-1"<<endl;
			break;
		}
	}
	return 0;
}


