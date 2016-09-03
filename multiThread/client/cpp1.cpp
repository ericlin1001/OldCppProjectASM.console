//by eric
#include<winsock2.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<fstream.h>
#define DEFAULT_PORT 5150
#define DEFAULT_BUFFER 500
char buffer[DEFAULT_BUFFER+1]="test";
#define DEFAULT_ADDR "172.18.157.121"
//my:"172.18.157.121";//my//
//xiao:"192.168.66.140";//xiaoyun//
//"127.0.0.1";//
char serverIP[100];//"172.18.157.120";//xiaoyun////"192.168.1.147";//
//client:
struct ClientInfo{
	SOCKET socket;
	char ip[20];
	int id;
	char nume[100];
};
unsigned long WINAPI recvServer(LPVOID lParam){
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
int main(){
	WSADATA wsd;
	SOCKET mySock;//u_int
	sockaddr_in serverAddr;
	unsigned short port=DEFAULT_PORT;
	int lenServerAddr;
	if(WSAStartup(MAKEWORD(2,2),&wsd)!=0){
		printf("Failed to load WinSock!\n");return 1;
	}
	mySock=socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
	if(mySock==SOCKET_ERROR){
		cout<<"socket() failed! can't create listenSock."<<endl;
		return 1;
	}
	//
	int lenx;
	while(1){
		//get ip
		lenx=0;
		cout<<"Connect to where?"<<endl;
		cout<<"IP:";
		while((serverIP[lenx]=cin.get())!='\n')lenx++;
		//cin.get();
		serverIP[lenx]='\0';
		if(lenx<=1){strcpy(serverIP,DEFAULT_ADDR);}
		//get port
		cout<<"Port:";
		lenx=0;
		while((buffer[lenx]=cin.get())!='\n')lenx++;
		buffer[lenx]='\0';
		//cin.get();
		if(lenx<=1){port=DEFAULT_PORT;}else{
			port=atoi(buffer);
		}
		cout<<"connecting,please wiat."<<endl;
		//cout<<"addr="<<serverIP<<"  port:"<<port<<endl;
		serverAddr.sin_port=htons(port);
		serverAddr.sin_addr.s_addr=inet_addr(serverIP);
		serverAddr.sin_family=AF_INET;
		lenServerAddr=sizeof(serverAddr);
		bool bconnect=connect(mySock,(sockaddr *)&serverAddr,lenServerAddr)!=SOCKET_ERROR;
		if(!bconnect){
			cout<<"Connect failed!"<<endl;
		}else{
			cout<<"Connect to "<<serverIP<<":"<<port<<" success!"<<endl<<endl;
			break;
		}
	};
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
	closesocket(mySock);
	WSACleanup();
	
	return 0;
}