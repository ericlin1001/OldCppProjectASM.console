

#include<iostream>
#include<cstring>
#include<vector>
#include<list>
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
/*
int isRegisterUser(char *user,char *pass){
#define REGED_USER_AND_PASS 2
#define REGED_USER 1
#define REGED_NONE 0
	//
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
		if(strcmp(u.user,user)==0){
			if(strcmp(p.pass,pass)==0){
				return REGED_USER_AND_PASS;
			}
			return REGED_USER;
		}
		infile>>(char *)&u>>(char *)&p;
	}
	return REGED_NONE;
}
*/

//global varibales:
CBasicServer s;
MyVector<CClientInfo *> clientList;
int numClients;
//
int init(){
	s.init(DEFAULT_PORT);
	return MYSUCCESS;
}
CClientInfo *getClient(char *name){
	for(MyVector<CClientInfo *>::iterator i=clientList.begin();i!=clientList.end();i++){
		if(strcmp((*i)->name,name)==0){
			return *i;
		}
	}
	return NULL;
}
CClientInfo *getClient(ID id){
	for(MyVector<CClientInfo *>::iterator i=clientList.begin();i!=clientList.end();i++){
		if((*i)->id==id){
			return *i;
		}
	}
	return NULL;
}
void lostUser(CClientInfo *ci){
	ci->logoff();
	cout<<"user:"<<ci->user<<" logoff !"<<endl;
	clientList.erase(ci);
	numClients--;
	Trace(numClients);
	Trace(clientList.size());
	cout<<"lost a user."<<endl;
}

int registerUser(const char *user,const char *pass,const char *name=0,int age=0){ 
	CClientInfo testc;
	if(testc.hasUser(user)==1){return REGISTER_USER_HAVED_USER;}
	if(testc.hasUser(user)==-1){return REGISTER_USER_UNKNOWN;}
	//
	CClientInfo ci;
	strcpy(ci.user,user);
	strcpy(ci.pass,pass);
	if(name==0)strcpy(ci.name,user);
	else strcpy(ci.name,name);
	ci.age=age;
	ofstream file;
#define PATH_USER_DATA FILE_USER_DATA
	if(!openFile(file,PATH_USER_DATA)){
		cout<<"open "PATH_USER_DATA" fail!"<<endl;
		return REGISTER_USER_UNKNOWN;
	}
	//file.seekp(0,ios::beg);
	ci.save(file);
	file.close();
	return REGISTER_USER_SUCCESS;
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
	CClientInfo *ci;
	ci=(CClientInfo *)lParam;
	//
	bool isquit=false;
	CClientInfo myci;
	myci.id=ci->id;
	strcpy(myci.ip,ci->ip);
	myci.port=ci->port;
	ci=&myci;
	SOCKET cs=ci->id;
	//
	cout<<"create an clinet(id="<<cs<<")'s thread"<<endl;
	Message m;
	CClientInfo * findci;
	//
	if(recvMess(cs,m)==MYSUCCESS){
		if(m.h.type==MT_LOGIN){
			m.d.login.id=ci->id;
			if(ci->login(m.d.login.user,m.d.login.pass)){
				m.d.login.isSuccess=true;
				ci->certification=m.d.login.certification=rand();
				//
				ci->print();
				cout<<"user:"<<m.d.login.user<<" login!"<<endl;
				//
				numClients++;
				clientList.push_back(ci);
				Trace(clientList.size());
				cout<<"add a user.there are "<<numClients<<" users"<<endl;
			
				//cout<<"ci:";ci->print();
			}else{
				m.d.login.isSuccess=false;
				isquit=true;
			}
			
			m.h.from=SERVER_ID;
			m.h.to=m.d.login.id;
			//
			sendMess(m.h.to,m);
			//Trace(ci->id);
		}
		if(m.h.type==MT_REGISTERUSER){
			
				cout<<"MT_REGISTERUSER"<<endl;
				
				if((m.d.registerUser.errorType=registerUser(m.d.registerUser.user,m.d.registerUser.pass))==REGISTER_USER_SUCCESS){
					cout<<"***New user:"<<m.d.registerUser.user<<" pass:"<<m.d.registerUser.pass<<"have registered!***"<<endl;

					m.d.registerUser.isSuccess=true;
				}else{
					m.d.registerUser.isSuccess=false;
				}
				//
				m.h.to=ci->id;
				m.h.from=SERVER_ID;
				sendMess(m.h.to,m);
				cout<<"r"<<endl;
			
		}
	}else{
		cout<<"1lost the client"<<endl;
		isquit=true;
	}
	//
	//Trace(ci->id)
	int expectNum;int i;
	while(!isquit && ci->getIsLogin()){
		cout<<"while"<<endl;
		//Trace(ci->id)
		if(recvMess(cs,m)==MYERROR){
			cout<<"2lost the client"<<endl;lostUser(ci);isquit=true;break;
		}
		cout<<"client("<<ci->id<<"):";
		switch(m.h.type){
			case MT_GETUSERDATA:
				cout<<"MT_GETUSERDATA"<<endl;
				m.d.userData.isSuccess=true;
				if(m.d.userData.type==USER_DATA_READ){
					strcpy(m.d.userData.name,ci->name);
					m.d.userData.age=ci->age;
				}else if(m.d.userData.type==USER_DATA_WRITE){
					strcpy(ci->name,m.d.userData.name);
					ci->age=m.d.userData.age;
					if(!ci->updateFile()){
						m.d.userData.isSuccess=false;
					}
				}else {
					m.d.userData.isSuccess=false;
				}
				m.h.to=m.h.from;
				m.h.from=SERVER_ID;
				sendMess(m.h.to,m);
					break;
			case MT_LOGOFF:
				cout<<"MT_LOGOFF"<<endl;
				m.d.logoff.isSuccess=true;
				m.h.to=m.h.from;
				m.h.from=SERVER_ID;
				sendMess(m.h.to,m);
				lostUser(ci);
				break;
			case MT_EXAMPLE:
				cout<<"MT_EXAMPLE"<<endl;
				sendMess(m.h.to,m);
				break;
			case MT_CHAT:
				cout<<"MT_CHAT"<<endl;
				strcpy(m.d.chat.prefix,ci->name);
				strcat(m.d.chat.prefix," say:");
				sendMess(m.h.to,m);
				//
				/*strcpy(m.d.chat.prefix,"you say:");
				m.h.to=cs;
				m.h.from=SERVER_ID;
				sendMess(m.h.to,m);*/
				break;
			case MT_GETUSERDETAIL:
				cout<<"MT_GETUSERDETAIL"<<endl;
				findci=getClient(m.d.userDetail.name);
				if(findci==NULL){
					m.d.userDetail.id=INVALID_ID;
				}else{
					m.d.userDetail.id=findci->id;
				}
				m.h.to=m.h.from;
				m.h.from=SERVER_ID;
				sendMess(m.h.to,m);
				break;
			case MT_GETUSERLIST:
				cout<<"MT_GETUSERLIST"<<endl;
				expectNum=m.d.userList.num;
				m.d.userList.num=0;
				for(i=0;i<expectNum;i++){
					if(i+m.d.userList.from>=numClients){
						break;
					}else{
						strcpy(m.d.userList.users[i],clientList[i+m.d.userList.from]->name);
						m.d.userList.num++;
					}
				}
				m.h.to=m.h.from;
				m.h.from=SERVER_ID;
				sendMess(m.h.to,m);
				break;
			default:
				cout<<"MYERROR:in client not this type mess."<<endl;
				m.h.type=MT_ERROR;
				m.h.from=SERVER_ID;
				m.h.to=ci->id;
				sendMess(m.h.to,m);

				break;
			}
		
		//end deal with message.
	}
	cout<<"exit the clinett(id="<<cs<<")'s thread"<<endl;
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

