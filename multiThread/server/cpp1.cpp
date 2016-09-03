#include<winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream.h>
#include<fstream.h>
#define DEFAULT_PORT 5150
#define DEFAULT_BUFFER 400
#define DEFAULT_ORDERS 20
//server:

const int lenOrders=5;
char *orders[DEFAULT_ORDERS]={
"order:showOrder",
"order:returnToClient",
"order:executeInServer",
"order:replyInClientWord",
"order:OrdSend"};
typedef void (*pFunc)(void *,char *);
void readFile(void *fileName,char *buffer){
	fstream infile;
	infile.open((char *)fileName,ios::in,0);
	while(!infile.eof()){
		*buffer++=infile.get();
	}
	*buffer=0;
}
struct RegisterOrder{
	char order[20];
	char fileName[50];
	pFunc pExecu;
};
RegisterOrder *registerOrd[DEFAULT_ORDERS];
int numRegOrd=0;
bool bOrders[DEFAULT_ORDERS];
struct ClientInfo{
	SOCKET socket;
	char ip[20];
	int id;
	char nume[100];
};
int numID=0;
void executOrder(char *str,SOCKET clientSock){
	int i;
	for(i=0;i<lenOrders;i++){
		if(strncmp(str,orders[i],strlen(orders[i]))==0){
			bOrders[i]=!bOrders[i];
			break;
		}
	}
	if(i==4){//"order:OrdSend"
		char *pstr=str+strlen(orders[4])+1;
		RegisterOrder *pOrd=new RegisterOrder;
		registerOrd[numRegOrd]=pOrd;
		char *p=(pOrd->order);
		while(*pstr!=' ')*p++=*pstr++;
		*p=0;
		pstr++;
		p=(pOrd->fileName);
		while(*pstr!=' ' && *pstr!=0)(*p++=*pstr++);
		*p=0;
		pOrd->pExecu=readFile;
		numRegOrd++;
		return ;
	}
	char returninfo[50];
	sprintf(returninfo,"set %s=%s",str,bOrders[i] ? "true" : "false");
	if(i<lenOrders){
		if(bOrders[0]){//show in server
			cout<<returninfo<<endl;
		}
		if(bOrders[1]){//return to client
			send(clientSock,returninfo,strlen(returninfo),0);
		}
	}
	char temp[5];
	temp[4]='\0';
	strncpy(temp,str+6,4);
	str+=10;
	sprintf(returninfo,"%s>temp.dat",str);
	if(bOrders[2] && strcmp(temp,"cmd:")==0){
		system(returninfo);
		fstream infile;
		infile.open("temp.dat",ios::in,0);
		while(!infile.eof()){
			char ch=infile.get();
			send(clientSock,&ch,1,0);
		}
		infile.close();
		system("del temp.dat");
	}
	
}
bool filterRegOrd(char *str,SOCKET csocket){
	int i;
	
	RegisterOrder *pOrd;
	for(i=0;i<numRegOrd;i++){
		pOrd=registerOrd[i];
		if(strcmp(pOrd->order,str)==0){
			char buffer[DEFAULT_BUFFER*100];
			pOrd->pExecu(pOrd->fileName,buffer);
			send(csocket,buffer,strlen(buffer),0);
			return true;
		}
	}
	return false;
}
unsigned long WINAPI ClientThread(LPVOID pParma){
	ClientInfo *clientInfo=(ClientInfo *)pParma;
	SOCKET clientSock=clientInfo->socket;
	int clinetID=clientInfo->id;
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
			//
			char temp[7];
			strncpy(temp,buffer,6);
			temp[6]='\0';
			if(strcmp(temp,"order:")==0){
				executOrder(buffer,clientSock);
			}else{
				if(!bOrders[4] || !filterRegOrd(buffer,clientSock)){
				cout<<"From client("<<clinetID<<"):"<<buffer<<endl;
				Beep(5000,175);
				}
			}
			if(bOrders[3]){//return to client
				send(clientSock,buffer,strlen(buffer),0);
			}
		}else{
			cout<<"Error:in recv():lenRec <-1"<<endl;
			break;
		}
	}
	return 0;
}
void baiscMusic(int i,int duration=200){
	int fre=0;
	int k=1;
	switch(i){
	case 1:
		fre=1046;
		break;
		case 2:
		fre=1174;
		break;
		case 3:
		fre=1318;
		break;
		case 4:
		fre=1396;
		break;
		case 5:
		fre=1567;
		break;
		case 6:
		fre=1864;
		break;
		case 7:
		fre=1975;
		break;
		case 0:
		k=2;
		break;
		default:
			fre=0;
	}
	fre+=-500+k*300+200;
	Beep(fre,duration);
}
void playMusic(char *str){
	while(*str){
		baiscMusic(*str-'0');
		str++;
	}
}
int main(){
	for(int i=1;i<8;i++){
		//baiscMusic(i);
	}
	playMusic("767");
	/*Beep(2300,500);
	Beep(2000,500);
	Beep(1600,500);*/
	
							return 0;
	WSADATA wsd;
	SOCKET listenSock,clientSock;//u_int
	sockaddr_in localAddr,clientAddr;
	unsigned short port=DEFAULT_PORT;
	int lenClientAddr;
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
		cout<<"bind() failed:"<<endl;
	}
	listen(listenSock,8);
	//
	DWORD dwThread;
	int indexThread=1;
	HANDLE hThread;
	while(1){
		lenClientAddr=sizeof(clientAddr);
		clientSock=accept(listenSock,(struct sockaddr *)&clientAddr,&lenClientAddr);
		if(clientSock==INVALID_SOCKET){
			cout<<"accept() failed:"<<endl;
			break;
		}
		ClientInfo clientInfo;
		clientInfo.id=numID++;
		clientInfo.socket=clientSock;
		printf("Acceped client(%d):%s:%d\n",clientInfo.id,inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port));
		//create a new thread:
		hThread=CreateThread(NULL,0,&ClientThread,(LPVOID)&clientInfo,0,&dwThread);
		if(hThread==NULL){
			cout<<"CreateThread() failed!"<<endl;
			break;
		}
		CloseHandle(hThread);
		indexThread++;
	}
	closesocket(listenSock);
	WSACleanup();
	return 0;
}
