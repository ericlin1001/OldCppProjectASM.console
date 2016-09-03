//#define __test__
#include "EncryptFun.h"

#include<fstream>

#include<iostream>

//#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
using namespace std;
#define serial(m) (char *)&m,sizeof(m)
#define DEFAULT_KEY_LEN 8
#define DEFAULT_KEY "12345678"
typedef long FileLen;

#ifdef __test__
#define TraceVar(var) cout<<#var<<"="<<var<<endl;
#define Trace(mess) cout<<mess<<endl;
#else
#define TraceVar(var)
#define Trace(mess) 
#endif
int readFromFile(ifstream &infile,char *buffer,int len);
void encrypt(const char *src,char *dest,int strSize,const char *key,int keysize ){//
	for(int i=0;i<strSize;i++){
		char ch=*(src+i);
		ch^=key[i%keysize];
		*(dest+i)=ch;
	}
}
void encrypt(const char *src,char *dest,int size){
	encrypt(src,dest,size,DEFAULT_KEY,DEFAULT_KEY_LEN);
}
void decrypt(const char *src,char *dest,int strSize,const char *key,int keysize ){//
	for(int i=0;i<strSize;i++){
		char ch=*(src+i);
		ch^=key[i%keysize];
		*(dest+i)=ch;
	}
}
void decrypt(const char *src,char *dest,int size){
	decrypt(src,dest,size,DEFAULT_KEY,DEFAULT_KEY_LEN);
}


bool encryptFile(const char  *srcfile,const char  *destfile,const char *key,int keysize){
	if(strcmp(srcfile,destfile)==0){
		char *temp=new char[strlen(srcfile)+strlen("-encrypted")+2];
		temp=strcpy(temp,srcfile);temp=strcat(temp,"-encrypted");
		if(encryptFile(srcfile,temp,key,keysize)){
			if(remove(srcfile)==0){
				if(!rename(temp,srcfile)){
					delete []temp;
					return true;
				}
			}
		}
		delete []temp;
		return false;
	}
	ifstream infile;
    infile.open(srcfile,ios::binary);
	if(infile.fail())return false;
	ofstream outfile;
	outfile.open(destfile,ios::binary);
	
	char *buffer=new char[keysize];
	int readlen=0;
	while((readlen=readFromFile(infile,buffer,keysize))!=0){
		encrypt(buffer,buffer,readlen,key,keysize);
		outfile.write(buffer,readlen);
	}
	delete []buffer;
	//
	infile.close();
	outfile.close();
	return true;
}
bool decryptFile(const char  *srcfile,const char  *destfile,const char *key,int keysize){
	if(strcmp(srcfile,destfile)==0){
		char *temp=new char[strlen(srcfile)+strlen("-encrypted")+2];
		temp=strcpy(temp,srcfile);temp=strcat(temp,"-encrypted");
		if(decryptFile(srcfile,temp,key,keysize)){
			if(remove(srcfile)==0){
				if(!rename(temp,srcfile)){
					delete []temp;
					return true;
				}
			}
		}
		delete []temp;
		return false;
	}
	ifstream infile;
    infile.open(srcfile,ios::binary);
	if(infile.fail())return false;
	ofstream outfile;
	outfile.open(destfile,ios::binary);
	
	char *buffer=new char[keysize];
	int readlen=0;
	while((readlen=readFromFile(infile,buffer,keysize))!=0){
		decrypt(buffer,buffer,readlen,key,keysize);
		outfile.write(buffer,readlen);
	}
	delete []buffer;
	//
	infile.close();
	outfile.close();
	return true;
}
bool encryptFile(const char  *srcfile,const char  *destfile){
	return encryptFile(srcfile,destfile,DEFAULT_KEY,sizeof(DEFAULT_KEY));
}
bool decryptFile(const char  *srcfile,const char  *destfile){
	return decryptFile(srcfile,destfile,DEFAULT_KEY,sizeof(DEFAULT_KEY));
}
bool filecmp(const char  *fileName1,const char  *fileName2){
	ifstream fileA,fileB;
	fileA.open(fileName1);fileB.open(fileName2);
	if(fileA.fail() || fileB.fail())return false;
	while(fileA.get()==fileB.get() && !fileA.eof() && !fileB.eof());
	bool b= fileA.eof() && fileB.eof();
	fileA.close();fileB.close();
	return b;
}
#define TAG_FLAG_LEN 8

bool setTag(const char *fileName,const char *tagStr,int tagsize){
	char tagflag[TAG_FLAG_LEN];
	FileLen fileLen=0;
	//read
	ifstream infile;
	infile.open(fileName,ios::in|ios::binary);
	if(infile.fail())return false;
	int i=0;
	for(i=0;i<TAG_FLAG_LEN;i++){
		tagflag[i]=0;
	}
	while(1){
		char ch=infile.get();if(infile.eof())break;
		tagflag[fileLen%TAG_FLAG_LEN]^=ch;
		fileLen++;
	}
	TraceVar(fileLen)
		for(i=0;i<tagsize;i++){
			tagflag[i%TAG_FLAG_LEN]^=tagStr[i];
		}
		infile.close();/**/
		//
		//write:
		ofstream outfile;
		outfile.open(fileName,ios::app|ios::binary);
		if(outfile.fail())return false;
		outfile.write(tagStr,tagsize);//5
		outfile.write(tagflag,TAG_FLAG_LEN);//8
		outfile.write(serial(fileLen));//4
		//add 17 char in the end of file
		outfile.close();
		return true;
}
bool testTag(const char *fileName,const char *tagStr,int tagsize){
	char tagflag[TAG_FLAG_LEN];
	FileLen fileLen=0;
	
	//read
	ifstream infile;
	infile.open(fileName,ios::in|ios::binary);
	if(infile.fail())return false;
	//get the tag info:
	FileLen getFileLen=0;char getTagflag[TAG_FLAG_LEN];char *getTagStr=new char[tagsize+1];
	infile.seekg(-(int)(sizeof(getFileLen)+TAG_FLAG_LEN+tagsize),ios::end);
	infile.read(getTagStr,tagsize);
	infile.read(getTagflag,TAG_FLAG_LEN);
	infile.read(serial(getFileLen));
	//trace
	TraceVar(getFileLen);

	//
	/**/infile.seekg(0,ios::beg);
	FileLen filebeg=infile.tellg();
	TraceVar(filebeg);
	infile.seekg(0,ios::end);
	FileLen fileend=(long)infile.tellg();
	TraceVar(fileend);
	fileLen=fileend-filebeg;
	//while(

	TraceVar(fileLen);
	//ensure the file len
	
	if(fileLen==(getFileLen+TAG_FLAG_LEN+tagsize+sizeof(getFileLen))){
		Trace("check filelen ok");
		//ensure the tagStr

		getTagStr[tagsize]=0;
		TraceVar(getTagStr);
		TraceVar(tagStr);
		if(strncmp(tagStr,getTagStr,tagsize)==0){
			
		Trace("check tagStr ok");
			int i=0;
			for(i=0;i<TAG_FLAG_LEN;i++){
				tagflag[i]=0;
			}
			infile.seekg(0,ios::beg);
			for(i=0;i<getFileLen;i++){
				tagflag[i%TAG_FLAG_LEN]^=infile.get();
			}
			for(i=0;i<tagsize;i++){
				tagflag[i%TAG_FLAG_LEN]^=tagStr[i];
			}
			//ensure the tagflag
			if(strncmp(tagflag,getTagflag,TAG_FLAG_LEN)==0){
				Trace("check tagflag ok");
				delete []getTagStr;
				infile.close();
				return true;
			}
		}
	}
	
	delete []getTagStr;
	infile.close();
	return false;
}
bool removeTag(const char *fileName,const char *tagStr,int tagsize){
	if(!testTag(fileName,tagStr,tagsize))return false;
	FileLen fileLen=0;
	//get filelen
	ifstream infile;
	infile.open(fileName,ios::in|ios::binary);
	if(infile.fail())return false;
	infile.seekg(-(int)sizeof(fileLen),ios::end);
	infile.read(serial(fileLen));
	infile.close();
	TraceVar(fileLen);
	//end get filelen;

	//set len of file
	int fh;
	if( (fh = open(fileName,O_RDWR))!= -1 )
	{
		if(chsize( fh,fileLen )==0)return true;
		close(fh);
	}
	return false;
}
//
int readFromFile(ifstream &infile,char *buffer,int len){
	int count=0;
	while(1){
		*buffer++=infile.get();
		if(infile.eof())break;
		count++;
		if(count>=len){break;};
	}
	return count;
}