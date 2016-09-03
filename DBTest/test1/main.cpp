#include<fstream>
#include<iostream>
#include "share.h"
using namespace std;
#define FILE "save.txt"
#define T(m) //cout<<#m<<endl;
void help(){
	cout<<"order:read,clear,help,exit"<<endl;
}
void initFile(ofstream &file){
	system("@echo.>>"FILE);
	system("@echo %date% %time% >>"FILE);
	system("@echo ---------------------------------------->>"FILE);
	file.open(FILE,ios::app);
}
int contain(const char *str1,const char *str2){
	for(int i=0;i<strlen(str2);i++){
		if(str1[i]!=str2[i])return -1;
	}
	return 0;
}
#define DEFAULT_LEN_BUFFER 500
int main(){
	help();
	char buffer[DEFAULT_LEN_BUFFER];
	ofstream file;
	initFile(file);
	while(1){
		cout<<"SQL>";getStr(cin,buffer,DEFAULT_LEN_BUFFER,';');cin.get();

		if(contain(buffer,"read")==0||contain(buffer,"r")==0){
			T(1);
			ifstream t;t.open(FILE);
			if(t.fail())cout<<"open "FILE" fail!"<<endl;
			T(2)
			while(1){char temp;temp=t.get();if(t.eof())break;cout<<temp;}
			T(3)
			t.close();
		}else if(contain(buffer,"exit")==0){
			exit(0);
		}else  if(contain(buffer,"help")==0||contain(buffer,"h")==0){
			help();
		}else if(contain(buffer,"clear")==0){
			file.close();
			remove(FILE);
			initFile(file);
		}else {
			file<<buffer<<endl;
		}
	}
	file.close();
	return 0;
}