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
		TraceVar(len);
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
/*class CDataBase{
private:
	CLinkedList<TypeInfo *> types;
	CTable<CItem *> table;
	int numRows;
	int numCols;
private:
public:
	int getNumTypes(){
		return numCols;
	}
	int getNumRecords(){
		return numRows;
	}
	CDataBase(){
		numRows=0;
		numCols=0;
		table.init(0,0);
	}
	~CDataBase(){
	//interface:
public:
	
	void setType(int typeIndex,char *typeName,int valueLen);
	int getTypeCurMaxValueLen(int typeID);
	void delType(int typeIndex);
	int addRecord();
	int findRecordID(char *typeName,char *value);
	int delRecord(int recordID);
	void inputData();
	TypeInfo * getTypeInfo(int typeIndex);
	void assign(int recordIndex,int typeID,char *value);
	void printAll();
	void printWithoutID();
	void print();
	void print(bool *printRows,bool *printCols);
	int findTypeID(char *typeName);
	int findTypeIndex(char *typeName);
private:
	void printTimes(char ch,int times);
	int findDistinctMinTypeID();
	bool readFile(char *fileName);
	bool saveFile(char *fileName);
	bool serializeIn(fstream &file);
	bool serializeOut(fstream &file);
	//end interface
private:
	void releaseTypes(){
		for(int i=0;i<types.getNum();i++){
			delete types.get(i);
		}
	}
	TypeInfo *getTypeInfo(int typeIndex){
		return types.get(typeIndex);
	}
};*/

/*	
/*	
	
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
	
	void assign(int recordIndex,int typeID,char *value){
		//test
		cout<<"recordIndex="<<recordIndex<<endl;
		cout<<"numRecords="<<numRecords<<endl;
		//end test
			CRecord *record=(records+recordIndex);
			record->assign(typeID,value);
	}
	
	int findTypeIndex(char *typeName){
		for(int i=0;i<numTypes;i++){
			if(strcmp(typeName,typeInfos[i].typeName)==0){
				return i;
			}
		}
		return -1;
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
*/

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
