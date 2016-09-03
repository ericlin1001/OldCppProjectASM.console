#include "CDataBase.h"
/*
	CLinkedList<TypeInfo *> types;
	CTable<CItem *> table;
	int numTypes;
	int numRecords;
	isValTypeIndex
		isValRecordIndex
*/
bool CDataBase::insertRecord(int index){
	if(table.insertRow(index)){
		for(int i=0;i<numTypes;i++){
			if(!table.set(index,i,new CItem()))return false;
		}
		numRecords++;
		return true;
	}
	return false;
}
bool CDataBase::delRecord(int index){
	if(isValRecordIndex(index)){
		for(int i=0;i<numTypes;i++){
			delete table.get(index,i);
		}
		if(table.delRow(index)){
			numRecords--;
			return true;
		}
	}
	return false;
}
bool CDataBase::setItem(int recordIndex,int typeIndex,char *value){
	if(isValTypeIndex(typeIndex) && isValRecordIndex(recordIndex)){
		if(table.get(recordIndex,typeIndex)->assign(value)){
			getType(typeIndex)->updateLen(strlen(value));
			return true;
		}
	}
	return false;
}
char* CDataBase::getItem(int recordIndex,int typeIndex){
	CItem *p=table.get(recordIndex,typeIndex);
	if(p!=NULL){return p->getValue();}
	return (char *)NULL;
}

bool CDataBase::insertType(int index){
	if(types.insert(new TypeInfo(),index)&&table.insertCol(index)){
		for(int i=0;i<numRecords;i++){
			if(!table.set(i,index,new CItem()))return false;
		}
		numTypes++;
		return true;
	}
	return false;
}
bool CDataBase::delType(int index){
	if(isValTypeIndex(index)){
		delete types.get(index);
		types.del(index);
		for(int i=0;i<numRecords;i++){
			delete table.get(i,index);
		}
		if(table.delCol(index)){
			numTypes--;
			return true;
		}
	}
	return false;
}
bool CDataBase::setType(int index,char *name,int maxlen){
	TypeInfo *p=getType(index);
	if(p!=NULL){
		if(p->setName(name)){
			p->setMaxLen(maxlen);
			return true;
		}
	}
	return false;
}
	//
int CDataBase::findType(char *name){//return a index,-1 represent no find.
	TypeInfo *p;
	int i=0;
	for(types.begin(p);!types.end();types.next(p)){
		if(strcmp(name,p->getName())==0)return i;
		i++;
	}
	return -1;
}
int CDataBase::findItem(int typeIndex,char *value){//return a index,-1 represent no find.
	if(isValTypeIndex(typeIndex)){
		for(int i=0;i<numRecords;i++){
			if(strcmp(table.get(i,typeIndex)->getValue(),value)==0)return i;
		}
	}
	return -1;
}
