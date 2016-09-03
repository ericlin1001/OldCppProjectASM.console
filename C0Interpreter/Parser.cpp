#include "Parser.h"
#include<string.h>
#include<iostream.h>
#include<stdlib.h>
//
char g_ch;
//char *g_progFile;
int g_fp=-1;
Token g_token;
//
void back(){
	g_ch=g_progFile[--g_fp];
}
void nextChar(){
	g_ch=g_progFile[++g_fp];
}
void nextAvailChar(){
	nextChar();
	while(is_layout(g_ch)){ nextAvailChar();}
}
//
void recognizeNumber(){
	char digits[MAX_SIZEOF_DIGIT];
	int dsp=0;
	digits[dsp++]=g_ch;
	nextChar();
	while(is_digit(g_ch)){digits[dsp++]=g_ch;nextChar();}
	digits[dsp]='\0';
	g_token.type=NUM;
	strcpy(g_token.seman,digits);
	back();
}
void recognizeName(){
	char name[MAX_SIZEOF_SEMAN];
	int np=0;
	name[np++]=g_ch;
	nextChar();
	while(is_letter_or_digit(g_ch)){	name[np++]=g_ch;nextChar();}
	name[np++]='\0';
	//selection:
	if(!strcmp(name,"{")){g_token.type=BEGIN;
	}else if(!strcmp(name,"}")){g_token.type=END;
	}else if(!strcmp(name,"read")){g_token.type=READ;strcpy(g_token.seman,"read");
	}else if(!strcmp(name,"write")){g_token.type=WRITE;strcpy(g_token.seman,"write");
	}else{g_token.type=IDEN;strcpy(g_token.seman,name);
	}	/**/
	back();
}
void error(char *mess){
	cout<<"error!!!"<<mess<<endl;
	exit(1);
}
void print(Token token){
	cout<<"token.type = "<<token.type<<"  seman="<<token.seman<<endl;
}
void nextToken()
{
	nextAvailChar();
	//for test
	if(is_digit(g_ch)){
		recognizeNumber();
	}else if(is_letter(g_ch)){
		recognizeName();
	}else{
		switch(g_ch){
		case '+':	g_token.type=PLUS;strcpy(g_token.seman,"+");	break;
		case '-':	g_token.type=SUB;strcpy(g_token.seman,"-");	break;
		case '*':	g_token.type=MULT;strcpy(g_token.seman,"*");	break;
		case '=':	g_token.type=ASSI;strcpy(g_token.seman,"=");	break;
		case ';':	g_token.type=SEMI;strcpy(g_token.seman,";");	break;
		case '(':	g_token.type=OPEN;strcpy(g_token.seman,"(");	break;
		case ')':	g_token.type=CLOSE;strcpy(g_token.seman,")");	break;
		case '{':	g_token.type=BEGIN;strcpy(g_token.seman,"{");	break;
		case '}':	g_token.type=END;strcpy(g_token.seman,"}");	break;
		case '\0':	g_token.type=EOF;strcpy(g_token.seman,"\0");	break;
		default:
			error("nextToken");
			break;
		}
	}/**/
	//for test:
	print(g_token);
}
//************analysis*************
void checkToken(int type){
	if(g_token.type==type){
		nextToken();
	}else{
		error("checkToken");
	}
}
void prog(){
	nextToken();
	checkToken(BEGIN);
	int testi=0;
	while(g_token.type!=END){
		testi++;
	//	cout<<"sentence "<<testi<<":"<<endl;
		switch(g_token.type){
		case READ:nextToken();checkToken(OPEN);checkToken(IDEN);checkToken(CLOSE);checkToken(SEMI);break;
		case WRITE:nextToken();checkToken(OPEN);expr();checkToken(CLOSE);checkToken(SEMI);break;
		case IDEN:nextToken();checkToken(ASSI);expr();checkToken(SEMI);break;
			//blank sentence.
		case SEMI:cout<<"blank sentence."<<endl;nextToken();break;
		default:cout<<testi<<endl;error("prog");
		}
	}/**/
}

void expr(){
	//cout<<"g_token.type="<<g_token.type<<endl;
	if(g_token.type!=NUM && g_token.type!=IDEN){error("expr");}
	nextToken();
	while(g_token.type==PLUS||g_token.type==MULT||g_token.type==SUB){
		nextToken();
		if(g_token.type!=NUM && g_token.type!=IDEN){error("expr2");}
		nextToken();
	}
}
void reset()
{
g_ch='\0';
g_fp=-1;
}
