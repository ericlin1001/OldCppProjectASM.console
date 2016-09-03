//337
#ifndef CDATABASE_H
#define CDATABASE_H
#include "CRecord.h"
#include "CItem.h"
#include<iomanip>
#include<fstream>
#include<cstring>
using namespace std;

#define MAX_VALUE_LEN 50
#define MAX_RECORDS_NUM 100

class TypeInfo{
private:
public:
	char *typeName;
	int id;//recode the address.
	int valueLen;
	bool serializeIn(fstream &file){
		file>>id
			>>valueLen;
		//cout<<"id="<<id<<endl;
		//cout<<"valueLen="<<valueLen<<endl;
		int namelen=0;
		file>>namelen;
		//cout<<"namelen="<<namelen<<endl;
		if(typeName!=NULL)delete []typeName;
		typeName=new char[namelen+1];
		if(typeName==NULL)error("can't allocate the memory!");
		if(namelen!=0)file>>typeName;
		//cout<<"typeName="<<typeName<<endl;
		typeName[namelen]=0;
		return true;
	}
	bool serializeOut(fstream &file){
		file<<id<<endl
			<<valueLen<<endl
			<<strlen(typeName)<<endl
			<<typeName<<endl;
		return true;	
	}
	void assign(char *str,int len,int tid){
		int namelen=strlen(str);
		if(typeName!=NULL)delete [] typeName;
		if((typeName=new char[namelen+1])==NULL)error("can't allocate the memory");
		strcpy(typeName,str);
		//
		if(0<len && len<=MAX_VALUE_LEN){
			valueLen=len;
		}else{
			error("in TypeInfo::assign() valueLen is out of range.");
		}
		if(0<=tid){
			id=tid;
		}else{
			cout<<"error:id="<<tid<<endl;	
			error("in TypeInfo::assign() id is not a valid id.");
		}
	}
	TypeInfo(){
		typeName=0;
		valueLen=0;
		id=-1;
	}
	TypeInfo(TypeInfo &p){
		assign(p.typeName,p.valueLen,p.id);
	}
	TypeInfo &operator=(TypeInfo &p){
		assign(p.typeName,p.valueLen,p.id);
		return *this;
	}
	~TypeInfo(){
		if(typeName!=NULL) delete []typeName;
	}
};

class CDataBase{
public:
	CDataBase(){
		records=0;
		typeInfos=0;
		numTypes=0;
		numRecords=0;
		pCurrentID=0;
		maxNumRecords=MAX_RECORDS_NUM;
		maxNumTypes=MAX_TYPES_NUM;
		//
		typeInfos=new TypeInfo[maxNumTypes];
		if(typeInfos==NULL){
			error("can't allocate the memory");
		}
		records=new CRecord[maxNumRecords];
		if(records==NULL){
			error("can't allocate the memory");
		}
		colMask=new bool[maxNumRecords];
		if(colMask==NULL){
			error("can't allocate the memory");
		}
		rowMask=new bool[maxNumRecords];
		if(rowMask==NULL){
			error("can't allocate the memory");
		}
		//init:
		addType("ID",5);
	}
	int getNumTypes(){
		return numTypes;
	}
	int getNumRecords(){
		return numRecords;
	}
	bool readFile(char *fileName){
		fstream file;
		file.open(fileName,ios::in);
		if(!file){
			warn("Error:Can't open the file:",fileName);
			return false;
		}
		if(!serializeIn(file))warn("serializeIn() can't read the file:",fileName);
		return true;
	}
	bool saveFile(char *fileName){
		fstream file;
		file.open(fileName,ios::out);
		if(!file){
			cout<<"Error:Can't open the file:"<<fileName<<endl;
			return false;
		}
		if(!serializeOut(file))warn("serializeOut() can't write the file:",fileName);
		return true;
	}
	~CDataBase(){
		if(typeInfos!=NULL)delete []typeInfos;
		if(records!=NULL)delete []records;
	}
	bool serializeIn(fstream &file){
		char startflag;//$
		char endflag;//#
		file>>startflag;//cout<<"startflag="<<startflag<<endl;
		if(startflag!='$'){
			warn("starflag");return false;
		}
		file>>numTypes;//cout<<"numTypes="<<numTypes<<endl;
		file>>maxNumTypes;//cout<<"maxNumTypes="<<maxNumTypes<<endl;
		file>>numRecords;//cout<<"numRecords="<<numRecords<<endl;
		file>>maxNumRecords;//cout<<"maxNumRecords="<<maxNumRecords<<endl;
		file>>pCurrentID;
		int i=0;
		for(i=0;i<numTypes;i++){
			if(!typeInfos[i].serializeIn(file)){
				warn("typeInfos[i].serizlizeIn()");return false;
			}
		}
		for(i=0;i<numRecords;i++){
			if(!records[i].serializeIn(file)){
				warn("records[i].serizlizeIn()");return false;
			}
		}
		file>>endflag;
		if(endflag!='#'){
			warn("endflag");return false;
		}
		return true;
	}
	bool serializeOut(fstream &file){
		char startflag='$';
		char endflag='#';
		file<<startflag<<endl
			<<numTypes<<endl
			<<maxNumTypes<<endl
			<<numRecords<<endl
			<<maxNumRecords<<endl
			<<pCurrentID<<endl;
		int i=0;
		for(i=0;i<numTypes;i++){
			if(!typeInfos[i].serializeOut(file))return false;
		}
		for(i=0;i<numRecords;i++){
			if(!records[i].serializeOut(file))return false;
		}
		file<<endflag<<endl;	
		return true;
	}
	void addType(char *typeName,int valueLen=15){
		if(numTypes>maxNumTypes){
			error("need to expand the maxNumTypes!");
		}
		typeInfos[numTypes].assign(typeName,valueLen,findDistinctMinTypeID());
		CRecord *precord=records;
		for(int i=0;i<numRecords;i++){
			precord=records+i;
			precord->addItem(typeInfos[numTypes].id,typeInfos[numTypes].valueLen);
		}
		numTypes++;
	}
	int getTypeCurMaxValueLen(int typeID){
		CRecord *precord=records;
		int i;
		int t=0;
		for(i=0;i<numRecords;i++){
			precord=records+i;
			int len=precord->getItem(typeID)->getValueLen();
			t=len>t?len:t;
		}
		return t;
	}
	void setType(int typeIndex,char *typeName,int valueLen){
		if(!(0<=typeIndex && typeIndex<numTypes)){
			warn("no this type!");return;
		}
		int i;
		CRecord *precord=records;
		TypeInfo *pinfo=typeInfos+typeIndex;
		if(valueLen<getTypeCurMaxValueLen(pinfo->id)){
			warn("This operation may lose data!");
		}	
		pinfo->assign(typeName,valueLen,pinfo->id);
		for(i=0;i<numRecords;i++){
			precord=records+i;
			precord->getItem(pinfo->id)->setMaxSize(valueLen);
		}
	}
	void delType(int typeIndex){
		if(!(0<=typeIndex && typeIndex<numTypes)){
			warn("no this type!");return;
		}
		CRecord *precord=records;
		int i;
		for(i=0;i<numRecords;i++){
			precord=records+i;
			precord->delItem(typeInfos[typeIndex].id);
		}
		for(i=typeIndex;i<numTypes-1;i++){
			typeInfos[i]=typeInfos[i+1];
		}
		numTypes--;
	}
	int addRecord(){
		if(numRecords>maxNumRecords){
			error("need to expand the maxNumRecords!");
		}
		CRecord *precord=records+numRecords;
		TypeInfo *pinfo;
		for(int i=0;i<numTypes;i++){
			pinfo=typeInfos+i;
			precord->addItem(pinfo->id,pinfo->valueLen);
		}
		
		char buffferid[10];
		intToStr(pCurrentID++,buffferid);//
		precord->assign(0,buffferid);//initilizing id.
		numRecords++;
		return numRecords-1;
	}
	int findRecordID(char *typeName,char *value){
		int typeID=findTypeID(typeName);
		for(int j=0;j<numRecords;j++){
			if(strcmp(records[j].getItem(typeID)->getValue(),value)==0)return j;
		}
		return -1;
	}
	int delRecord(int recordID){
		if(!(0<=recordID && recordID<numRecords)){
			return -1;
		}
		for(int i=recordID;i<numRecords-1;i++){
			records[i]=records[i+1];
		}
		numRecords--;
		return recordID;
	}
	void inputData(){
		int i;
		CRecord *newRecord=records+addRecord();
		cout<<"Input the data:"<<endl;
		for(i=1;i<numTypes;i++){
			TypeInfo *pinfo=typeInfos+i;
			cout<<pinfo->typeName<<"("<<pinfo->valueLen<<"):";
			newRecord->getItem(pinfo->id)->inputData();
		}
		
	}
	TypeInfo * getTypeInfo(int typeIndex){
		return 	typeInfos+typeIndex;
	};
	void assign(int recordIndex,int typeID,char *value){
		//test
		cout<<"recordIndex="<<recordIndex<<endl;
		cout<<"numRecords="<<numRecords<<endl;
		//end test
			CRecord *record=(records+recordIndex);
			record->assign(typeID,value);
	}
	void printAll(){
		setColMask(true);
		setRowMask(true);
		print();
	}
	void printWithoutID(){
		setColMask(true);
		setRowMask(true);
		getColMask()[0]=false;
		print(rowMask,colMask);
	}
	void print(){
		print(rowMask,colMask);
	}
	void print(bool *printRows,bool *printCols){
		int i=0;
		int lenOfCols=1;
		TypeInfo *pinfo;
		for(i=0;i<numTypes;i++){
			pinfo=typeInfos+i;
			if(printCols[pinfo->id]){
				lenOfCols+=pinfo->valueLen+1;
			}
		}
		//start print;
		printTimes('-',lenOfCols);cout<<endl;//print --------
		//print typename
		cout<<'|';
		for(i=0;i<numTypes;i++){
			pinfo=typeInfos+i;
			if(printCols[pinfo->id]){
				cout<<setw(pinfo->valueLen)<<pinfo->typeName<<'|';
			}
		}
		cout<<endl;
		printTimes('-',lenOfCols);cout<<endl;//print --------
		//print the records.
		int j=0;
		CRecord *pRecord;//
		for(j=0;j<numRecords;j++){
			if(printRows[j]){
			pRecord=records+j;//get the record of j line.
			cout<<'|';
			for(i=0;i<numTypes;i++){
					pinfo=typeInfos+i;
			if(printCols[pinfo->id]){
					cout<<setw(pinfo->valueLen)<<pRecord->getItem(pinfo->id)->getValue()<<'|';
				}
			}
			cout<<endl;
			printTimes('-',lenOfCols);cout<<endl;//print --------
			}
		}
	}
	int findTypeID(char *typeName){
		for(int i=0;i<numTypes;i++){
			if(strcmp(typeName,typeInfos[i].typeName)==0){
				return typeInfos[i].id;
			}
		}
		return -1;
	}
	int findTypeIndex(char *typeName){
		for(int i=0;i<numTypes;i++){
			if(strcmp(typeName,typeInfos[i].typeName)==0){
				return i;
			}
		}
		return -1;
	}
private:
	void printTimes(char ch,int times){
		for(int i=0;i<times;i++)
			cout<<ch;
	}
	int findDistinctMinTypeID(){
	
		bool *hasid=new bool[numTypes+1];
		int i;
		for( i=0;i<=numTypes;i++){
			hasid[i]=false;
		}
		for( i=0;i<numTypes;i++){
			hasid[typeInfos[i].id]=true;
		}
		for( i=0;i<=numTypes;i++){
			if(!hasid[i])return i;
		}
		error("in CDataBase::findDistinctMinTypeID().");
		return -1;
	}
public:
	//deal with the mask
	void setColMask(bool b){
		memset(colMask,b,maxNumTypes);
	}
	void setRowMask(bool b){
		memset(rowMask,b,maxNumRecords);
	}
	bool *getColMask(){
		return colMask;
	}
	bool *getRowMask(){
		return rowMask;
	}
public:
	
	
private:
	bool *colMask;
	bool *rowMask;
	int pCurrentID;
	int maxNumTypes;int maxNumRecords;
	int numRecords;
	int numTypes;
	CRecord *records;//
	TypeInfo *typeInfos;//decide the orders of the items,the id decide the location.
};
#endif