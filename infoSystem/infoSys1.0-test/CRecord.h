//113
#ifndef CRECORD_H
#define CRECORD_H
#include "CItem.h"
#include "share.h"

#define MAX_TYPES_NUM 30

class CRecord{
public:
	CRecord(){
		maxSize=MAX_TYPES_NUM;
		items=0;
		size=0;
		avaliIDs=0;
		init();
	}
	void init(){
		if(maxSize<=2)error("in CRecord::init() maxSize<=2");
		if(items!=NULL)delete []items;
		items=new CItem[maxSize];
		if(items==NULL){
			error("can't allocate the memory");
		}
		if(avaliIDs!=NULL)delete []avaliIDs;
		avaliIDs=new int[maxSize];
		if(avaliIDs==NULL){
			error("can't allocate the memory");
		}
	}
	CRecord(CRecord &p){
		*this=p;
	}
	CRecord & operator=(CRecord &p){
		maxSize=p.maxSize;
		 size=p.size;
		 init();
		 int i=0;
		 for(i=0;i<size;i++){
			avaliIDs[i]=p.avaliIDs[i];
			items[avaliIDs[i]]=p.items[avaliIDs[i]];
		 }
		 return *this;
	}
	~CRecord(){
		if(items!=NULL){
			delete []items;
		}
	}
	CItem *getItem(int id){
		if(isValidID(id)){
			return &items[id];
		}else{
			error("in CRecord::getItem() The itemID is not a registered ID.");
		}
		return NULL;
	}
	void inputData(int itemID){
		if(getItem(itemID)!=NULL){
			items[itemID].inputData();
		}
	}
	bool isValidID(int id){
		for(int i=0;i<size;i++){
			if(id==avaliIDs[i])return true;
		}
		return false;
	}
	void addItem(int id,int valuelen){
		if(0<=id && id<maxSize){
			avaliIDs[size++]=id;//register the id.
			items[id].init(valuelen);
		}else{
			error("in CRecord::addItem() id out of range.");
		}
	}
	void delItem(int id){
		//cout<<"id in delItem()="<<id<<endl;
		if(0<=id && id<maxSize){
			//avaliIDs[size]=id;//unregister the id.
			int i;
			for(i=0;i<size;i++){
				if(avaliIDs[i]==id){
					break;
				}
			}
			if(i==size)error("in CRecord::delItem() the id is not in the registered list..");
			for(int j=i;j<size-1;j++){
				avaliIDs[j]=avaliIDs[j+1];
			}
			size--;
		}else{
			error("in CRecord::delItem() id out of range.");
		}
	}
	void assign(int id,char *str){
		items[id].assign(str);
	}
	bool serializeIn(fstream &file){
		file>>maxSize
			>>size;
		//cout<<"maxSize="<<maxSize<<endl;
		//cout<<"size="<<size<<endl;
		int i=0;
		if(avaliIDs!=NULL)delete [] avaliIDs;
		if((avaliIDs=new int[maxSize])==NULL)error("can't allocate the memory.");
		//cout<<"avaliIDS:";
		for(i=0;i<size;i++){
			file>>avaliIDs[i];
			//cout<<avaliIDs[i]<<',';
		}
		for(i=0;i<size;i++){
			getItem(avaliIDs[i])->serializeIn(file);
		}
		return true;
	}
	bool serializeOut(fstream &file){
		file<<maxSize<<endl
			<<size<<endl;
		int i=0;
		for(i=0;i<size;i++){
			file<<avaliIDs[i]<<endl;
		}
		for(i=0;i<size;i++){
			getItem(avaliIDs[i])->serializeOut(file);
		}
		return true;
	}
private:
	int maxSize;
	int size;
	CItem *items;
	int *avaliIDs;
};
#endif