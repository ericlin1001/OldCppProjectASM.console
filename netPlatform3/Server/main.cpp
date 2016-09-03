

#include<iostream>
#include<cstring>
#include<vector>
#include<winsock2.h>
#include<cstdlib>
#include<fstream>
using namespace std;
//
#include "../definedMess.h"
#define Trace(m) cout<<#m"="<<m<<endl;
//
class CBasicServer{
protected:
	SOCKET listenSock;
	sockaddr_in localAddr;
public:
	CBasicServer(){
		WSADATA wsd;
		if(WSAStartup(MAKEWORD(2,2),&wsd)!=0){
			cout<<"Failed to load WinSock!\n";return;
		}
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
	int wait(SOCKET &clientSock,char *ip,unsigned short &port){
		sockaddr_in clientAddr;
		int lenClientAddr=sizeof(clientAddr);
		clientSock=accept(listenSock,(struct sockaddr *)&clientAddr,&lenClientAddr);
	
		if(clientSock==INVALID_SOCKET){
			cout<<"accept() failed:"<<endl;
			return MYERROR;
		}
		strcpy(ip,inet_ntoa(clientAddr.sin_addr));
		port=ntohs(clientAddr.sin_port);
		return MYSUCCESS;
	}
	~CBasicServer(){
		closesocket(listenSock);
		WSACleanup();
	}
	static int sendMess(SOCKET s,void* m,int len){
		//send m to server.
		return send(s,(char*)m,len,0);
	}
	static int recvMess(SOCKET s,void *m,int len){
#define _recvMess_test
#ifdef recvMess_test 
		cout<<"expect bytes:"<<len<<endl;
#endif
		int leftLen=len;
		int recvLen=0;
		while(leftLen>0){
			recvLen=recv(s,(char *)m,len,0);
			if(recvLen==SOCKET_ERROR){
				return MYERROR;
			}
			leftLen-=recvLen;
		}
		#ifdef recvMess_test 
		cout<<"recv bytes:"<<len<<endl;
#endif
		return MYSUCCESS;
		//there had better to start a timmer to ensure the server is alive.
	}
};

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

class CClientInfo{
public:
	SOCKET id;//u_int
	char ip[20];
	unsigned  short port;
	int certification;//no use.
	bool isLogin;
	//
	char showName[MAX_LEN_SHOWNAME];
	char user[MAX_LEN_USERNAME];//connect with database;
	bool login(char *userName,char *pass){
		if(isRegisterUser(userName,pass)){
			strcpy(user,userName);
			isLogin=true;
			return true;
		}
		return false;
	}
	void print(){
		cout<<"user:"<<user<<" id:"<<id<<endl;
	}
	CClientInfo(){
		//memset(user,0,sizeof(user));
		isLogin=false;
	}
	/*CClientInfo CClientInfo(CClientInfo &p){
		id=p.id;
		strcpy(ip,p.ip);
		port=p.port; 
		certification=p.certification;
		isLogin=p.isLogin;
		strcpy(showName,p.showName);
		strcpy(user,p.user);
		return *this;
	}*/
};
//global varibales:
CBasicServer s;
vector<CClientInfo> clientList;
int numClients;
//
int init(){
	s.init(DEFAULT_PORT);
	return MYSUCCESS;
}
CClientInfo *getClient(char *user){
	for(vector<CClientInfo >::iterator i=clientList.begin();i!=clientList.end();i++){
		if(strcmp(i->user,user)==0){
			return i;
		}
	}
	return NULL;
}




int recvMess(SOCKET s,Message &m){
	 if(::s.recvMess(s,&m.h,sizeof(m.h))==MYERROR){
		 return MYERROR;
	 }
	 if(::s.recvMess(s,&m.d,m.h.dataLen)==MYERROR){
		 return MYERROR;
	 }
	 return MYSUCCESS;
}
int sendMess(SOCKET s,Message &m){
	 ::s.sendMess(s,&m,sizeof(m.h)+m.h.dataLen);
	 return 0;
}

//client's main function:
unsigned long WINAPI dealClient(LPVOID lParam){
	CClientInfo *ci=(CClientInfo *)lParam;
	clientList.push_back(*ci);
	ci=&clientList.back();
	Trace(clientList.size());
	SOCKET cs=ci->id;
	cout<<"create an clinet(id="<<ci->id<<")'s thread"<<endl;
	Message m;
	CClientInfo * findci;
	//
	if(recvMess(cs,m)==MYSUCCESS){
		if(m.h.type==MT_LOGIN){
			m.d.login.id=ci->id;
			if(ci->login(m.d.login.user,m.d.login.pass)){
				m.d.login.isSuccess=true;
				ci->certification=m.d.login.certification=rand();
				cout<<"MT_LOGIN"<<endl;
				numClients++;
				cout<<"add a user.there are "<<numClients<<" users"<<endl;
				//cout<<"ci:";ci->print();
				//cout<<"clientList[0]:";clientList[0].print();

			}else{
				m.d.login.isSuccess=false;
			}
			m.h.from=SERVER_ID;
			m.h.to=m.d.login.id;
			sendMess(m.h.to,m);
		}
	}else{
		cout<<"1lost the client"<<endl;
	}
	//
	int expectNum;int i;
	while(ci->isLogin){
		if(recvMess(cs,m)==MYERROR){
			cout<<"2lost the client"<<endl;break;
		}
		cout<<"client("<<ci->id<<"):";
		//start deal with message
		if(ci->isLogin){
			switch(m.h.type){
			case MT_LOGOFF:
				cout<<"MT_LOGOFF"<<endl;
				m.d.logoff.isSuccess=true;
				m.h.to=m.h.from;
				m.h.from=SERVER_ID;
				sendMess(m.h.to,m);
				ci->isLogin=false;
				break;
			case MT_EXAMPLE:
				sendMess(m.h.to,m);
				break;
			case MT_CHAT:
				strcpy(m.d.chat.prefix,ci->showName);
				strcat(m.d.chat.prefix," say:");
				sendMess(m.h.to,m);
				//
				strcpy(m.d.chat.prefix,"you say:");
				m.h.to=cs;
				m.h.from=SERVER_ID;
				sendMess(m.h.to,m);
				break;
			case MT_GETUSERDETAIL:
				findci=getClient(m.d.userDetail.user);
				if(findci==NULL){
					m.d.userDetail.id=INVALID_ID;
				}else{
					m.d.userDetail.id=findci->id;
				}
				//
				m.h.to=m.h.from;
				m.h.from=SERVER_ID;
				sendMess(m.h.to,m);
				break;
			case MT_GETUSERLIST:
#define _GETUSERLIST_test
				//cout<<"1"<<endl;
				expectNum=m.d.userList.num;
				m.d.userList.num=0;
#ifdef GETUSERLIST_test
				Trace(expectNum);
				Trace(numClients);
				Trace(m.d.userList.from);
#endif
				for(i=0;i<expectNum;i++){
					if(i+m.d.userList.from>=numClients){
						break;
					}else{
						strcpy(m.d.userList.users[i],clientList[m.d.userList.from+i].user);
						#ifdef GETUSERLIST_test
						Trace(m.d.userList.from+i);
						clientList[m.d.userList.from+i].print();
						Trace(m.d.userList.users[i]);
						#endif
						m.d.userList.num++;
					}
				}
				ci->print();
					#ifdef GETUSERLIST_test
				Trace((&clientList[0]==ci));
				Trace(clientList.size());

				Trace(m.d.userList.num);
				Trace(numClients);
				Trace(m.d.userList.users[0]);

				cout<<"2"<<endl;
				#endif
				//
				m.h.to=m.h.from;
				m.h.from=SERVER_ID;
				sendMess(m.h.to,m);
				//cout<<"3"<<endl;
				break;
			default:
				cout<<"MYERROR:in client not this type mess."<<endl;
				break;
			}
		}
		//end deal with message.
	}
	cout<<"exit the clinett(id="<<ci->id<<")'s thread"<<endl;
	return 0;
}





int main(){
	s.init(DEFAULT_PORT);
	while(1){
		CClientInfo ci;
		
		CClientInfo *p=&ci;
		
		if(s.wait(p->id,p->ip,p->port)==MYERROR){
			cout<<"wait fail"<<endl;break;
		}
		cout<<"IP:"<<p->ip<<" id:"<<p->id<<" port:"<<p->port<<" connect!"<<endl;
		DWORD dwThread;
		HANDLE hThread=CreateThread(NULL,0,&dealClient,(LPVOID)p,0,&dwThread);
		if(hThread==NULL){
			cout<<"CreateThread() failed!"<<endl;break;
		}
		CloseHandle(hThread);

	}
	return 0;
}

