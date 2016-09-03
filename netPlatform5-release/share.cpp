//#define __saveOrder__
#include "share.h"
bool isExistFile(char *fileName){
	if(*fileName=='\n' || *fileName==0)return false;
	ifstream file;
	file.open(fileName,ios::in);
	return !file.fail();
}
#include<stdio.h>
bool openFile(ofstream &outfile,char *file){
	ifstream infile;
	char *temp=new char[strlen(file)+10];
	strcpy(temp,file);strcat(temp,"-temp");
	if(rename(file,temp)){return false;}
	infile.open(temp,ios::in|ios::binary);
	if(!infile.fail()){
		outfile.open(file,ios::out);
		if(!outfile.fail()){
			while(1){char ch=infile.get();if(infile.eof())break;outfile.put(ch);}
			infile.close();
			if(!remove(temp)){
				return true;
			}
		}
	}
	rename(temp,file);
	return false;
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
bool isBlank(char *str){
	while(*str){
		char ch=*str;
		if(!(ch==' ' || ch=='\n' ||ch=='\r' || ch=='\t')){
		return false;
		}
		str++;
	}
	return true;
}
int getStr(istream & in,char *str,int len,char delims,char emit){// include 0,that means the max of str is len-1
#ifdef __saveOrder__
	char *saveOrder=str;
#endif
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
	//
#ifdef __saveOrder__
#include<fstream>
	ofstream outfile;
	outfile.open("inputOrder.txt",ios::app);
	outfile<<saveOrder<<endl;
	outfile.close();
#endif
	//
	return count;
}
char *delBlank(char *str){
	while(*str==' ' &&*str)str++;
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
