#ifndef CDATABASE_H
#define CDATABASE_H
#include "CSaveExternal.h"
//if you want to save as external ,please #define __saveExternal__
#include "CTable.h"
#include "CLinkedList.h"
#include<cstring>

class TypeInfo:public CSaveExternal{
public:
	#ifdef __saveExternal__
	bool  serizlIn(ifstream &infile){
		infile.read(serial(index));
		infile.read(serial(curMaxLen));
		infile.read(serial(maxLen));
		StrLen len;//include the last char '\0';
		infile.read(serial(len));
		//
		char *temp;
		if((temp=new char[len])==NULL)return false;
		infile.read(temp,len);
		if(name!=NULL)delete []name;
		name=temp;
		updateLen(len-1);//len-1 represent the real len of str.
		
		return true;
	}
	bool  serizlOut(ofstream &outfile){
		outfile.write(serial(index));
		outfile.write(serial(curMaxLen));
		outfile.write(serial(maxLen));
		writeStr(name,outfile);
		return true;
	}
	#endif
	TypeInfo(int tindex=-1){
		//name=NULL;
		name=new char[2];name[0]=0;
		maxLen=0;
		index=tindex;
		curMaxLen=0;
	}
	~TypeInfo(){
		if(name!=NULL)delete []name;
	}
	void updateLen(int addedLen){
		if(addedLen>curMaxLen)curMaxLen=addedLen;
	}
	bool setName(char *tname){
		int len=strlen(tname);
		if(len<=0)len=1;//this protected the len+1>=2
		char *temp;
		if((temp=new char[len+1])==NULL)return false;
		strcpy(temp,tname);
		if(name!=NULL)delete []name;
		name=temp;
		updateLen(len);
		return true;
	}
	int getShowLen(){
		//return curMaxLen;
		return curMaxLen>maxLen? maxLen:curMaxLen;
	}
	char *getName(){return name;}
	void setMaxLen(int a){maxLen=a;}
	int getMaxLen(){return maxLen;}
	int getCurMaxLen(){return curMaxLen;}
	bool assign(char *tname,int tmaxlen,int tindex){
		maxLen=tmaxlen;
		index=tindex;
		return setName(tname);
	}
private:
	char *name;//when init,it contain like that : name[0]=0,
	//name at least consist of two char,or may make error.
	int maxLen;
	int curMaxLen;
public:
	int index;//no use.
	
	//determine the width of the type.
};
#include "share.h"
class CItem:public CSaveExternal{
public:
	#ifdef __saveExternal__
	bool  serizlIn(ifstream &infile){
		StrLen len;//include the last char '\0';
		infile.read(serial(len));
		char *temp;
		if((temp=new char[len])==NULL)return false;
		infile.read(temp,len);
		if(value!=NULL)delete []value;
		value=temp;/**/
		return true;
	}
	bool  serizlOut(ofstream &outfile){
		writeStr(value,outfile);
		return true;
	}
	#endif
	CItem(){
		//value=NULL;
		value=new char[2];value[0]=0;
	}
	~CItem(){
		if(value!=NULL)delete []value;
	}
	bool assign(char *tvalue){
		return setValue(tvalue);
	} 
	bool setValue(char *tvalue){
		if(value!=NULL)delete []value;
		int len=strlen(tvalue);
		if(len<=0)len=1;//this protected the len+1>=2
		if((value=new char[len+1])==NULL)return false;
		strcpy(value,tvalue);
		return true;
	}
	char *getValue(){return value;}
private:
	char *value;
};
class CDataBase:public CSaveExternal{
	private:
	CLinkedList<TypeInfo *> types;
	CTable<CItem *> table;
	int numRecords;
	int numTypes;
private:
	
	bool isValTypeIndex(int index){return 0<=index && index<numTypes;}
	bool isValRecordIndex(int index){return 0<=index && index<numRecords;}
public:
	#ifdef __saveExternal__
	bool  serizlIn(ifstream &infile){
		int readnumTypes,readnumRecords;
		infile.read(serial(readnumTypes));
		infile.read(serial(readnumRecords));
		//
		for(int i=0;i<readnumTypes;i++){
			if(!insertType(i))return false;
			getType(i)->serizlIn(infile);
		}
		for(int row=0;row<readnumRecords;row++){
			if(!insertRecord(row))return false;
			for(int col=0;col<numTypes;col++){
				table.get(row,col)->serizlIn(infile);
			}
		}
		return true;
	}
	bool  serizlOut(ofstream &outfile){
		outfile.write(serial(numTypes));
		outfile.write(serial(numRecords));
		//
		TypeInfo *p;
		for(types.begin(p);!types.end();types.next(p)){
			p->serizlOut(outfile);
		}
		for(int row=0;row<numRecords;row++){
			for(int col=0;col<numTypes;col++){
				table.get(row,col)->serizlOut(outfile);
			}
		}
		return true;
	}
	#endif
	//notice:the index==-1,this mean no
	bool insertRecord(int index);
	bool delRecord(int index);
	bool setItem(int recordIndex,int typeIndex,char *value);
	char* getItem(int recordIndex,int typeIndex);

	bool insertType(int index);
	bool delType(int index);
	bool setType(int index,char *name,int maxlen);
	TypeInfo *getType(int index){return types.get(index);}
	//
	int findType(char *name);//return a index,-1 represent no find.
	int findItem(int typeIndex,char *value);//return a index,-1 represent no find.
	int getNumTypes(){
		return numTypes;
	}
	int getNumRecords(){
		return numRecords;
	}
private:

public:
	bool interchangeRecord(int recorda,int recordb){
		return table.interchangeRow(recorda,recorda);
	}
	CDataBase(){
		numTypes=0;
		numRecords=0;
		table.init(0,0);
	}
	bool reset(){
		int i=0;
		for(i=numRecords-1;i>=0;i--){
			delRecord(i);
		}
		for(i=numTypes-1;i>=0;i--){
			delType(i);
		}
		if(numTypes==0 && numRecords==0 && table.getNumRows()==0 && table.getNumCols()==0)return true;
		return false;
	}
	~CDataBase(){
		reset();
	}
};
#endif

//test cases:
/*CItem *item=new CItem();
	TypeInfo *type=new TypeInfo();

	ofstream outfile;
	outfile.open(filePath,ios_base::out);//|ios_base::app);
	item->setValue("test2589");
	item->serizlOut(outfile);
	type->assign("mytype",15,2);
	type->serizlOut(outfile);
	outfile.close();
	
	ifstream infile;
	infile.open(filePath,ios_base::in);
	item->serizlIn(infile);
	TraceVar(item->getValue());
	type->serizlIn(infile);
	TraceVar(type->index<<type->getName()<<type->getMaxLen()<<type->getCurMaxLen());
	infile.close();
	*/
//test serial in and out cases:
/*CDataBase db;
	CDataBaseView dbView;
	dbView.setDB(&db);
	//
	dbView.printAll();
	//
	/*dbView.addType("Name");
	cout<<"no error"<<endl;
	dbView.addType("QQ");dbView.addType("phhone");
	dbView.addType("eamil");
	dbView.inputData();	dbView.printAll();dbView.inputData();	dbView.printAll();dbView.inputData();	dbView.printAll();
	*/
	/*ofstream outfile;
	outfile.open(filePath,ios_base::out);//|ios_base::app);
	db.serizlOut(outfile);
	outfile.close();

	ifstream infile;
	infile.open(filePath,ios_base::in);
	db.serizlIn(infile);
	infile.close();
	

	dbView.printAll();
	*/
