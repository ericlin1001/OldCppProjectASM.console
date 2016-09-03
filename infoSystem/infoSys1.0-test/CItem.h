//82
#ifndef CITEM_H
#define CITEM_H
#include"share.h"
#include<iostream>
#include<cstring>
using namespace std;
class CItem{
private:
	char *value;
	int len;
	int maxlen;
public:
	CItem(){
		value=0;
		len=0;
		maxlen=0;
	}
	CItem (CItem &p){
		init(p.maxlen);
		assign(p.value);
	}
	CItem & operator=(CItem &p){
		init(p.maxlen);
		assign(p.value);
		return *this;
	}
	char *getValue(){
		return value;
	}
	//added
	int getValueLen(){
		return len;
	}
	void setMaxSize(int tmaxlen){
		char *buffer=new char[len+1];
		strncpy(buffer,value,len+1);
		init(tmaxlen);
		assign(buffer);
		delete []buffer;
	}
	//end added
	void assign(char *str){
		len=strlen(str);
		if(len>maxlen){
			warn("The len is out of maxlen,so it may lose the data.");
			len=maxlen;
		}
		strncpy(value,str,len+1);
	}
	void inputData(){
		len=getStr(cin,value,maxlen+1);//
	}
	void init(int tmaxlen){
		if(value!=NULL)delete []value;
		value=0;
		maxlen=tmaxlen;
		len=0;
		value=new char[maxlen+1];
		if(value==NULL){
			error("can't allocate the memory");
		}
		memset(value,0,maxlen+1);
	}
	~CItem(){
		if(value!=NULL){
			delete []value;
		}
	}
	bool serializeIn(fstream &file){
		file>>maxlen
			>>len;
		//cout<<"maxlen="<<maxlen<<endl;
		//cout<<"len="<<len<<endl;
		if(value!=NULL)delete []value;
		value=new char[maxlen+1];
		if(value==NULL){
			error("can't allocate the memory");
		}
		if(len!=0)file>>value;
		value[len]=0;
	//	cout<<"value="<<value<<endl;
		return true;
	}
	bool serializeOut(fstream &file){
		file<<maxlen<<endl
			<<len<<endl
			<<value<<endl;
		return true;
	}
	
};
#endif