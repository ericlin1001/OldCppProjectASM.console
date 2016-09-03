#ifndef CASICCLIENT_H
#define CASICCLIENT_H
#include<iostream>
#include<cstring>
#include<vector>
#include<winsock2.h>
#include<cstdlib>
#include<string.h>
#include<string>
#include<fstream>
#include "../definedMess.h"
using namespace std;
#define _CLIENT_TEST
#ifdef CLIENT_TEST
#define Trace(m) cout<<#m"="<<m<<endl;
#else 
#define Trace(m) //cout<<#m"="<<m<<endl;
#endif
//
extern int testCount;
#ifdef CLIENT_TEST
#define testTag cout<<"testTag:"<<testCount++<<endl;
#else
#define testTag //cout<<"testTag:"<<testCount++<<endl;
#endif
#define resetTag testCount=0;
//
#ifndef DLL_FILE
#define DLL_FILE
#endif

#ifdef DLL_FILE
#define DLLDECL __declspec(dllexport)
#else
#define DLLDECL __declspec(dllimport)
#endif

class DLLDECL CBasicClient{

public:
	bool isConn(){return bconn;}
	bool isConnect(){return bconn;}
	void disConn();
	CBasicClient();
	~CBasicClient();
	int init(char *serverIP,unsigned short  port);
protected:
	int sendMess(void* m,int len);
	int recvMess(void *m,int len);
protected:
	SOCKET mySock;
	bool bconn;
};

class DLLDECL CClientTest:public CBasicClient{
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
	void print();
	int recvMess(Message &m);
	int sendMess(Message &m);
	CClientTest();
	~CClientTest();
	int start();
	bool isLogin();
	void pauseThread();
	void resumeThread();
	void lostServer();
	static unsigned long WINAPI threadFun(LPVOID lParam);
	void startRecv(){WaitForSingleObject(hMainSig,INFINITE);}
	void endRecv(){SetEvent(hThreadSig);}
	char *getName(){return name;}
	ID getID(){return id;}
	int getAge(){return age;}
	void login(char *user,char *pass);
	void getUserData();
	void updateUserData();
	void recvWrongMess();
	void getUserDetail(char *user,ID &getid);
	void getUserList();
	void logoff();
	void sendStr(char *str,const ID toID);
};
#endif