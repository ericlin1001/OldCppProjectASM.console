/*#define _CLIENT_TEST

#ifdef CLIENT_TEST
#else
#endif



#include<iostream>
#include<cstring>
#include<vector>
#include<winsock2.h>
#include<cstdlib>
#include<string.h>
#include<string>
#include<fstream>
using namespace std;
#include "../share.h"
#include "../definedMess.h"*/
#include "CBasicClient.h"
#include<string.h>
#include<string>
#include<fstream>
using namespace std;

#define SERVER_INFO "serverInfo.txt"

void help(){
	cout<<"all order:\nconnect,login,logoff,getUsers,myprofile,send,exit."<<endl;
}

int main(){
	CClientTest c;
	/*
	ID id_buffer;
	//
	int orderCount=0;
	fstream infile;
	infile.open(SERVER_INFO);
	if(infile.fail()){
		cerr<<"open "SERVER_INFO" failed!"<<endl;
		return 0;
	}
	char serverIP[20];unsigned short port;
	infile>>serverIP>>port;
#ifdef CLIENT_TEST
	cout<<"server IP:"<<serverIP<<endl
		<<"port     :"<<port<<endl;
#else
#endif
	help();
	
	while(1){
		orderCount++;
		#ifdef CLIENT_TEST
	cout<<"orderCount:"<<orderCount<<endl;
#else
#endif
		char buffer[100];
		cout<<"$>";
		getStr(cin,buffer,100);
		lowerCase(buffer);delBlank(buffer);
	
		
		//temp_buffer
		if(strcmp(buffer,"login")==0||strcmp(buffer,"l")==0){
			char user[MAX_LEN_USERNAME];
			char pass[MAX_LEN_PASS];

			if(!c.isConn()){

			cout<<"connectting,please wait..."<<endl;
			if( c.init(serverIP,port)!=MYSUCCESS){cerr<<"Can't find server."<<endl;continue;}
			cout<<"Connect successfully!"<<endl;
			c.start();
}
			cout<<"user:";getStr(cin,user,MAX_LEN_USERNAME);
			cout<<"password:";getStr(cin,pass,MAX_LEN_PASS);
			c.login(user,pass);
		}else if(strcmp(buffer,"exit")==0){
			c.logoff();
			exit(0);
		}else if(strcmp(buffer,"logoff")==0){
			c.logoff();
			cout<<"You have logged off."<<endl;
		}else if(strcmp(buffer,"connect")==0||strcmp(buffer,"c")==0){
			if(c.isConn()){cout<<"have connected!"<<endl;continue;}
			cout<<"connectting,please wait..."<<endl;
			if( c.init(serverIP,port)!=MYSUCCESS){cerr<<"Can't find server."<<endl;continue;}
			cout<<"Connect successfully!"<<endl;
			c.start();
		}else if(strcmp(buffer,"getusers")==0||strcmp(buffer,"g")==0){
			c.getUserList();
		}else if(strcmp(buffer,"myprofile")==0){
			cout<<" id:"<<c.getID()
			<<" name:"<<c.getName()
			<<" age:"<<c.getAge()
			<<endl;
		}else if(strcmp(buffer,"send")==0){
			char toname[20];
			while(1){
			//	cout<<"Blank mean the previous chatter."<<endl;
cout<<"# means the end of message."<<endl;
				cout<<"to(name):";getStr(cin,toname,20);
				if(*toname=='\0'){
					cout<<"no input name"<<endl;
					if(id_buffer!=0){
						break;
					}
				}else{
					c.getUserDetail(toname,id_buffer);break;
				}
			}
			
			if(id_buffer==INVALID_ID){cout<<"can't find user:"<<toname<<endl;continue;}
			char str[MAX_LEN_CHATTEXT];
			
			cout<<"message("<<MAX_LEN_CHATTEXT<<"):";
			//
			int len=0;
			str[len++]=cin.get();
			while(len<MAX_LEN_CHATTEXT-1){
				str[len++]=cin.get();
				if(str[len-1]=='#'){
					if(str[len-2]=='\\' ){
						str[len-2]='#';
						len--;
					}else if(str[len-2]!='\\'){
						len--;
						break;
					}
					
				}
			
			}
			str[len]=0;
			c.sendStr(str,id_buffer);
			cin.get();
			Sleep(300);
		}else if(strcmp(buffer,"help")==0||strcmp(buffer,"?")==0||strcmp(buffer,"h")==0){
			help();
		}else if(isBlank(buffer)){
			//do nothing....
		//	cout<<"buffer("<<buffer<<")"<<endl;
		}else{
			cout<<"no this order:"<<buffer<<endl;
		}
	}
	*/
	return 0;
}

