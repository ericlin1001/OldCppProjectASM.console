#include<iostream>
#include<cstring>
#include<vector>
#include<winsock2.h>
#include<cstdlib>
#include<fstream>
using namespace std;
//
class CClientInfo{
public:
	int id;
	char name[20];
	void print(){
		cout<<"id="<<id<<endl
			<<"name="<<name<<endl;
	}
};
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
	
	return 0;
}