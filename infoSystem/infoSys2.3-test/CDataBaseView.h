#ifndef CDATABASEVIEW_H
#define CDATABASEVIEW_H
#include "EncryptFun.h"
#include "CDataBase.h"
#include "CSaveExternal.h"
//if you want to save as external ,please #define __saveExternal__
#include<iomanip>
#include<fstream>
#include<iostream>
#include<cstring>
using namespace std;
#define DEFAULT_TAG "InfoSystem's file"
class CDataBaseView:public CSaveExternal{//this class operate the dataBase and show or input of dataBase.
	//this class just offers a friendly interface for programmer.
private:
	CDataBase *db;//ensure db!=NULL,because the following function don't examine whether is==NULL.
public:
#ifdef __saveExternal__
	bool  serizlIn(ifstream &infile){
		if(db->serizlIn(infile)){
			return true;
		}
		return false;
	}
	bool  serizlOut(ofstream &outfile){
		if(db->serizlOut(outfile)){
			return true;
		}
		return false;
	}
	bool readFromFile(char *filePath,const char *tag=DEFAULT_TAG){
		if(isExistFile(filePath)){
			if(testTag(filePath,tag,strlen(tag))){
				if(db->reset()){
				ifstream infile;
				infile.open(filePath,ios_base::in);
				if(db->serizlIn(infile)){
					infile.close();
					return true;
				}
				}
			}
		}
		return false;
	}
	bool saveAsFile(char *filePath,const char *tag=DEFAULT_TAG){//ensure the filePath is a avliable path,or maybe error.
		if(*filePath!=0){
			ofstream outfile;
			outfile.open(filePath,ios_base::out);//|ios_base::app);
			if(db->serizlOut(outfile)){
				outfile.close();
				if(setTag(filePath,tag,strlen(tag))){
					return true;
				}
			}
			
		}
		return false;
	}
	bool readFromEncryptedFile(char *filePath,const char *key,int keysize,const char *tag=DEFAULT_TAG){
		char *temp=new char[strlen(filePath)+strlen("-temp")+1];
		strcpy(temp,filePath);strcat(temp,"-temp");
		if(decryptFile(filePath,temp,key,keysize)){
			if(readFromFile(temp,tag) && remove(temp)==0){
				return true;
			}
		}
		return false;
	}
	bool saveAsEncryptedFile(char *filePath,const char *key,int keysize,const char *tag=DEFAULT_TAG){//ensure the filePath is a avliable path,or maybe error.
		if(saveAsFile(filePath,tag)){
			if(encryptFile(filePath,filePath,key,keysize)){
				return true;
			}
		}
		return false;
	}
#endif
	void print(bool *printRows,bool *printCols);
	CDataBaseView(CDataBase *pDB=NULL){
		db=pDB;
		lenColMasks=lenRowMasks=5;
		colMask=new bool[lenColMasks];
		rowMask=new bool[lenRowMasks];
	}
	~CDataBaseView(){
		delete []colMask;
		delete []rowMask;
	}
	void setDB(CDataBase *pDB){
		db=pDB;
	}
	void print(){

		print(rowMask,colMask);
	}

	void printAll(){
		setColMask(true);
		setRowMask(true);
		print();
	}
	void addType(char *typeName,int valueLen=15);
	void inputData();
	
public:
	//deal with the mask
	void setColMask(bool b){
		memset(getColMask(),b,lenColMasks);
		
	}
	void setRowMask(bool b){
		memset(getRowMask(),b,lenRowMasks);
	}
	bool *getColMask(){
		if(db->getNumTypes() >= lenColMasks){
			bool *temp=new bool[lenColMasks*2];
			memcpy(temp,colMask,lenColMasks);
			delete []colMask;
			colMask=temp;
			lenColMasks*=2;
		}
		return colMask;
	}
	bool *getRowMask(){//for change.
		if(db->getNumRecords() >= lenRowMasks){
			bool *temp=new bool[lenRowMasks*2];
			memcpy(temp,rowMask,lenRowMasks);
			delete []rowMask;
			rowMask=temp;
			lenRowMasks*=2;
		}
		return rowMask;
	}
private:
	void printTimes(char ch,int times){
		for(int i=0;i<times;i++)
			cout<<ch;
	}
	void printStr(char *str,int printLen){
		while(*str && printLen>0){
			cout.put(*str);
			str++;printLen--;
		}
	}
	bool *colMask,*rowMask;
	int lenColMasks,lenRowMasks;
};
#endif