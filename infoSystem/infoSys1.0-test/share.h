#ifndef SHARE_H
#define SHARE_H
#include<stdlib.h>
#include<iostream>
#include<fstream>
//#include<windows.h>
using namespace std;



#define DEFAULT_MAX_VALUE_LEN 15

#define MAX_LEN_VALUE 30
//
//
void error(char *mess,int type=0);
void warn(char *mess,int type=0);

void error(char *mess,char *mess2,int type=0){
	char buffer[100];
	strcpy(buffer,mess);
	strcat(buffer,mess2);
	cerr<<"Error("<<type<<")"<<mess<<mess2<<endl;
//	MessageBox(NULL,buffer,"Error",0);
	//exit(1);
}
void warn(char *mess,char *mess2,int type=0){
	char buffer[100];
	strcpy(buffer,mess);
	strcat(buffer,mess2);
		cerr<<"Warn("<<type<<")"<<mess<<mess2<<endl;
	//	MessageBox(NULL,buffer,"Warning",0);
}

void error(char *mess,int type){
	error(mess,"",type);
}
void warn(char *mess,int type){
		//cerr<<"Warn("<<type<<")"<<mess<<endl;
	warn(mess,"",type);
}

bool isExistFile(char *fileName){
	if(*fileName=='\n' || *fileName==0)return false;
	ifstream file;
	file.open(fileName,ios::in);
	return !file.fail();
}
void intToStr(int n,char *buffer){
	char *p=buffer;
	if(n==0){*p++='0';*p++=0;return ;}
	while(n){
		*p++=n%10+'0';
		n/=10;
	}
	*p=0;
	p--;
	while(buffer<p){
		char ch=*p;
		*p=*buffer;
		*buffer=ch;
		buffer++;
		p--;
	}
}
int getStr(istream & in,char *str,int len,char delims='\n',char emit=' '){// include 0,that means the max of str is len-1
	char ch;
	len--;
	int count=0;
	while((ch=in.get())==emit);
	while(ch!=delims){
		if(len>0){
			len--;
			*str++=ch;
			count++;
		}
		ch=in.get();
	}
	*str=0;
	return count;
}
char *delBlank(char *str){
	while(*str!=' ' && *str)str++;
	*str=0;
	return str;
}
char* lowerCase(char *src){
	char *p=src;
	while(*src){
		if('A'<=*src && *src<='Z')*src+='a'-'A';
		src++;
	}
	return p;
}
#endif