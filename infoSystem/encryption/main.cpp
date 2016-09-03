
#include<iostream>
#include<fstream>
#include "EncryptFun.h"
using namespace std;
#define MING_FILE_NAME "ming.txt"
#define MI_FILE_NAME "mi.txt"
#define DECODE_MI_FILE_NAME "mi.txt-decode.txt"
int pi=0;

#define TraceVar(var) cout<<#var<<"="<<var<<endl;
int main(){
	//MING_FILE_NAME
	//MI_FILE_NAME
	/*ifstream infile;
	infile.open("test.txt");
	TraceVar(infile.fail());
	int i=0;
	while(1){
		char ch=infile.get();
		cout<<++i<<":";
		TraceVar(ch);
		if(infile.eof())break;
	}
	cout<<"ok"<<endl;*/
	//TraceVar(setNoChangeTag("cc.txt","MyTag",5));
	
	//TraceVar(testTag("cc.txt","MyTag",5));
	//TraceVar(removeNoChangeTag("cc.txt","MyTag",5));
	//TraceVar(encryptFile("test.txt","ctest.txt","my",2));
	//TraceVar(decryptFile("ctest.txt","dtest.txt","my",2));
	/*if(filecmp(MING_FILE_NAME,DECODE_MI_FILE_NAME)){
		cout<<"decode success!"<<endl;
	}else{
		cout<<"Error:decode failed!"<<endl;
	}*/
	return 0;
}
