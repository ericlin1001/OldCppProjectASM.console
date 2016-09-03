#include "Interpreter.h"
#include<string.h>
#include<iostream.h>
 Memory g_memory;
 int g_pMemory=0;
int fetch(char *name){
	int i=0;
	while(strcmp(g_memory[i].name,name)&& i<=g_pMemory)i++;
	if(i>g_pMemory) error("fetch");
	else return g_memory[i].value;
	return 0;
}
void store(char *name,int value){
	int i=0;
	while(strcmp(g_memory[i].name,name)&& i<=g_pMemory)i++;
	if(i<=g_pMemory){ error("fetch");
	}else{
		g_pMemory++;
		if(g_pMemory>=MAX_SIZEOF_MEMORY){
			error("in store .Memory overflow.");
		}else{
		strcpy(g_memory[g_pMemory].name,name);
		g_memory[g_pMemory].value=value;
		}
	}
}
//
/*
#include "Parser.h"
#define MAX_SIZEOF_MEMORY 20
#define MAX_SIZEOF_INPUT 50
#define MAX_SIZEOF_OUTPUT 50*/
int Input[MAX_SIZEOF_INPUT];
int Output[MAX_SIZEOF_OUTPUT];
int rp=0;
int op=0;
int readNum(){
	cin>>Input[rp];
	return Input[rp++];
}
void writeNum(int n){
	Output[op++]=n;
}
void wirteFlush(){
	cout<<Output[op]<<endl;
}

//
void Interpreter()
{

}