#ifndef SHARE_H
#define SHARE_H

#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<stdio.h>
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


bool isExistFile(char *fileName);
void intToStr(int n,char *buffer);
int getStr(istream & in,char *str,int len,char delims='\n',char emit=' ');
char *delBlank(char *str);
char* lowerCase(char *src);
bool isBlank(char *str);
bool openFile(ofstream &outfile,char *file);
#endif