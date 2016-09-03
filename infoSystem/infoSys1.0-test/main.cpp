#include "CDataBase.h"
#include "share.h"
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<cstring>
using namespace std;
typedef void (*POrderFun)();

//constant:
#define DEFFAULT_FILE_NAME "infoSystem.dat"
#define MAX_LEN_ORDER 20
#define MAX_LEN_DESCRIPT 100
const int numOrders=18;

//the interpreter function declare:
int findOrderIndex(char *order);
int choose();
//assistant function declare:
void askIfSave();void showMenu();void saveDataBase();
//order function declare:
void openFile();void menu();void resetAll();void showAll();void showGivenPerson();void showGivenType();void showGiveTypePerson();void addPerson();void addType();void delPerson();void delType();void setPeron();void renameType();void save();void quit();void help();void clear();void changePrintAfter();


//global variables:
bool isQuit=false;
char filePath[100]=DEFFAULT_FILE_NAME;//the file path
CDataBase dataBase;//store the main data
bool printAfter=false;
char descriptOrders[numOrders][MAX_LEN_DESCRIPT+1]=
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
		"Open a file.",
};
POrderFun orderFuns[numOrders]={menu,resetAll,showAll,showGivenPerson,showGivenType,showGiveTypePerson,addPerson,addType,delPerson,delType,setPeron,renameType,save,quit,help,clear,changePrintAfter,openFile};
char accessOrders[numOrders][MAX_LEN_ORDER+1]={"menu","resetAll","showAll","showGivenPerson","showGivenType","search","addPerson","addType","delPerson","delType","setPerson","resetType","save","quit","help","clear","printAfter","openFile"};

//assistant function:
void askIfSave(){
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
}
void showMenu(){
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
}
void saveDataBase(){
	dataBase.saveFile(filePath);
}
//end assistant function.

//order function:
void openFile(){
	save();
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
	
}
void resetAll(){
	char ch[2];
	while(1){
		cout<<"Warning:This operation will delete all data!"<<endl;
		cout<<"Continue?(Y/N)";
		getStr(cin,ch,2);
		if(ch[0]=='Y' || ch[0]=='y'){
			cout<<"Creating a new dataBase..."<<endl;
			CDataBase temp;
			temp.addType("Name",8);temp.addType("Phone",11);temp.addType("QQ",10);
			temp.saveFile(filePath);
			dataBase.readFile(filePath);
			cout<<"success!"<<endl;
			break;
		}else if(ch[0]=='N' || ch[0]=='n'){
			cout<<"Haven't resetAll."<<endl;
			break;
		}
	}
}
void save(){
	saveDataBase();
	cout<<"Save successfully!"<<endl;
}
void  clear(){
	system("cls");
}
void menu(){
	clear();
	showMenu();
}
void help(){
	showMenu();
}
void showAll(){
	dataBase.printWithoutID();
}
void  showGivenPerson(){
	cout<<"Name:";
	char name[MAX_LEN_VALUE+1];
	getStr(cin,name,MAX_LEN_VALUE);
	int index=dataBase.findRecordID("Name",name);
	if(index==-1){
		cout<<"No this person."<<endl;
	}else{
		dataBase.setRowMask(false);
		dataBase.setColMask(true);
		dataBase.getRowMask()[index]=true;
		dataBase.getColMask()[0]=false;
		dataBase.print();
	}
} 
void  showGivenType(){
	cout<<"Name of type:";
	char name[MAX_LEN_VALUE+1];
	getStr(cin,name,MAX_LEN_VALUE);
	int index=dataBase.findTypeID(name);
	//cout<<"index:"<<index<<endl;
	if(index==-1){
		cout<<"No this type."<<endl;
	}else{
		dataBase.setColMask(false);
		dataBase.setRowMask(true);
		dataBase.getColMask()[1]=true;//show name
		dataBase.getColMask()[index]=true;
		dataBase.print();
	}	
} 
void  showGiveTypePerson(){
	cout<<"Name:";
	char name[MAX_LEN_VALUE+1];
	getStr(cin,name,MAX_LEN_VALUE);
	int rowindex=dataBase.findRecordID("Name",name);
	if(rowindex==-1){
		cout<<"No this person."<<endl;return ;
	}
	cout<<"Name of type:";
	char typeName[MAX_LEN_VALUE+1];
	getStr(cin,typeName,MAX_LEN_VALUE);
	int colindex=dataBase.findTypeID(typeName);
	if(colindex==-1){
		cout<<"No this type."<<endl;
		return ;
	}
	dataBase.setRowMask(false);
	dataBase.setColMask(false);
	dataBase.getColMask()[1]=true;//show name
	dataBase.getColMask()[colindex]=true;
	dataBase.getRowMask()[rowindex]=true;
	dataBase.print();
} 
void addPerson(){ 
	dataBase.inputData();
	askIfSave();
} 
void addType(){
	char typeName[MAX_LEN_VALUE+1];
	int valueLen;
	char lenBuffer[10];
	while(1){
		cout<<"The length of value:";
		getStr(cin,lenBuffer,10);
		valueLen=atoi(lenBuffer);
		//cout<<"valueLen="<<valueLen<<endl;
		if(0<valueLen && valueLen<=MAX_LEN_VALUE)break;
		cout<<"The length of value must be between 1 and "<<MAX_LEN_VALUE<<endl;
	}
	cout<<"The name of type("<<valueLen<<"):";
	//cin.get();
	getStr(cin,typeName,valueLen+1);
	dataBase.addType(typeName,valueLen);
	askIfSave();
} 
void changePrintAfter(){
	printAfter=!printAfter;
	cout<<"printAfter="<<(printAfter?"true":"false")<<endl;
}
void delPerson(){
	cout<<"Name:";
	char name[MAX_LEN_VALUE+1];
	getStr(cin,name,MAX_LEN_VALUE);
	int index=dataBase.findRecordID("Name",name);
	if(index==-1){
		cout<<"No this person."<<endl;return ;
	}
	dataBase.delRecord(index);
	cout<<"Delete person:"<<name<<" success!"<<endl;
	askIfSave();
	return;
} 
void delType(){
	cout<<"The name of type:";
	char typeName[MAX_VALUE_LEN+1];
	getStr(cin,typeName,MAX_VALUE_LEN+1);
	int index=dataBase.findTypeIndex(typeName);
	if(index==-1){
		cout<<"No this type."<<endl;
	}else if(index==0){
		cout<<"Can't delete type:ID."<<endl;
	}else if(index==1){
		cout<<"Can't delete type:Name."<<endl;
	}else{
		dataBase.delType(index);
		cout<<"Delete type:"<<typeName<<" successfully!"<<endl;
		askIfSave();
	}
}
void setPeron(){
	cout<<"Name:";
	char name[MAX_LEN_VALUE+1];
	getStr(cin,name,MAX_LEN_VALUE+1);
	int index=dataBase.findRecordID("Name",name);
	if(index==-1){
		cout<<"No this person."<<endl;return ;
	}
	cout<<"Change To(no input means no change):"<<endl;
	int numtype=dataBase.getNumTypes();
	char buffer[MAX_VALUE_LEN+1];
	for(int i=1;i<numtype;i++){
		TypeInfo *pinfo=dataBase.getTypeInfo(i);
		cout<<pinfo->typeName<<"("<<pinfo->valueLen<<"):";
		getStr(cin,buffer,pinfo->valueLen+1);
		if(*buffer!='\n' && *buffer!=0)dataBase.assign(index,pinfo->id,buffer);
	}
	askIfSave();
}
void renameType(){
//	cout<<"renameType"<<endl;
	cout<<"The name of type:";
	char typeName[MAX_VALUE_LEN+1];
	getStr(cin,typeName,MAX_VALUE_LEN+1);
	int index=dataBase.findTypeIndex(typeName);
	if(index==-1){
		cout<<"No this type."<<endl;
	}else if(index==0){
		cout<<"Can't rename type:ID."<<endl;
	}else if(index==1){
		cout<<"Can't rename type:Name."<<endl;
	}else{
		//
		int valueLen;
		char lenBuffer[10];
		int minValueLen=dataBase.getTypeCurMaxValueLen(dataBase.getTypeInfo(index)->id);
		while(1){
			cout<<"The new length of value(no input means no change):";
			getStr(cin,lenBuffer,10);
			if(*lenBuffer=='\n' || *lenBuffer==0){
				valueLen=dataBase.getTypeInfo(index)->valueLen;
				break;
			}
			valueLen=atoi(lenBuffer);
			if(minValueLen<=valueLen && valueLen<=MAX_LEN_VALUE)break;
			cout<<"The length of value must be between "<<minValueLen<<" and "<<MAX_LEN_VALUE<<endl;
		}
		cout<<"The new name of type("<<valueLen<<")(no input means no change):";
		getStr(cin,typeName,valueLen+1);
		dataBase.setType(index,typeName,valueLen);
		cout<<"Reset type:"<<typeName<<" successfully!"<<endl;
		askIfSave();
	}
}
void quit(){
//	save();
//	cout<<"exiting..."<<endl;
//	isQuit=true;
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
//end interpreter function.

//main
int main(){
/**/	while(1){
		if(isExistFile(filePath)&&dataBase.readFile(filePath))break;
		cout<<"Can't open the file:"<<filePath<<endl;
		cout<<"Do you want to creat a new file("<<filePath<<")?(Y/N):";
		char ch[2];
		getStr(cin,ch,2);
		if(ch[0]=='Y' || ch[0]=='y'){
			dataBase.addType("Name",8);dataBase.addType("Phone",11);dataBase.addType("QQ",10);
			dataBase.saveFile(filePath);
		}else if(ch[0]=='N' || ch[0]=='n'){
			cout<<"Please input the path of the data file:";
			getStr(cin,filePath,990);
			if(*filePath=='\n' || *filePath==0){
				strcpy(filePath,DEFFAULT_FILE_NAME);
			}
		}
	}
	menu();	
	quit();
	showAll();
	while(!isQuit){
		choose();//execute the order.
		if(printAfter)showAll();
	}
	saveDataBase();
	return 0;
}

