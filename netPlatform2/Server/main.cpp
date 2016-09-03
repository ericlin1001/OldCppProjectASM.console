
#include "../definedMess.h"
#include<iostream>
#include<cstring>
#include<vector>
#include<winsock2.h>
#include<cstdlib>
#include<fstream>
using namespace std;
//
#define Trace(m) cout<<#m"="<<m<<endl;

class CClientInfo{
public:
	SOCKET s;
	char ip[20];
	int id;
	char showName[MAX_LEN_SHOWNAME];
	char user[MAX_LEN_USERNAME];//connect with database;
	int certification;
};
int nextID;
class CServer{
protected:
	SOCKET listenSock;
	sockaddr_in localAddr;
	//
	vector<CClientInfo> clientList;
	int numClients;
	
public:
	CServer(){
		WSADATA wsd;
		if(WSAStartup(MAKEWORD(2,2),&wsd)!=0){
			cout<<"Failed to load WinSock!\n";return;
		}
		//
		numClients=0;
		nextID=1;
		
	}
	CClientInfo *getClient(int id){
		for(vector<CClientInfo>::iterator i=clientList.begin();i!=clientList.end();i++){
			if(i->id==id){
				return i;
			}
		}
		return NULL;
	}
	int getNextID(){
		return nextID++;
	}
	int init(unsigned short port,int maxlisten=10){
		listenSock=socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
		if(listenSock==SOCKET_ERROR){
			cout<<"socket() failed! can't create listenSock."<<endl;
			return MYERROR;
		}
		localAddr.sin_family=AF_INET;
		localAddr.sin_port=htons(port);
		localAddr.sin_addr.s_addr=htonl(INADDR_ANY);
		if(bind(listenSock,(struct sockaddr *)&localAddr,sizeof(localAddr))==-1){
			cout<<"bind() failed:"<<endl;return MYERROR;
		}
		listen(listenSock,maxlisten);
		return MYSUCCESS;
	}
	struct SockInfo{
		char ip[20];
		SOCKET s;
		CServer *server;
	};
	void start(){
		while(1){
			sockaddr_in clientAddr;
			int lenClientAddr=sizeof(clientAddr);
			SOCKET clientSock=accept(listenSock,(struct sockaddr *)&clientAddr,&lenClientAddr);
			if(clientSock==INVALID_SOCKET){
				cout<<"accept() failed:"<<endl;
				break;
			}
			SockInfo si;
			strcpy(si.ip,inet_ntoa(clientAddr.sin_addr));
			si.s=clientSock;
			DWORD dwThread;
			HANDLE hThread=CreateThread(NULL,0,&threadFun,(LPVOID)&si,0,&dwThread);
			if(hThread==NULL){
				cout<<"CreateThread() failed!"<<endl;
				break;
			}
			CloseHandle(hThread);
		}
	}
	bool isRegisterUser(char *user,char *pass){
		ifstream infile;
		infile.open(FILE_USERPASS);
		if(infile.fail()){
			cerr<<"can't open "FILE_USERPASS<<endl;
			return false;
		}
		struct{
			char prefix[5];//user:
			char user[MAX_LEN_USERNAME];
		}u;
		struct{
			char prefix[5];//pass:
			char pass[MAX_LEN_PASS];
		}p;
		infile>>(char *)&u>>(char *)&p;
		while(!infile.eof()){
			//cout<<u.prefix<<"\t"<<p.prefix<<endl;
			if(strcmp(u.user,user)==0 && strcmp(p.pass,pass)==0){
				return true;
			}
			infile>>(char *)&u>>(char *)&p;
		}
		return false;
	}
	static unsigned long WINAPI threadFun(LPVOID lParam){
		cout<<"create an clinet's thread"<<endl;
		SockInfo *hsi=(SockInfo *)lParam;
		CServer * s=hsi->server;
		SOCKET cs=hsi->s;
		cout<<hsi->ip<<" connect!"<<endl;
		//
		Message m;
		Trace(s->getNextID());
		while(1){
			if(s->recvMess(cs,m)==MYERROR){
				cout<<"lost the client"<<endl;break;
			}
			Trace(s->getNextID());
			//m.h.print();
			switch(m.h.type){
			case MT_LOGIN:
				Trace(s->getNextID());
				cout<<"MT_LOGIN"<<endl;
				cout<<"user:"<<m.d.login.user<<endl
					<<"pass:"<<m.d.login.pass<<endl;
				if(s->isRegisterUser(m.d.login.user,m.d.login.pass)){
					m.d.login.isSuccess=true;
					m.d.login.id=s->getNextID();
					m.d.login.certification=rand();
					m.h.dataLen=sizeof(m.d.login);
				}else{
					m.d.login.isSuccess=false;
				}
				//
				m.h.from=SERVER_ID;
				m.h.to=m.d.login.id;
				sendMess(cs,m);
				break;
			case MT_LOGOFF:
				cout<<"MT_LOGOFF"<<endl;
				m.d.logoff.isSuccess=true;
				m.h.from=SERVER_ID;
				sendMess(cs,m);
				break;
			case MT_CHAT:
				cout<<"MT_CHAT"<<endl;
				cout<<"chat text:"<<m.d.chat.text<<endl;
				strcpy(m.d.chat.prefix,"you say:");
				
				m.h.from=SERVER_ID;
				sendMess(cs,m);
				break;
			default:
				cout<<"MYERROR:in client not this type mess."<<endl;
				break;
			}
		}
		cout<<"exiting the thread"<<endl;
		return 0;
	}
	~CServer(){
		closesocket(listenSock);
		WSACleanup();
	}
	
	protected:
		static int sendMess(SOCKET s,void* m,int len){
			//send m to server.
			return send(s,(char*)m,len,0);
		}
		static int recvMess(SOCKET s,void *m,int len){
			//cout<<"expect bytes:"<<len<<endl;
			int leftLen=len;
			int recvLen=0;
			while(leftLen>0){
				recvLen=recv(s,(char *)m,len,0);
				if(recvLen==SOCKET_ERROR){
					return MYERROR;
				}
				leftLen-=recvLen;
			}
			//cout<<"recv bytes:"<<len<<endl;
			return MYSUCCESS;
			//there had better to start a timmer to ensure the server is alive.
		}
		static int recvMess(SOCKET s,Message &m){
			if(recvMess(s,&m.h,sizeof(m.h))==MYERROR){
				return MYERROR;
			}
			if(recvMess(s,&m.d,m.h.dataLen)==MYERROR){
				return MYERROR;
			}
			return MYSUCCESS;
		}
		static int sendMess(SOCKET s,Message &m){
			sendMess(s,&m,sizeof(m.h)+m.h.dataLen);
			return 0;
		}
};


int main(){
	CServer s;
	s.init(DEFAULT_PORT);
	s.start();
	cout<<"hello"<<endl;
	return 0;
}
