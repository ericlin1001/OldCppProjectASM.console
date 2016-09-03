//#define __test__
#include "CDataBaseView.h"
#include "share.h"
#define RIGHT_ARROW (char)26
#define MAX_INPUT_BUFFER 100
void CDataBaseView::addType(char *typeName,int valueLen){
	if(db->insertType(db->getNumTypes())){
		db->setType(db->getNumTypes()-1,typeName,valueLen);
	}
}
void CDataBaseView::inputData(){
	int i;
	char buffer[MAX_INPUT_BUFFER];
	if(db->insertRecord(db->getNumRecords())){
		cout<<"Input the data:"<<endl;
		for(i=0;i<db->getNumTypes();i++){
			cout<<db->getType(i)->getName()<<"("<<db->getType(i)->getMaxLen()<<"):";
			getStr(cin,buffer,sizeof(buffer));
			db->setItem(db->getNumRecords()-1,i,buffer);
		}
	}
}
void CDataBaseView::print(bool *printRows,bool *printCols){
	int i=0;
	int lenOfCols=1;
	int numTypes=db->getNumTypes();int numRecords=db->getNumRecords();
	for(i=0;i<numTypes;i++){
		if(printCols[i]){
			lenOfCols+=db->getType(i)->getShowLen()+1;
		}
	}
	//start print;
	printTimes('-',lenOfCols);cout<<endl;//print --------
	//print typename
	cout<<'|';
	for(i=0;i<numTypes;i++){
		if(printCols[i]){
			char *name=db->getType(i)->getName();
			int showlen=db->getType(i)->getShowLen();
			if(strlen(name)<=showlen){
				cout<<setw(showlen)<<name<<'|';
			}else{//too long
				printStr(name,showlen-1);cout<<RIGHT_ARROW<<'|';
			}
		}
	}
	cout<<endl;
	printTimes('-',lenOfCols);cout<<endl;//print --------
	//print the records.
	int j=0;
	
	for(j=0;j<numRecords;j++){
		if(printRows[j]){
			cout<<'|';
			for(i=0;i<numTypes;i++){
				if(printCols[i]){
					char *name=db->getItem(j,i);
					int showlen=db->getType(i)->getShowLen();
					if(strlen(name)<=showlen){
						cout<<setw(showlen)<<name<<'|';
					}else{//too long
						printStr(name,showlen-1);cout<<RIGHT_ARROW<<'|';
					}
				}
			}
			cout<<endl;
			printTimes('-',lenOfCols);cout<<endl;//print --------
		}
	}
	cout.flush();
	//cout<<RIGHT_ARROW<<":means not end."<<endl;
}
