//#define __test__ //this determine whether is test mode.
#include "OrderFun.h"

//the interpreter function declare:
int findOrderIndex(char *order);int choose();

//global variables:
char *key;//[]="mykey";

//main
int main(){
	//init:
	key=new char[10];strcpy(key,"012345768");
	initAll();//output the first init face.
	help();
	while(!isQuit){
		choose();//execute the order.
		if(printAfter)showAll();
	}
	delete []key;

	return 0;
}

//the interpreter function
int findOrderIndex(char *order){
	lowerCase(order);
	char buffer[MAX_LEN_ORDER+1];
	for(int i=0;i<numOrders;i++){
		strcpy(buffer,&accessOrders[i][0]);
		if(strcmp(lowerCase(buffer),order)==0)return i;
	}
	return -1;
}
int choose(){
	char choice[MAX_LEN_ORDER+1];
	cout<<"Order_$:";
	getStr(cin,choice,MAX_LEN_ORDER);
	delBlank(choice);
	int order=findOrderIndex(choice);
	if(order==-1){
		cout<<"No this order!"<<endl;
	}else{
		orderFuns[order]();
	}
	return order;
}
//end interpreter function.


//assistant function:
bool showMenu(){
	cout<<"infoSystem:"<<endl;
	int starlen=75;
	int maxOrderLen=0;
	int i;
	for( i=0;i<numOrders;i++){
		int len=strlen(accessOrders[i]);
		maxOrderLen=len>maxOrderLen?len:maxOrderLen;
	}
	cout<<setfill('*')<<setw(starlen)<<"*"<<endl;
	for( i=0;i<numOrders;i++){
		cout<<setfill(' ')<<setw(maxOrderLen+1)<<accessOrders[i]<<" : "<<descriptOrders[i]<<endl;
	}
	cout<<setfill('*')<<setw(starlen)<<"*"<<endl;
	cout<<setfill(' ');
	return true;
}
bool saveDataBase(){
	return dataBase.saveAsEncryptedFile(filePath,key,strlen(key),tag);
}
bool readDataBase(){
	return dataBase.readFromEncryptedFile(filePath,key,strlen(key),tag);
}
bool initDB(){//just add some type.
	if(db==NULL)db=new CDataBase();
	if(db->reset()){
		dataBase.addType("Name",10);dataBase.addType("QQ",10);dataBase.addType("Phone",18);dataBase.addType("Email",30);
		return true;
	}
	return false;
}
bool initAll(){
	if(db!=NULL)delete db;
	db=new CDataBase();
	dataBase.setDB(db);
	while(1){
		cout<<"Please input the path of a data file:("<<DEFFAULT_FILE_NAME<<")";
		getStr(cin,filePath,990);
		if(*filePath=='\n' || *filePath==0){
			strcpy(filePath,DEFFAULT_FILE_NAME);
		}
		if(!isExistFile(filePath)){
			cout<<"File doesn't exsit!\nDo you want to create the file:"<<filePath<<"?(Y/N):";
			char ch[2];
			getStr(cin,ch,2);
			if(ch[0]=='Y' || ch[0]=='y'){
				cout<<"Creating the file:"<<filePath<<" ..."<<endl;
				initDB();
				saveDataBase();
			}else{
				cout<<"Haven't create the file:"<<filePath<<"!"<<endl;
			}
		}
		if(isExistFile(filePath)){
			cout<<"Opening "<<filePath<<" ..."<<endl;
			if(!readDataBase()){
				cout<<"Open the file:"<<filePath<<" failed!"<<endl;
				cout<<"Maybe the file has been destroyed,you can delete it and creat a new one."<<endl;
				//break;
			}else{//only this is success.
				cout<<"Open the file:"<<filePath<<" successfully!"<<endl;
				break;
			}
		}
	}
	return true;
}
//end assistant function.