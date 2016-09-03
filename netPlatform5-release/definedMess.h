#ifndef DEFINEMESS_H
#define DEFINEMESS_H

#define _MESS_TEST
#ifdef MESS_TEST
#else
#endif

#include<iostream>
#include "share.h"
#include<winsock2.h>
using namespace std;
//user define:
#define ID unsigned int
#define INVALID_ID -1
#define SERVER_ID 0
//
#define DEFAULT_PORT 6789
#define FILE_USERPASS "userpass.txt"

//
#define MAX_LEN_SHOWNAME		20
#define MAX_LEN_USERNAME		20
#define MAX_LEN_PASS			20
#define MAX_LEN_CHATTEXT		200
#define MAX_LEN_PREFIX			40
#define MAX_NUM_USERLIST		10
//

//
#define MYSUCCESS 0
#define MYERROR -1

#define UINT unsigned int
//
//Message type defined
struct MessageHeader{
	int type;
	ID from;//id,SOCKET
	ID to;//id,SOCKET
	UINT dataLen;//remmember the len() must be invoked int the end.
	int certification;//not use.
	void print(){
		cout<<"Messageheader:"<<endl
			<<"type="<<type<<endl
			<<"from id:"<<from<<endl
			<<"to id:"<<to<<endl
			<<"dataLen:"<<dataLen<<endl
			<<"certification:"<<certification<<endl;
	}
};
union MessageData{
	struct LoginData{
		char user[MAX_LEN_USERNAME];
		char pass[MAX_LEN_PASS];
		ID id;
		int certification;
		bool isSuccess;
		UINT len(){return sizeof(LoginData);}
		void print(){
			cout<<" user:"<<user
				<<" pass:"<<pass
				<<" id:"<<id
				<<" isSuccess:"<<(isSuccess?"true":"false")
				<<" len:"<<len()
				<<endl;
		}
	} login;
	struct LogoffData{
		bool isSuccess;
		UINT len(){return sizeof(LogoffData);}
	} logoff;
	struct ChatData{
		char prefix[MAX_LEN_PREFIX];
		char text[MAX_LEN_CHATTEXT];
		UINT len(){return MAX_LEN_PREFIX+strlen(text)+1;}
	} chat;
	struct ExampleData{
		int a;
		char str[10];
		UINT len(){return sizeof(ExampleData);}
	} example;
	struct UserDetailData{
		ID id;
		char name[MAX_LEN_USERNAME];
		UINT len(){return sizeof(UserDetailData);}
	}userDetail;
	struct UserListData{
		int from;
		int num;
		char users[MAX_NUM_USERLIST][MAX_LEN_USERNAME];
		UINT len(){return sizeof(from)+sizeof(num)+MAX_LEN_USERNAME*num;}
	}userList;
	struct UserDataData{
#define USER_DATA_READ		0
#define USER_DATA_WRITE		1
		char name[MAX_LEN_SHOWNAME];
		int age;
		int type;
		bool isSuccess;
		UINT len(){return sizeof(UserDataData);}
	}userData;
};
struct Message{
	MessageHeader h;
	MessageData d;
};
//MESSAGE.TYPE
#define MT_ERROR					-1
#define MT_LOGIN					0
#define MT_LOGOFF					1
#define MT_CHAT						2
#define MT_PASSDIRECT				3
#define MT_EXAMPLE					4
#define MT_GETUSERDETAIL			5
#define MT_GETUSERLIST				6
#define MT_GETUSERDATA				7
//

#ifdef MESS_TEST
#define Test(m) cout<<#m"="<<(m)<<endl;
#else
#define Test(m) //cout<<#m"="<<(m)<<endl;
#endif



//
template<class T>
class MyVector{
public:
	typedef T* iterator;
	typedef const T CT;
private:
	typedef unsigned int sizt_t;
#define UNIT sizeof(T)
	size_t s;
	iterator head;
	size_t max;
public:
	
	
	iterator begin(){
		return head;
	}
	MyVector(){
		max=1;
		s=0;
		head=NULL;
		expand();
	}
	void del(const T t){
		for(iterator i=begin();i!=end();i++){
			if(*i==t){
				memcpy(i,i+1,((end()-i)-1)*UNIT);
				s--;
				return;
			}
		}
	}
	void del(const sizt_t p){
		iterator i=begin()+p;
		memcpy(i,i+1,((end()-i)-1)*UNIT);
		s--;
	}
	void erase(const T i){
		del(i);
	}
	void erase(const sizt_t i){
		del(i);
	}
	
	~MyVector(){
		if(head!=NULL){
			delete []head;
		}
	}
	iterator end(){
		return head+s;
	}
	size_t size(){
		return s;
	}
	void push_back(CT & t){
		memcpy(end(),&t,sizeof(T));
		s++;
		if(s>=max){
			expand();
		}
	}
	T &back(){
		return *(head+s-1);
	}
	T &at(size_t i ){
		return *(head+i);
	}
	T &operator[](size_t i){
		return at(i);
	}
	bool empty(){
		return s==0;
	}
private:
	void expand(){
		iterator temp=new T[max*2];
		if(head!=NULL){
			memcpy(temp,head,max*sizeof(T));
			delete []head;
		}
		head=temp;
		max*=2;
	}
};
//


//
class CClientInfo{
#define FILE_USER_DATA "userData.txt"
	//don't need saving
public:
	SOCKET id;//u_int
	char ip[20];
	unsigned  short port;
	int certification;//no use.
private:
	//need saving.
public:
	char name[MAX_LEN_SHOWNAME];
	char user[MAX_LEN_USERNAME];//connect with database;
	char pass[MAX_LEN_PASS];
	int age;
private:
	bool isLogin;
	streamoff fileOff;
public:
	bool updateFile(){
		if(fileOff==-1){
			cout<<"error:updateFile"<<endl;
			return false;
		}
		ofstream file;
		if(!openFile(file,FILE_USER_DATA)){
			cout<<"Error:open "FILE_USER_DATA" fail!"<<endl;
			return false;
		}
		file.seekp(fileOff,ios::beg);
		save(file);
		file.close();
		return true;
	}
	bool load(char *user,char *pass){
		ifstream infile;
		infile.open(FILE_USER_DATA,ios::in|ios::out|ios::app);
		if(infile.fail()){
			cout<<"open "FILE_USER_DATA" fail!"<<endl;
			return false;
		}
		while(1){
			read(infile);
			if(infile.eof())break;
			if(strcmp(this->user,user)==0 && strcmp(this->pass,pass)==0){
				fileOff=infile.tellg()-(streamoff)saveSize();
				infile.close();
				return true;
			}
		}
		infile.close();
		return false;
	}
	bool login(char *user,char *pass){
		if(load(user,pass)){
			if(!this->isLogin){
				isLogin=true;
				if(updateFile()){
					return true;
				}else{
					isLogin=false;
					return false;
				}
			}else{
				print();
				cout<<"\b have been online,you can't login!"<<endl;
				return false;
			}
		}else{
			cout<<"can't find user: "<<user<<" pass:"<<pass<<endl;
		}
		return false;
	}
#define serial(m) (char*)&m,sizeof(m)
	unsigned int save(ofstream &outfile){
		outfile.write(user,sizeof(user));
		outfile.write(pass,sizeof(pass));
		outfile.write(name,sizeof(name));
		outfile.write(serial(isLogin));
		outfile.write(serial(age));
		return saveSize();
	}
	unsigned int read(ifstream &infile){
		infile.read(user,sizeof(user));
		infile.read(pass,sizeof(pass));
		infile.read(name,sizeof(name));
		infile.read(serial(isLogin));
		infile.read(serial(age));
		return saveSize();
	}
	unsigned int saveSize(){
		return sizeof(user)+sizeof(pass)+sizeof(name)+sizeof(isLogin)+sizeof(age);
	}
	bool getIsLogin(){
		return isLogin;
	}
	bool logoff(){
		isLogin=false;
		if(updateFile()){
			return true;
		}else{
			isLogin=true;
			return false;
		}
	}
	void print(){
		cout
			
			<<" user:"<<user
			<<" pass:"<<pass
			
			<<" name:"<<name
			<<" age:"<<age
			<<" state:"<<(isLogin ? "login":"logoff")
			<<" id:"<<id
			<<endl;
	}
	CClientInfo(){
		memset(name,0,sizeof(user));
		memset(user,0,sizeof(user));
		isLogin=false;
		fileOff=-1;
		age=-1;
	}
};



#endif