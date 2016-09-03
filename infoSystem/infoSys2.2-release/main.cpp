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
typedef void (*POrderFun)();

//constant:
#define MAX_INPUT_BUFFER 100
#define DEFFAULT_FILE_NAME "infoSystem.dat"
#define MAX_NUM_ORDERS 30
#define MAX_LEN_ORDER 20
#define MAX_LEN_DESCRIPT 100
#define MAX_SIZE_TYPE MAX_INPUT_BUFFER
const int numOrders=17;

//the interpreter function declare:
int findOrderIndex(char *order);
int choose();
//assistant function declare:
void askIfSave();void showMenu();void saveDataBase();void initDB();
//order function declare:
void openFile();void menu();void resetAll();void showAll();void showGivenPerson();void showGivenType();void showGiveTypePerson();void addPerson();void addType();void delPerson();void delType();void setPeron();void renameType();void save();void quit();void help();void clear();void changePrintAfter();


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
	}/**/
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
	dataBase.saveAsFile(filePath);/**/
}
//end assistant function.

//order function:
void openFile(){
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
}
void resetAll(){
	char ch[2];
	while(1){
		cout<<"Warning:This operation will delete all data!"<<endl;
		cout<<"Continue?(Y/N)";
		getStr(cin,ch,2);
		if(ch[0]=='Y' || ch[0]=='y'){
			cout<<"Creating a new dataBase..."<<endl;
			initDB();
			dataBase.saveAsFile(filePath);
			cout<<"success!"<<endl;
			break;
		}else if(ch[0]=='N' || ch[0]=='n'){
			cout<<"Haven't resetAll."<<endl;
			break;
		}
	}/**/
}
void save(){
	saveDataBase();
	cout<<"Save successfully!"<<endl;/**/
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
	dataBase.printAll();
}
void  showGivenPerson(){//we assume the first col is the key index.
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
	}/**/
} 
void  showGivenType(){
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
} 
void  showGiveTypePerson(){
	cout<<db->getType(0)->getName()<<":";
	char buffer[MAX_INPUT_BUFFER];
	getStr(cin,buffer,MAX_LEN_VALUE);
	
	int rowindex=db->findItem(0,buffer);
	if(rowindex==-1){
		cout<<"No this person."<<endl;return ;
	}
	cout<<"Name of type:";
	getStr(cin,buffer,MAX_INPUT_BUFFER);
	
	int colindex=db->findType(buffer);
	if(colindex==-1){
		cout<<"No this type."<<endl;
		return ;
	}
	cout<<"The \""<<buffer<<"\" of \""<<db->getItem(rowindex,0)<<"\" is :";
	cout<<db->getItem(rowindex,colindex)<<endl;
} 
void addPerson(){ 
	dataBase.inputData();
	askIfSave();/**/
} 
void addType(){
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
} 
void changePrintAfter(){
	printAfter=!printAfter;
	cout<<"printAfter="<<(printAfter?"true":"false")<<endl;
}
void delPerson(){
	
	cout<<db->getType(0)->getName()<<":";
	char buffer[MAX_INPUT_BUFFER];
	getStr(cin,buffer,MAX_LEN_VALUE);
	int index=db->findItem(0,buffer);
	if(index==-1){
		cout<<"No this person."<<endl;return ;
	}
	db->delRecord(index);
	cout<<"Delete person:"<<buffer<<" success!"<<endl;
	askIfSave();/**/
	return;
} 
void delType(){
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
	}/**/
}
void setPeron(){
	cout<<db->getType(0)->getName()<<":";
	char buffer[MAX_INPUT_BUFFER];
	getStr(cin,buffer,MAX_LEN_VALUE);
	int index=db->findItem(0,buffer);
	if(index==-1){
		cout<<"No this person."<<endl;return ;
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
}
void renameType(){
	//	cout<<"renameType"<<endl;
	cout<<"Name of type:";
	char buffer[MAX_INPUT_BUFFER];
	getStr(cin,buffer,MAX_LEN_VALUE);
	int index=db->findType(buffer);
	if(index==-1){
		cout<<"No this type."<<endl;
		return ;
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
				
}
void quit(){
	save();
	cout<<"exiting..."<<endl;
	isQuit=true;
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
void initDB(){//just add some type.
	db->reset();
	dataBase.addType("Name",10);dataBase.addType("QQ",10);dataBase.addType("Phone",18);dataBase.addType("Email",30);
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
			if(!dataBase.readFromFile(filePath)){
				cout<<"Can't open the file:\""<<filePath<<"\""<<endl;
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
