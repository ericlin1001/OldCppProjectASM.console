#define SERVER_INFO "serverInfo.txt"

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
int testCount=0;
#define testTag cout<<"testTag:"<<testCount++<<endl;
#define resetTag testCount=0;
//
class CBasicClient{
protected:
	SOCKET mySock;
	bool bconn;
public:
	bool isConn(){
		return bconn;
	}
	void disConn(){
		bconn=false;
		shutdown(mySock,2);
	}
	CBasicClient(){
		bconn=false;
		WSADATA wsd;
		if(WSAStartup(MAKEWORD(2,2),&wsd)!=0){
			cerr<<"Failed to load WinSock!\n";
		}
		mySock=SOCKET_ERROR;
	}
	~CBasicClient(){
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
			bconn=true;
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
class CClientTest:public CBasicClient{
protected:
	ID id;
	int age;
	char name[MAX_LEN_SHOWNAME];
	HANDLE hThread;
	HANDLE hMainSig;
	HANDLE hThreadSig;
private:
	Message m;
private:
	int certification;
public:
	void print(){
		cout<<" id:"<<id
			<<" name:"<<name
			<<" age:"<<age
			<<endl;
			
	}
	
	int recvMess(Message &m){
		if(isConnect()){
			if(CBasicClient::recvMess(&m.h,sizeof(m.h))==MYSUCCESS){
				if(CBasicClient::recvMess(&m.d,m.h.dataLen)==MYSUCCESS){
					return MYSUCCESS;
				}
			}
			return MYERROR;
		}
		Test("Error:not connect in recvMess ");
		return MYERROR;
	}
	int sendMess(Message &m){
		if(isConnect()){
			//m.h.print();
			CBasicClient::sendMess(&m,sizeof(m.h)+m.h.dataLen);
			return MYSUCCESS;
		}
		Test("Error:not connect in sendMess ");
		return MYERROR;
		
	}
	CClientTest(){
		id=INVALID_ID;
		memset(name,0,sizeof(name));
		hMainSig=CreateEvent(NULL,FALSE,FALSE,NULL);
		hThreadSig=CreateEvent(NULL,FALSE,FALSE,NULL);
	}
	~CClientTest(){
		CloseHandle(hThread);
	}
	void start(){
	DWORD dwThread;
	hThread=CreateThread(NULL,0,threadFun,(LPVOID)this,0,&dwThread);
	if(hThread==NULL){
	cerr<<"CreateThread failed!"<<endl;
	return ;
	}
		
	}
	bool isLogin(){
		return id!=INVALID_ID;
	}

	void pauseThread(){
		SuspendThread(hThread);
	}
	void resumeThread(){
		ResumeThread(hThread);
	}
	void lostServer(){
		cout<<"lost the server"<<endl;
		logoff();
	}
	static unsigned long WINAPI threadFun(LPVOID lParam){
		//deal with mess which be sent arbitary
		cout<<"create a thread"<<endl;
		CClientTest * c=(CClientTest *)lParam;
		Message m;
		//Message &m=c->m;
		while(1){
			if(c->recvMess(m)==MYERROR){
				c->lostServer();break;
			}
			cout<<"Thread:Recv a mess."<<endl;
			//m.h.print();
			switch(m.h.type){
			case MT_CHAT:
				cout<<m.d.chat.prefix<<m.d.chat.text<<endl;
				break;
			default:
				/**/
				cout<<"not deal with in thread."<<endl;
				memcpy(&c->m,&m,sizeof(m.h)+m.h.dataLen);
				//
				SetEvent(c->hMainSig);
				WaitForSingleObject(c->hThreadSig,INFINITE);
				break;
			}
		}
		return 0;
	}
	void startRecv(){
		WaitForSingleObject(hMainSig,INFINITE);
	}
	void endRecv(){//must after the dealing with the m;
		SetEvent(hThreadSig);
	}
	char *getName(){
		return name;
	}
	ID getID(){
		return id;
	}
	void login(char *user,char *pass){
		if(!isLogin()){
			//for test:
			fstream infile;
			infile.open(SERVER_INFO);
			if(infile.fail()){
				cerr<<"open "SERVER_INFO" failed!"<<endl;
				return ;
			}
			char serverIP[20];unsigned short port;
			infile>>serverIP>>port;
			//
			cout<<"please wait..."<<endl;
			if(isConn()){cout<<"have connected!"<<endl;return;}else{
				if(  init(serverIP,port)!=MYSUCCESS){
					cerr<<"Can't find server."<<endl;
					return;
				}else{
					cout<<"Have connected to server."<<endl;
					start();
				}
			}
			//
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
			startRecv();
			if(m.h.type==MT_LOGIN){
				if(m.d.login.isSuccess){
					certification=m.d.login.certification;
					id=m.d.login.id;
					Trace(id);
					cout<<"test:login MYSUCCESS."<<endl;
					
				}else{
					cout<<"login fail"<<endl;
				}
			}else{
				recvWrongMess();
			}
			endRecv();
			
			if(isLogin()){
				getUserData();
				print();
			}
		}else{
			cout<<"you have logined!"<<endl;
		}
		
	}
	void getUserData(){
		//update data;
		m.h.type=MT_GETUSERDATA;
		m.h.from=getID();
		m.h.to=SERVER_ID;
		//
		m.d.userData.type=USER_DATA_READ;
		//
		m.h.dataLen=m.d.login.len();
		sendMess(m);
		//recv
		startRecv();
		if(m.h.type==MT_GETUSERDATA){
			if(m.d.userData.isSuccess){
				age=m.d.userData.age;
				strcpy(name,m.d.userData.name);
				cout<<"updateData success."<<endl;
			}else{
				cout<<"updateData fail"<<endl;
			}
		}else{
			recvWrongMess();
		}
		endRecv();
	}
	void updateUserData(){
		//update data;
		m.h.type=MT_GETUSERDATA;
		m.h.from=getID();
		m.h.to=SERVER_ID;
		//
		m.d.userData.type=USER_DATA_WRITE;
		//
		m.h.dataLen=m.d.login.len();
		sendMess(m);
		//recv
		startRecv();
		if(m.h.type==MT_GETUSERDATA){
			if(m.d.userData.isSuccess){
				m.d.userData.age=age;
				strcpy(m.d.userData.name,name);
				cout<<"updateData success."<<endl;
			}else{
				cout<<"updateData fail"<<endl;
			}
		}else{
			recvWrongMess();
		}
		endRecv();
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
	void getUserDetail(char *user,ID &getid){
		m.h.type=MT_GETUSERDETAIL;
		m.h.from=getID();
		m.h.to=SERVER_ID;
		//
		strcpy(m.d.userDetail.name,user);
		// 
		m.h.dataLen=m.d.userDetail.len();
		sendMess(m);
		//recv
		startRecv();
		if(m.h.type==MT_GETUSERDETAIL){
			getid=m.d.userDetail.id;
		}else{
			recvWrongMess();
		}
		endRecv();
	}
	void getUserList(){
		m.h.type=MT_GETUSERLIST;
		m.h.from=getID();
		m.h.to=SERVER_ID;
		//
		testTag;
		SuspendThread(NULL);
		testTag;

		m.d.userList.num=5;
		m.d.userList.from=0;
		//
		
		m.h.dataLen=m.d.userList.len();
		sendMess(m);
		//recv
		startRecv();
		if(m.h.type==MT_GETUSERLIST){
			cout<<"List:"<<endl;
			Trace(m.d.userList.num);
			Trace(m.d.userList.users[0]);
			for(int i=0;i<m.d.userList.num;i++){
				cout<<m.d.userList.users[i]<<"\t";
				if((i+1)%5==0)cout<<endl;
			}
			cout<<endl;
		}else{
			recvWrongMess();
		}
		endRecv();
	}
	void logoff(){
		
		//
		if(isConn()){
			m.h.type=MT_LOGOFF;
			m.h.from=getID();
			m.h.to=SERVER_ID;
			//
			m.h.dataLen=m.d.logoff.len();
			sendMess(m);
		}
		/*//recv
		startRecv();
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
		endRecv();*/
		//
		
		
		TerminateThread(hThread,0);
		disConn();
		id=INVALID_ID;
		ResetEvent(hMainSig);ResetEvent(hThreadSig);
	}
	void sendStr(char *str,char *toName){
		getUserDetail(toName,m.h.to);
		//
		m.h.type=MT_CHAT;
		m.h.from=getID();
		//
		if(m.h.to==INVALID_ID){
			cout<<"can't find user:"<<toName<<endl;
			return;
		}
		//
		if(strlen(str)>MAX_LEN_CHATTEXT-1){
			str[MAX_LEN_CHATTEXT]=0;
		}
		strcpy(m.d.chat.text,str);
		//
		m.h.dataLen=m.d.chat.len();
		sendMess(m);
	}
};


#define test
CClientTest c;

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
	
	//
	
#ifdef test
	
#endif
				//
	while(1){
		char buffer[100];
		cout<<"~order:";cin>>buffer;	
		if(strcmp(buffer,"t")==0){
			cout<<"please wait..."<<endl;
			if(c.isConn()){cout<<"have connected!"<<endl;}else{
			if(  c.init(serverIP,port)!=MYSUCCESS){
				cerr<<"Can't find server."<<endl;
			}else{
				cout<<"Have connected to server."<<endl;
				c.start();
			}
			}
			c.login("eric","123");
			c.getUserList();
		}else if(strcmp(buffer,"login")==0||strcmp(buffer,"l")==0){
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
			if(c.isConn()){cout<<"have connected!"<<endl;}else{
			if(  c.init(serverIP,port)!=MYSUCCESS){
				cerr<<"Can't find server."<<endl;
			}else{
				cout<<"Have connected to server."<<endl;
				c.start();
			}
			}
		}else  if(strcmp(buffer,"update")==0){
			c.getUserData();
			c.print();
		}else if(strcmp(buffer,"getList")==0){
			c.getUserList();
		}else if(strcmp(buffer,"send")==0){
			char toname[20];
			cout<<"to(name):";cin>>toname;
			char str[MAX_LEN_CHATTEXT];
			cout<<"## means the end of message."<<endl;
			cout<<"message("<<MAX_LEN_CHATTEXT<<"):";
			cin.get();
			int strlen=0;
			cin.get();
			str[strlen++]=cin.get();
			while(strlen<MAX_LEN_CHATTEXT-1){
				str[strlen++]=cin.get();
				if(str[strlen-2]=='\\' && str[strlen-1]=='#'){
					str[strlen-2]='#';
					strlen--;
					break;
				}
				if(str[strlen-2]!='\\' && str[strlen-1]=='#'){
					strlen-=2;
					break;
				}
			}
			str[strlen]=0;
			c.sendStr(str,toname);
		}else{
			cout<<"no this order"<<endl;
		}
	}
	
	return 0;
}

