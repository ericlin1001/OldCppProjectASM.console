#include<iostream>
#include<cstring>
#include<vector>
#include<winsock2.h>
#include<cstdlib>
#include<fstream>
//
using namespace std;
#define Trace(m) cout<<#m"="<<m<<endl;
#define SUCCESS 0
#define ERROR -1
//
struct message{
#define MAX_DATA_LEN 200
	int type;
	int from;
	int to;
	char data[MAX_DATA_LEN];
	char endflag;
	message(){endflag='#';}
};
#define SIZEOF_MESSAGE (MAX_DATA_LEN+13)
//MESSAGE.TYPE
#define MT_ERROR				-1
#define MT_LOGIN				0
#define MT_LOGOFF				1
#define MT_NORMAL				2
#define MT_TEST					3
#define MT_LOGIN_SUCCESS		4
//
class CClient;
class CServer;
//
class CClient{
protected:
	int id;
	SOCKET mySock;
public:
	CClient(){
		id=-1;
		memset(name,0,sizeof(name));
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
		//
		mySock=socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
		if(mySock==SOCKET_ERROR){
			cout<<"socket() failed! can't create socket."<<endl;
		}
		//
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
	int sendMess(void *m){
		//send m to server.
		send(mySock,(char *)&m,sizeof(m),0);
		return 0;
	}
	int recvMess(void *m){
		char buffer[SIZEOF_MESSAGE];
		int leftLen=SIZEOF_MESSAGE;
		int recvLen=0;
		while(leftLen>0){
			recvLen=recv(mySock,buffer,SIZEOF_MESSAGE,0);
			if(recvLen==SOCKET_ERROR){
				cerr<<"recv() fialed:"<<WSAGetLastError()<<endl;
				return -1;
			}
			leftLen-=recvLen;
		}
		memcpy((void *)&m,buffer,SIZEOF_MESSAGE);
		return 0;
		//there had better to start a timmer to ensure the server is alive.
	}
	
/*	void startRecv(){

	}
	static unsigned long WINAPI threadFun(LPVOID lParam){
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
		DWORD dwThread;
		HANDLE hThread=	CreateThread(NULL,0,recvServer,(LPVOID)&clientInfo,0,&dwThread);
		CloseHandle(hThread);
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
};
class CClientTest:public CClient{
private:
	char name[20];
public:
	int login(){
		message m;
		m.from=id;
		m.type=MT_LOGIN;
		sendMess(m);
		recvMess(m);
		if(m.type==MT_LOGIN_SUCCESS){
			return SUCCESS;
		}
		return ERROR;
	}
	int logoff(){
		message m;
		m.from=id;
		m.type=MT_LOGIN;
		sendMess(m);
		shutdown(mysock,0);//
		return SUCCESS;
	}
	int sendStr(char *str,int toID){
		message m;
		m.from=id;
		m.to=toID;
		m.type=MT_TEST;
		strcpy(m.data,str);
		sendMess(m);
		return SUCCESS;
	}
};
class CClientInfo{
public:
	int id;
	char name[20];
	void print(){
		cout<<"id="<<id<<endl
			<<"name="<<name<<endl;
	}
};
/*MT_ERROR				-1
#define MT_LOGIN				0
#define MT_LOGOFF				1
#define MT_NORMAL				2
#define MT_TEST					3
#define MT_LOGIN_SUCCESS	*/
class CServer{
	int numClients;
	vector<CClientInfo> clientList;
public:

private:
	void recvMess(message &m){
		//receive m from the client
		switch(m.type){
			case MT_LOGIN:
				break;
			case MT_LOGOFF:
				break;
			case MT_NORMAL:
				break;
			case MT_TEST:
				break;
		}
	}
	void addClient(){
		
	}
	void sendMess(message &m,int client){
		//send m to client
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
				if(c.login()==SUCCESS){
					cout<<"login success."<<endl;
				}else {
					cout<<"login fail."<<endl;
				}
			}		
		}else if(strcmp(buffer,"logoff")==0){
			if(c.logoff()==SUCCESS){
				cout<<"logoff success."<<endl;
			}else {
				cout<<"logoff fail."<<endl;
			}
		}else if(strcmp(buffer,"setname")==0){
			
		}else if(strcmp(buffer,"getClientList")==0){
			
		}else if(strcmp(buffer,"send")==0){
			char str[MAX_DATA_LEN+1];
			cout<<"## means the end of message."<<endl;
			cout<<"message("<<MAX_DATA_LEN<<"):";
			cin.get();
			int strlen=0;
			str[strlen++]=cin.get();
			while(strlen<MAX_DATA_LEN){
				str[strlen++]=cin.get();
				if(str[strlen-1]=='#' && str[strlen-2]=='#'){
					strlen-=2;
					break;
				}
			}
			c.sendStr(str);
		}
	}
	/*
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);v.push_back(4);
	Trace(v.size());
	v.pop_back();
	Trace(v.back());
	Trace(v.front());
	Trace(v.at(2));
	vector<int>::iterator iv;
	for(iv=v.begin();iv!=v.end();iv++){
		Trace(*iv);
	}
	//4 3 1 3 1 2 3
*/
	return 0;
}