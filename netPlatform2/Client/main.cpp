
#include "../definedMess.h"
#include<iostream>
#include<cstring>
#include<vector>
#include<winsock2.h>
#include<cstdlib>
#include<fstream>
using namespace std;
#define Trace(m) cout<<#m"="<<m<<endl;
//
class CClient{
protected:
	SOCKET mySock;
public:
	CClient(){
		WSADATA wsd;
		if(WSAStartup(MAKEWORD(2,2),&wsd)!=0){
			cerr<<"Failed to load WinSock!\n";
		}
		mySock=SOCKET_ERROR;
	}
	~CClient(){
		closesocket(mySock);
		WSACleanup();
	}
	bool isConnect(){
		return mySock!=SOCKET_ERROR;
	}
	int init(char *serverIP,unsigned short  port){
		//try to connect
		mySock=socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
		if(mySock==SOCKET_ERROR){
			cout<<"socket() failed! can't create socket."<<endl;
		}
		sockaddr_in serverAddr;
		serverAddr.sin_port=htons(port);
		serverAddr.sin_addr.s_addr=inet_addr(serverIP);
		serverAddr.sin_family=AF_INET;
		if(connect(mySock,(sockaddr *)&serverAddr,sizeof(serverAddr))== SOCKET_ERROR){
			cerr<<"Connect server failed!"<<endl;
			mySock=SOCKET_ERROR;
			return -1;
		}else{
			cerr<<"connect server success!"<<endl;
		}
		return 0;
	}
protected:
	int sendMess(void* m,int len){
		send(mySock,(char *)m,len,0);
		return 0;
	}
	int recvMess(void *m,int len){
		int leftLen=len;
		int recvLen=0;
		while(leftLen>0){
			recvLen=recv(mySock,(char *)m,len,0);
			if(recvLen==SOCKET_ERROR){
				//cerr<<"recv() fialed:"<<WSAGetLastError()<<endl;
				return MYERROR;
			}
			leftLen-=recvLen;
		}
		return MYSUCCESS;
		//there had better to start a timmer to ensure the server is alive.
	}
};
class CClientTest:public CClient{
protected:
	int id;
	char showName[MAX_LEN_SHOWNAME];
private:
	int certification;
public:
	int recvMess(Message &m){
		if(isConnect()){
			if(CClient::recvMess(&m.h,sizeof(m.h))==MYERROR){
				return MYERROR;
			}
			if(CClient::recvMess(&m.d,m.h.dataLen)==MYERROR){
				return MYERROR;
			}
			return MYSUCCESS;
		}
		Test("Error:not connect in recvMess ");
		return MYERROR;
	}
	int sendMess(Message &m){
		if(isConnect()){
			//m.h.print();
			CClient::sendMess(&m,sizeof(m.h)+m.h.dataLen);
			return MYSUCCESS;
		}
		Test("Error:not connect in sendMess ");
		return MYERROR;
		
	}
	CClientTest(){
		id=INVALID_ID;
		memset(showName,0,sizeof(showName));
	}
	void start(){
		DWORD dwThread;
		HANDLE hThread=	CreateThread(NULL,0,threadFun,(LPVOID)this,0,&dwThread);
		if(hThread==NULL){
			cerr<<"CreateThread failed!"<<endl;
			return ;
		}
		CloseHandle(hThread);
	}
	bool isLogin(){
		return id>0;
	}
	static unsigned long WINAPI threadFun(LPVOID lParam){
		CClientTest * c=(CClientTest *)lParam;
		Message m;
		while(1){
			if(c->recvMess(m)==MYERROR){
				cout<<"lost the server"<<endl;break;
			}
			//m.h.print();
			switch(m.h.type){
			case MT_LOGIN:
				if(m.d.login.isSuccess){
					c->certification=m.d.login.certification;
					c->id=m.d.login.id;
					Trace(c->certification);
					Trace(c->id);
					cout<<"login MYSUCCESS."<<endl;
				}else{
					cout<<"login fail"<<endl;
				}
				break;
			case MT_LOGOFF:
				if(m.d.logoff.isSuccess){
					c->id=INVALID_ID;
					cout<<"log off MYSUCCESS!"<<endl;
				}else{
					cout<<"log off failed!"<<endl;
				}
				break;
			case MT_CHAT:
				cout<<m.d.chat.prefix<<m.d.chat.text<<endl;
				break;
			default:
				cout<<"MYERROR:in client not this type mess."<<endl;
				break;
			}
		}
		return 0;
	}
	char *getName(){
		return showName;
	}
	int getID(){
		return id;
	}
	void login(char *user,char *pass){
		Message m;
		m.h.type=MT_LOGIN;
		m.h.from=getID();
		m.h.to=SERVER_ID;
		//
		m.h.dataLen=sizeof(m.d.login);
		strcpy(m.d.login.pass,pass);
		strcpy(m.d.login.user,user);
		//
		sendMess(m);
	}
	void logoff(){
		Message m;
		m.h.type=MT_LOGOFF;
		m.h.from=getID();
		m.h.to=SERVER_ID;
		//
		m.h.dataLen=sizeof(m.d.logoff);
		//
		sendMess(m);
	}
	void sendStr(char *str,int toID){
		Message m;
		m.h.type=MT_CHAT;
		m.h.from=getID();
		m.h.to=toID;
		//
		if(strlen(str)>MAX_LEN_CHATTEXT-1){
			str[MAX_LEN_CHATTEXT]=0;
		}
		strcpy(m.d.chat.text,str);
		m.h.dataLen=sizeof(m.d.chat.prefix)+(strlen(m.d.chat.text)+1);
		//
		sendMess(m);
	}
};

#define SERVER_INFO "serverInfo.txt"
int main(){
	fstream infile;
	infile.open(SERVER_INFO);
	if(infile.fail()){
		cerr<<"open "SERVER_INFO" failed!"<<endl;
		return 0;
	}
	char serverIP[20];unsigned short port;
	infile>>serverIP>>port;
	cout<<"server IP:"<<serverIP<<endl
		<<"port     :"<<port<<endl;
	//
	CClientTest c;
	//
	cout<<"please wait..."<<endl;
	if(c.init(serverIP,port)!=MYSUCCESS){
		cerr<<"Can't find server."<<endl;
	}else{
		cout<<"Have connected to server."<<endl;
		c.start();
	}
	
				//
	while(1){
		char buffer[100];
		cout<<"~order:";cin>>buffer;
		if(strcmp(buffer,"login")==0){
			char user[MAX_LEN_USERNAME];
			char pass[MAX_LEN_PASS];
			cout<<"user:";cin>>user;
			cout<<"password:";cin>>pass;
			c.login(user,pass);
		}else if(strcmp(buffer,"logoff")==0){
			c.logoff();
		}else if(strcmp(buffer,"help")==0){
			cout<<"all order:\nlogin,logoff,help,setname,getClientList,send."<<endl;
		}else if(strcmp(buffer,"connect")==0 ||strcmp(buffer,"c")==0){
			cout<<"please wait..."<<endl;
			if(c.init(serverIP,port)!=MYSUCCESS){
				cerr<<"Can't find server."<<endl;
			}else{
				cout<<"Have connected to server."<<endl;
				c.start();
			}
		}else if(strcmp(buffer,"setname")==0){
			
		}else if(strcmp(buffer,"getClientList")==0){
			
		}else if(strcmp(buffer,"send")==0){
			int toID;
			cout<<"to(ID):";cin>>toID;
			char str[MAX_LEN_CHATTEXT];
			cout<<"## means the end of message."<<endl;
			cout<<"message("<<MAX_LEN_CHATTEXT<<"):";
			cin.get();
			int strlen=0;
			str[strlen++]=cin.get();
			while(strlen<MAX_LEN_CHATTEXT-1){
				str[strlen++]=cin.get();
				if(str[strlen-1]=='#' && str[strlen-2]=='#'){
					strlen-=2;
					break;
				}
			}
			str[strlen]=0;
			c.sendStr(str,toID);
		}else{
			cout<<"no this order"<<endl;
		}
	}
	
	return 0;
}

