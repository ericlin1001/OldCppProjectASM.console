//#define __test__
#define __saveExternal__
#include "CDataBaseView.h"
#include "CDataBase.h"
#include <iostream>
using namespace std;
#define DEFAULT_BUFFER_LEN 20
int main(){
	//init
	CDataBase db;
	CDataBaseView dbv;
	dbv.setDB(&db);//this is very important,and you must set this before any operation of dbv.
	//end init
	dbv.addType("Name");dbv.addType("QQ");
	//
	char buffer[DEFAULT_BUFFER_LEN];
	while(1){
		cout<<"order:init,read,save,addRecord,addType,find"<<endl;
		getStr(cin,buffer,DEFAULT_BUFFER_LEN);/*this just like cin>>buffer;And you had better use this if need.*/
		lowerCase(buffer);
		if(strcmp(buffer,"save")==0){
			if(dbv.saveAsEncryptedFile("saveData.dat","mypass",strlen("mypass")))cout<<"save successfully"<<endl;
			else cout<<"save failed"<<endl;
		}else if(strcmp(buffer,"read")==0){
			db.reset();
			if(dbv.readFromEncryptedFile("saveData.dat","mypass",strlen("mypass")))cout<<"read successfully"<<endl;
			else cout<<"read failed"<<endl;
		}else  if(strcmp(buffer,"init")==0){
			db.reset();
			dbv.addType("Name");dbv.addType("QQ");
		}else  if(strcmp(buffer,"find")==0){
			cout<<db.getType(0)->getName()<<":";getStr(cin,buffer,DEFAULT_BUFFER_LEN);
			int index=db.findItem(0,buffer);
			if(index>=0){
				cout<<"have found:"<<endl;
				dbv.setColMask(true);
				dbv.setRowMask(false);
				dbv.getRowMask()[index]=true;
				dbv.print();
				cout<<"find successfully"<<endl;
			}else cout<<"no find"<<endl;
		}else  if(strcmp(buffer,"addtype")==0){
			db.insertType(db.getNumTypes());
			//
			cout<<"typeName:"<<endl;getStr(cin,buffer,DEFAULT_BUFFER_LEN);
			db.getType(db.getNumTypes()-1)->setName(buffer);
			//
			cout<<"maxLen:"<<endl;getStr(cin,buffer,DEFAULT_BUFFER_LEN);
			int maxlen=atoi(buffer);if(maxlen<=0 || maxlen>50)maxlen=15;
			db.getType(db.getNumTypes()-1)->setMaxLen(maxlen);
		}else if(strcmp(buffer,"addrecord")==0){
			dbv.inputData();
		}else{
			cout<<"No this order!"<<endl;
		}
		dbv.printAll();//print the data in table form.
	}/**/
	return 0;
}
