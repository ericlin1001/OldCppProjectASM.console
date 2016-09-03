

#include<iostream>
#include<cstring>
#include<vector>
#include<winsock2.h>
#include<cstdlib>
#include<fstream>
using namespace std;
#include "../definedMess.h"
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
#define _sendMess_test
#ifdef sendMess_test
		cout<<"send bytest:"<<len<<endl;
#endif
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
	ID id;
	char showName[MAX_LEN_SHOWNAME];
private:
	Message m;
private:
	int certification;
public:
	int recvMess(Message &m){
		if(isConnect()){
			if(CClient::recvMess(&m.h,sizeof(m.h))==MYSUCCESS){
				if(CClient::recvMess(&m.d,m.h.dataLen)==MYSUCCESS){
					return MYSUCCESS;
				}
			}
			lostServer();
			return MYERROR;
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
	/*DWORD dwThread;
	HANDLE hThread=	CreateThread(NULL,0,threadFun,(LPVOID)this,0,&dwThread);
	if(hThread==NULL){
	cerr<<"CreateThread failed!"<<endl;
	return ;
	}
		CloseHandle(hThread);*/
	}
	bool isLogin(){
		return id>0;
	}
	void lostServer(){
		cout<<"lost the server"<<endl;
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
	ID getID(){
		return id;
	}
	void login(char *user,char *pass){
		m.h.type=MT_LOGIN;
		m.h.from=getID();
		m.h.to=SERVER_ID;
		//
		strcpy(m.d.login.pass,pass);
		strcpy(m.d.login.user,user);
		//
		m.h.dataLen=m.d.login.len();
		sendMess(m);
		
		//recv
		recvMess(m);
		
		if(m.h.type==MT_LOGIN){
			if(m.d.login.isSuccess){
				certification=m.d.login.certification;
				id=m.d.login.id;
				Trace(certification);
				Trace(id);
				cout<<"login MYSUCCESS."<<endl;
			}else{
				cout<<"login fail"<<endl;
			}
		}else{
			recvWrongMess();
		}
	}
	void recvWrongMess(){
		cout<<"recv wrong mess."<<endl;
	}
	/*	struct UserDetailData{
	ID id;
	char user[MAX_LEN_USERNAME];
	int len(){return sizeof(UserDetailData);}
	}userDetail;
	struct UserListData{
	int from;
	int num;
	char users[MAX_NUM_USERLIST][MAX_LEN_USERNAME];
	int len(){return sizeof(from)+sizeof(num)+MAX_LEN_USERNAME*num;}
	}userList;
	
	  #define MT_GETUSERDETAIL			5
#define MT_GETUSERLIST				6*/
	void getUserDetail(char *user){
		Message m;
		m.h.type=MT_GETUSERDETAIL;
		m.h.from=getID();
		m.h.to=SERVER_ID;
		//
		m.h.dataLen=m.d.userList.len();
		strcpy(m.d.userDetail.user,user);
		//
		sendMess(m);
		//recv
		recvMess(m);
		if(m.h.type==MT_GETUSERDETAIL){
			cout<<m.d.userDetail.id<<"\t"<<m.d.userDetail.user<<endl;
		}else{
			recvWrongMess();
		}
	}
	void getUserList(){
		Message m;
		m.h.type=MT_GETUSERLIST;
		m.h.from=getID();
		m.h.to=SERVER_ID;
		//
		
		m.d.userList.num=5;
		m.d.userList.from=0;
		//
		
		m.h.dataLen=m.d.userList.len();
		sendMess(m);
		//recv
		recvMess(m);
		if(m.h.type==MT_GETUSERLIST){
			cout<<"List:"<<endl;
			for(int i=0;i<m.d.userList.num;i++){
				cout<<m.d.userList.users[i]<<"\t";
				if((i+1)%5==0)cout<<endl;
			}
			cout<<endl;
		}else{
			recvWrongMess();
		}
	}
	void logoff(){
		Message m;
		m.h.type=MT_LOGOFF;
		m.h.from=getID();
		m.h.to=SERVER_ID;
		//
		m.h.dataLen=m.d.logoff.len();
		sendMess(m);
		//recv
		recvMess(m);
		if(m.h.type==MT_LOGOFF){
			if(m.d.logoff.isSuccess){
				id=INVALID_ID;
				cout<<"log off MYSUCCESS!"<<endl;
			}else{
				cout<<"log off failed!"<<endl;
			}
		}else{
			recvWrongMess();
		}
		
	}
	void sendStr(char *str,ID toID){
		Message m;
		m.h.type=MT_CHAT;
		m.h.from=getID();
		m.h.to=toID;
		//
		if(strlen(str)>MAX_LEN_CHATTEXT-1){
			str[MAX_LEN_CHATTEXT]=0;
		}
		strcpy(m.d.chat.text,str);
		//
		m.h.dataLen=m.d.chat.len();
		sendMess(m);
		//recv
		recvMess(m);
		if(m.h.type==MT_CHAT){
			cout<<m.d.chat.prefix<<m.d.chat.text<<endl;
		}else{
			recvWrongMess();
		}
	}
};

#define SERVER_INFO "serverInfo.txt"
#define test
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
	
#ifdef test
	
#endif
				//
	while(1){
		char buffer[100];
		cout<<"~order:";cin>>buffer;
		
			
		if(strcmp(buffer,"t")==0){
			cout<<"please wait..."<<endl;
			if(c.init(serverIP,port)!=MYSUCCESS){
				cerr<<"Can't find server."<<endl;
			}else{
				cout<<"Have connected to server."<<endl;
				c.start();
			}
			c.login("eric","123");
			c.getUserList();
		}else if(strcmp(buffer,"login")==0||strcmp(buffer,"l")==0){
			//
			cout<<"please wait..."<<endl;
			if(c.init(serverIP,port)!=MYSUCCESS){
				cerr<<"Can't find server."<<endl;
			}else{
				cout<<"Have connected to server."<<endl;
				c.start();
			}
			//
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
		}else if(strcmp(buffer,"getDetail")==0){
			char user[20];
			cout<<"user:";cin>>user;
			c.getUserDetail(user);
		}else if(strcmp(buffer,"getList")==0){
			c.getUserList();
		}else if(strcmp(buffer,"send")==0){
			ID toID;
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

