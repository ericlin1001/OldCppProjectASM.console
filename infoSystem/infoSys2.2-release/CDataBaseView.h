#ifndef CDATABASEVIEW_H
#define CDATABASEVIEW_H
#include "CDataBase.h"
#include "CSaveExternal.h"
//if you want to save as external ,please #define __saveExternal__
#include<iomanip>
#include<fstream>
#include<iostream>
#include<cstring>
using namespace std;

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
	bool readFromFile(char *filePath){
		if(isExistFile(filePath)){
			if(db->reset()){
				ifstream infile;
				infile.open(filePath,ios_base::in);
				if(db->serizlIn(infile)){
					infile.close();
					return true;
				}
			}
		}
		return false;
	}
	bool saveAsFile(char *filePath){//ensure the filePath is a avliable path,or maybe error.
		if(*filePath!=0){
			ofstream outfile;
			outfile.open(filePath,ios_base::out);//|ios_base::app);
			db->serizlOut(outfile);
			outfile.close();
			return true;
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