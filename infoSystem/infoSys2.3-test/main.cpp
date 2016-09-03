//#define __test__ //this determine whether is test mode.
#define __saveExternal__//this determine whether the class can be saved in external file.

#include "CDataBaseView.h"
#include "CDataBase.h"

#include "share.h"

#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<cstring>
#include<iomanip>

using namespace std;
typedef bool (*POrderFun)();

//constant:
#define MAX_INPUT_BUFFER 100
#define DEFFAULT_FILE_NAME "infoSystem.dat"
#define MAX_NUM_ORDERS 30
#define MAX_LEN_ORDER 20
#define MAX_LEN_DESCRIPT 100
#define MAX_SIZE_TYPE MAX_INPUT_BUFFER
const int numOrders=17;
char key[]="mykey";
//the interpreter function declare:
int findOrderIndex(char *order);
int choose();
//assistant function declare:
bool askIfSave();bool showMenu();bool saveDataBase();bool initDB();
//order function declare:
bool openFile();bool menu();bool resetAll();bool showAll();bool showGivenPerson();bool showGivenType();bool showGiveTypePerson();bool addPerson();bool addType();bool delPerson();bool delType();bool setPeron();bool renameType();bool save();bool quit();bool help();bool clear();bool changePrintAfter();


//global variables:
bool isQuit=false;
char filePath[100]=DEFFAULT_FILE_NAME;//the file path
CDataBase *db;
CDataBaseView dataBase;//we assume that the first col is the index.
bool printAfter=false;
char descriptOrders[][MAX_LEN_DESCRIPT+1]=
{
		"Return to menu.",//menu
		"ResetAll.",//resetAll
		"Show all the infomation.",//showAll
		"Given the person,and show the infomation about it.",//showGivenPerson
		"Given the information's type and show just about this.",//showGivenType
		"Search given person and given information's type.",//showGiveTypePerson
		"Add a person.",//addPerson
		"Add an information type.",//addType
		"Delete a person.",//delPerson
		"Delete an information type.",//delType
		"Set the information of a given person.",//setPeron
		"Reset the the name of type and the len of type.",
		"Save.",//saveDataBase
		"Save and quit.",//quit
		"Show the menu.",
		"Clear the screen.",
		"Set whether to printAll after every action.",
};
POrderFun orderFuns[]={menu,resetAll,showAll,showGivenPerson,showGivenType,showGiveTypePerson,addPerson,addType,delPerson,delType,setPeron,renameType,save,quit,help,clear,changePrintAfter};
char accessOrders[][MAX_LEN_ORDER+1]={"menu","resetAll","showAll","showGivenPerson","showGivenType","search","addPerson","addType","delPerson","delType","setPerson","resetType","save","quit","help","clear","printAfter"};

//assistant function:
bool askIfSave(){
	cout<<"Do you want to save now?(Y/N)";
	char ch[2];
	getStr(cin,ch,2);
	if(ch[0]=='Y' || ch[0]=='y'){
		save();
	}else if(ch[0]=='N' || ch[0]=='n'){
		cout<<"The data have not been saved."<<endl;
	}else{
		askIfSave();
	}
	return true;
}
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
	return dataBase.saveAsEncryptedFile(filePath,key,sizeof(key));
}
//end assistant function.

//order function:
bool openFile(){
/*	save();
//askIfSave();
cout<<"file path:";
char buffer[100];
getStr(cin,buffer,100);
if(!isExistFile(buffer)){
cout<<"The file don't exist."<<endl;
return ;
}else{
if(dataBase.readFile(buffer)){
cout<<"Open the file successfully."<<endl;
strcpy(filePath,buffer);
}else{
cout<<"Can't open the file."<<endl;
dataBase.readFile(filePath);
}
}
*/	
	return true;
}
bool resetAll(){
	char ch[2];
	while(1){
		cout<<"Warning:This operation will delete all data!"<<endl;
		cout<<"Continue?(Y/N)";
		getStr(cin,ch,2);
		if(ch[0]=='Y' || ch[0]=='y'){
			cout<<"Creating a new dataBase..."<<endl;
			initDB();
			if(!saveDataBase())return false;
			cout<<"success!"<<endl;
			break;
		}else if(ch[0]=='N' || ch[0]=='n'){
			cout<<"Haven't resetAll."<<endl;
			break;
		}
	}
	return true;
}
bool save(){
	if(saveDataBase()){
		cout<<"Save successfully!"<<endl;
		return true;
	}else{
		cout<<"Save failed!"<<endl;
		return false;
	}
}
bool  clear(){
	system("cls");
	return true;
}
bool menu(){
	clear();
	showMenu();
	return true;
}
bool help(){
	showMenu();
	return true;
}
bool showAll(){
	dataBase.printAll();
	return true;
}
bool  showGivenPerson(){//we assume the first col is the key index.
	cout<<db->getType(0)->getName()<<":";
	char buffer[MAX_INPUT_BUFFER];
	getStr(cin,buffer,MAX_LEN_VALUE);
	int index=db->findItem(0,buffer);
	if(index==-1){
		cout<<"No this person."<<endl;
	}else{
		dataBase.setRowMask(false);
		dataBase.setColMask(true);
		dataBase.getRowMask()[index]=true;
		dataBase.print();
	}
	return true;
} 
bool  showGivenType(){
	cout<<"Name of type:";
	char buffer[MAX_INPUT_BUFFER];
	getStr(cin,buffer,MAX_LEN_VALUE);
	int index=db->findType(buffer);
	if(index==-1){
		cout<<"No this type."<<endl;
	}else{
		dataBase.setColMask(false);
		dataBase.setRowMask(true);
		dataBase.getColMask()[0]=true;//show name
		dataBase.getColMask()[index]=true;
		dataBase.print();/**/
	}	
	return true;
} 
bool  showGiveTypePerson(){
	cout<<db->getType(0)->getName()<<":";
	char buffer[MAX_INPUT_BUFFER];
	getStr(cin,buffer,MAX_LEN_VALUE);
	
	int rowindex=db->findItem(0,buffer);
	if(rowindex==-1){
		cout<<"No this person."<<endl;return false;
	}
	cout<<"Name of type:";
	getStr(cin,buffer,MAX_INPUT_BUFFER);
	
	int colindex=db->findType(buffer);
	if(colindex==-1){
		cout<<"No this type."<<endl;
		return false;
	}
	cout<<"The \""<<buffer<<"\" of \""<<db->getItem(rowindex,0)<<"\" is :";
	cout<<db->getItem(rowindex,colindex)<<endl;
	return true;
} 
bool addPerson(){ 
	dataBase.inputData();
	askIfSave();
	return true;
} 
bool addType(){
	char typeName[MAX_LEN_VALUE+1];
	int valueLen;
	char lenBuffer[10];
	while(1){
		cout<<"The max size of type:";
		getStr(cin,lenBuffer,10);
		valueLen=atoi(lenBuffer);
		
		if(2<=valueLen && valueLen<=MAX_SIZE_TYPE)break;
		cout<<"The length of value must be between 2 and "<<MAX_SIZE_TYPE<<endl;
	}
	cout<<"The name of type("<<valueLen<<"):";
	getStr(cin,typeName,valueLen+1);
	dataBase.addType(typeName,valueLen);
	askIfSave();
	return true;
} 
bool changePrintAfter(){
	printAfter=!printAfter;
	cout<<"printAfter="<<(printAfter?"true":"false")<<endl;
	return true;
}
bool delPerson(){
	cout<<db->getType(0)->getName()<<":";
	char buffer[MAX_INPUT_BUFFER];
	getStr(cin,buffer,MAX_LEN_VALUE);
	int index=db->findItem(0,buffer);
	if(index==-1){
		cout<<"No this person."<<endl;return true;
	}
	db->delRecord(index);
	cout<<"Delete person:"<<buffer<<" success!"<<endl;
	askIfSave();/**/
	return true;
} 
bool delType(){
	cout<<"Name of type:";
	char buffer[MAX_INPUT_BUFFER];
	getStr(cin,buffer,MAX_LEN_VALUE);
	int index=db->findType(buffer);
	if(index==-1){
		cout<<"No this type."<<endl;
	}else if(index==0){
		cout<<"You can't delete the first type:"<<buffer<<endl;
	}else{
		db->delType(index);
		cout<<"Delete type:"<<buffer<<" successfully!"<<endl;
		askIfSave();
	}
	return true;
}
bool setPeron(){
	cout<<db->getType(0)->getName()<<":";
	char buffer[MAX_INPUT_BUFFER];
	getStr(cin,buffer,MAX_LEN_VALUE);
	int index=db->findItem(0,buffer);
	if(index==-1){
		cout<<"No this person."<<endl;return false;
	}
	cout<<"(Note:No input means no change.)"<<endl;

	int numtype=db->getNumTypes();
	
	for(int i=0;i<numtype;i++){
		cout<<db->getType(i)->getName()<<"("<<db->getType(i)->getMaxLen()<<"):";
		cout<<"("<<db->getItem(index,i)<<")"<<endl;
		cout<<"Change to:";
		getStr(cin,buffer,MAX_INPUT_BUFFER);
		if(*buffer!='\n' && *buffer!=0) db->setItem(index,i,buffer);
	}
	askIfSave();/**/
	return true;
}
bool renameType(){
	//	cout<<"renameType"<<endl;
	cout<<"Name of type:";
	char buffer[MAX_INPUT_BUFFER];
	getStr(cin,buffer,MAX_LEN_VALUE);
	int index=db->findType(buffer);
	if(index==-1){
		cout<<"No this type."<<endl;
		return false;
	}else if(index==0){
		cout<<"Note:You had better not to rename this type."<<endl;
	}
	int valueLen;
	char lenBuffer[10];//when addtype control the maxsize.
	cout<<"(Note:No input means no change.)"<<endl;
	while(1){cout<<"The max size of type:("<<db->getType(index)->getMaxLen()<<")"<<endl;
	cout<<"Change to:";
	getStr(cin,lenBuffer,10);
	if(*lenBuffer=='\n' || *lenBuffer==0){
		valueLen=db->getType(index)->getMaxLen();
		break;
	}
	valueLen=atoi(lenBuffer);
	if(2<=valueLen && valueLen<=MAX_SIZE_TYPE)break;
	cout<<"The length of value must be between 2 and "<<MAX_SIZE_TYPE<<endl;
	}	
	cout<<"Name of type("<<valueLen<<"):("<<db->getType(index)->getName()<<")"<<endl;
	cout<<"Change to:";
	getStr(cin,buffer,MAX_INPUT_BUFFER);
	if(*buffer!='\n' && *buffer!=0)db->setType(index,buffer,valueLen);
	cout<<"Rename type successfully!"<<endl;
	askIfSave();
	return true;	
}
bool quit(){
	save();
	cout<<"exiting..."<<endl;
	isQuit=true;
	return true;
}
//end order functions.

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
bool initDB(){//just add some type.
	if(db->reset()){
		dataBase.addType("Name",10);dataBase.addType("QQ",10);dataBase.addType("Phone",18);dataBase.addType("Email",30);
		return true;
	}
	return false;

}
//end interpreter function.

//main
int main(){
	//init:
	db=new CDataBase();
	dataBase.setDB(db);
	//end init.
	/**/while(1){
	bool isExist=isExistFile(filePath);
	if(isExist){
		cout<<"Do you want to open this file:\""<<filePath<<"\"?(Y/N):";
	}else{
		cout<<"Do you want to create this file:\""<<filePath<<"\"?(Y/N):";
	}
	char ch[2];
	getStr(cin,ch,2);
	if(ch[0]=='Y' || ch[0]=='y'){
		if(isExist){
			if(!dataBase.readFromEncryptedFile(filePath,key,sizeof(key))){
				cout<<"Can't open the file:\""<<filePath<<"\""<<endl;
				cout<<"Maybe the file has been destroyed,you can delete it."<<endl;
			}else{
				break;
			}
		}else{
			initDB();
			dataBase.saveAsFile(filePath);
			break;
		}
	}else if(ch[0]=='N' || ch[0]=='n'){
		cout<<"Please input the path of the data file:";
		getStr(cin,filePath,990);
		if(*filePath=='\n' || *filePath==0){
			strcpy(filePath,DEFFAULT_FILE_NAME);
		}
	}
	}
	help();	/**/
#ifdef __test__
	showAll();
#endif
	//
	while(!isQuit){
		choose();//execute the order.
		if(printAfter)showAll();
		#ifdef __test__
		//test:
		/*{
		
		  dataBase.print();
		}*/
		#endif
		
	}
	saveDataBase();
	
	return 0;
}
