#include<iostream>
#include<cstring>
#include<vector>
#include<winsock2.h>
#include<cstdlib>
#include<fstream>
using namespace std;
//user define:
#define MAX_LEN_SHOWNAME		20
#define MAX_LEN_USERNAME		20
#define MAX_LEN_PASS			20
#define MAX_LEN_CHATTEXT		200
#define MAX_LEN_PREFIX			40
//
#define INVALID_ID -1
#define SERVER_ID 0
//
//MESSAGE.TYPE
#define MT_ERROR					-1
#define MT_LOGIN					0
#define MT_LOGOFF					1
#define MT_CHAT						2
#define MT_PASSDIRECT				3
//
#define SUCCESS 0
#define Trace(m) cout<<#m"="<<m<<endl;
//
//Message type defined
typedef struct {
	int type;
	int from;
	int to;
	unsigned int dataLen;
}MessageHeader,*hMessageHeader;
struct LoginData{
	char user[MAX_LEN_USERNAME];
	char pass[MAX_LEN_PASS];
	int id;
	int certification;
};
struct LogoffData{
	bool isSuccess;
};
struct ChatData{
	char prefix[MAX_LEN_PREFIX];
	char text[MAX_LEN_CHATTEXT];
};
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
	}
	 ~CClient(){
		closesocket(mySock);
		WSACleanup();
	}
	int init(char *serverIP,unsigned short  port){
		mySock=socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
		if(mySock==SOCKET_ERROR){
			cout<<"socket() failed! can't create socket."<<endl;
		}
		sockaddr_in serverAddr;
		serverAddr.sin_port=htons(port);
		serverAddr.sin_addr.s_addr=inet_addr(serverIP);
		serverAddr.sin_family=AF_INET;
		if(connect(mySock,(sockaddr *)&serverAddr,sizeof(serverAddr))== SOCKET_ERROR){
			cerr<<"Connect server failed!"<<endl;return -1;
		}else{
			cerr<<"connect server success!"<<endl;
		}
		return 0;
	}
protected:
	int sendMess(void* m,int len){
		//send m to server.
		send(mySock,(char *)m,len,0);
		return 0;
	}
	int recvMess(void *m,int len){
		int leftLen=len;
		int recvLen=0;
		while(leftLen>0){
			recvLen=recv(mySock,(char *)m,len,0);
			if(recvLen==SOCKET_ERROR){
				cerr<<"recv() fialed:"<<WSAGetLastError()<<endl;
				return -1;
			}
			leftLen-=recvLen;
		}
		return 0;
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
		cout<<"create a thread"<<endl;
		CClientTest * c=(CClientTest *)lParam;
		MessageHeader mh;
		c->recvMess(&mh,sizeof(mh));
		union{
			LoginData login;
			LogoffData logoff;
			ChatData chat;
		}d;
		c->recvMess(&d,mh.dataLen);
		switch(mh.type){
			case MT_LOGIN:
				c->certification=d.login.certification;
				c->id=d.login.id;
				break;
			case MT_LOGOFF:
				if(d.logoff.isSuccess){
					c->id=INVALID_ID;
					cout<<"log off success!"<<endl;
				}else{
					cout<<"log off failed!"<<endl;
				}
				break;
			case MT_CHAT:
				cout<<d.chat.prefix<<d.chat.text<<endl;
				break;
			default:
				cout<<"error:in client not this type mess."<<endl;
				break;
		}
			
	}
	char *getName(){
		return showName;
	}
	int getID(){
		return id;
	}
	void login(char *user,char *pass){
		struct {
			MessageHeader h;
			LoginData d;
		} m;
		m.h.type=MT_LOGIN;
		m.h.from=getID();
		m.h.to=SERVER_ID;
		m.h.dataLen=sizeof(LoginData);
		//
		strncpy(m.d.pass,pass,sizeof(m.d.pass));
		strncpy(m.d.user,user,sizeof(m.d.user));
		//
		sendMess(&m,sizeof(MessageHeader)+m.h.dataLen);
	}
	void logoff(){
		struct {
			MessageHeader h;
			LogoffData d;
		} m;
		m.h.type=MT_LOGOFF;
		m.h.from=getID();
		m.h.to=SERVER_ID;
		m.h.dataLen=sizeof(LogoffData);
		//
		sendMess(&m,sizeof(m));
	}
	void sendStr(char *str,ID toID){
		struct {
			MessageHeader h;
			ChatData d;
		} m;
		m.h.type=MT_CHAT;
		m.h.from=getID();
		m.h.to=toID;
		m.h.dataLen=sizeof(ChatData);
		//
		if(strlen(str)>MAX_LEN_CHATTEXT){
			str[MAX_LEN_CHATTEXT]=0;
		}
		strcpy(m.d.text,str);
		sendMess(&m,sizeof(m));
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
	cout<<"server IP:"<<serverIP<<"\n port"<<port<<endl;
	//
	CClientTest c;
	while(1){
		char buffer[100];
		cin>>buffer;
		if(strcmp(buffer,"login")==0){
			cout<<"please wait..."<<endl;
			if(c.init(serverIP,port)!=SUCCESS){
				cerr<<"can't find server."<<endl;
			}else{
				char user[MAX_LEN_USERNAME];
				char pass[MAX_LEN_PASS];
				cout<<"user:";cin>>user;
				cout<<"password:";cin>>pass;
				c.login(user,pass);
			}		
		}else if(strcmp(buffer,"logoff")==0){
			c.logoff();
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
			c.sendStr(str,toID);
		}
	}

	return 0;
}

/*	void startRecv(){

	}
	
		ClientInfo *clientInfo=(ClientInfo *)lParam;
		SOCKET clientSock=clientInfo->socket;
		int lenRec;
		char buffer[DEFAULT_BUFFER+1];
		while(1){
			lenRec=recv(clientSock,buffer,DEFAULT_BUFFER,0);//×èÈû.
			if(lenRec==0) break;
			else if(lenRec==SOCKET_ERROR){
			 	cout<<"recv() fialed:"<<WSAGetLastError()<<endl;
				break;
			}else if(lenRec>0){
				buffer[lenRec]='\0';
				cout<<"\nFrom server :"<<buffer<<endl;
				Beep(5000,175);
			}else{
				cout<<"Error:in recv():lenRec <-1"<<endl;
				break;
			}
		}
		return 0;
	}
		
		ClientInfo clientInfo;
		clientInfo.socket=mySock;
		
		while(1){
			cout<<"Please input anything:";
			int lenBuffer=0;
			while(lenBuffer<DEFAULT_BUFFER &&(buffer[lenBuffer]=cin.get())!='\n')lenBuffer++;
			buffer[lenBuffer]='\0';
			if(strcmp(buffer,"exit")==0 || strcmp(buffer,"quit")==0){
				cout<<"exiting "<<endl;
				send(mySock,buffer,strlen(buffer),0);
				break;
			}
			send(mySock,buffer,lenBuffer,0);
		}
	//	CloseHandle(hThread);
		
		*/