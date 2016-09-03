// C0Interpreter.cpp : Defines the entry point for the console application.
//
#include "Interpreter.h"
#include "Parser.h"
#include <fstream.h>
#include<string.h>
//
char *g_progFile;
#define DEFAULTFILE "temp.txt"
int main(int argc, char* argv[])
{
	if(argc==1){
		fstream pfile;
		pfile.open(DEFAULTFILE,ios::nocreate|ios::in|ios::out,0);
		char ch;
		int len=pfile.tellg();
		pfile.seekg(0,ios::end);
		len=pfile.tellg()-len;
		cout<<"the len is:"<<len<<endl;
		//
		g_progFile=new char[len];
		//
		pfile.seekg(0,ios::beg);
		int i=0;
		cout<<"the program:"<<endl;
		while(!pfile.eof()){
			pfile.get(ch);
			cout<<ch;
			*(g_progFile+i++)=ch;
		}
		cout<<endl<<"end"<<endl;
	}else{
	} 
//	g_progFile
	//for test:
/*	delete g_progFile;
	g_progFile=new char [50];
	strcpy(g_progFile,"{x = 10;read(y);x=x+y;write(x * y);}");
	cout<<"the program:"<<g_progFile<<endl;*/
	prog();
	return 0;
}

/*C0³ÌÐòÀý×Ó:
{
 x = 10;
 read(y);
 x=x+y;
 write(x * y);
 }
 */