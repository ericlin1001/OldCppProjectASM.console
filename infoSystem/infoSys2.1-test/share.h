#ifndef SHARE_H
#define SHARE_H

#include<stdlib.h>
#include<iostream>
#include<fstream>
using namespace std;

#ifdef __test__
#define Test(mess)  cout<<mess<<endl;
#define TraceVar(var) cout<<#var<<"="<<var<<endl;
#else
#define Test(mess) 
#define TraceVar(var)  
#endif 
//new added

//end new added
#define DEFAULT_MAX_VALUE_LEN 15
#define MAX_LEN_VALUE 30
//
//
void error(char *mess,int type=0);
void warn(char *mess,int type=0);

void error(char *mess,char *mess2,int type=0);
void warn(char *mess,char *mess2,int type=0);

void error(char *mess,int type);
void warn(char *mess,int type);

bool isExistFile(char *fileName);
void intToStr(int n,char *buffer);
int getStr(istream & in,char *str,int len,char delims='\n',char emit=' ');
char *delBlank(char *str);
char* lowerCase(char *src);
#endif