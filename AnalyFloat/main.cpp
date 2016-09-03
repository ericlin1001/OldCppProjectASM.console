//set which one to complie.
//#define case1
#define tempCase
//
#include "testCases.txt"
#ifdef tempCase
//begin:
#include<iostream>
using namespace std;
#define __test__
#ifdef __test__
#define Trace(m,sep) cout<<#m<<sep<<(m)<<endl;
#else 
#define Trace(m,sep) 
#endif
//
typedef char Byte;
typedef Byte * Pointer;
typedef bool Bit;
//
Bit getBit(Pointer p,int index){//bit is unit of size
	return (*(p+index/8) & (1<<(index%8)))!=0;
}
char *getSeqBin(Pointer p,int size,char *str){//bit is unit of size
//get the bit:address low to high
	for(int i=0;i<size;i++){
		str[i]=getBit(p,i)?'1':'0';
	}
	str[size]=0;
	return str;
}
char *revStr(char * const str,int beg,int end){
	char *p1=str+beg;
	char *p2=str+end;
	while(p1<p2){
		*p1^=*p2^=*p1^=*p2;
		p1++;p2--;
	}
	return str;
}
char *strInsert(char *str,int begIndex,char ch){
	int len=strlen(str);
	for(int i=len+1;i>=begIndex+1;i--){
		str[i]=str[i-1];
	}
	str[begIndex]=ch;
	return str;
}
char *formatStr(char *str,char sep=' ',int stepSep=8){
	int charcount=0;
	int strlen=0;
	while(str[strlen]){

		strlen++;//count one bit.
		charcount++;//the count add 1
		if(charcount%stepSep==0){
			strInsert(str,strlen++,sep);
		}
	}
	return str;
}
char *getBin(Pointer p,int size,char *const str,char sep=' ',int stepSep=8){//bit is unit of size
	getSeqBin(p,size,str);
	formatStr(str,sep,stepSep);
	return str;
}
int binToInt(const char *str,const int size,const int beg=0){
	int s=0;
	for(int i=beg;i<size+beg;i++){
		s*=2;
		s+=(str[i]!=0);
	}
	return s;
}
int binFract(const char *str,const int size,const int beg=0){
	int s=0;
	for(int i=beg;i<size+beg;i++){
		s*=2;
		s+=(str[i]!=0);
	}
	return s;
}
#define ShowBin(m) Trace(getBin((Pointer)&(m),sizeof((m))*8,buffer,' '),'\n');
int main(){
	char buffer[100];
	//
/*	int a=0x4080;
	ShowBin(a);
	//
	float f=15.25f;
	getSeqBin((Pointer)&f,sizeof(f)*8,buffer);
	revStr(buffer,0,strlen(buffer)-1);
	//formatStr(buffer,'\n');
	Trace(buffer,"=\n");
	//ShowBin(f);
	Trace(f,'=');
	//
	*/
	float f=15.25f;
	for(int i=32-1;i>=0;i--){
		cout<<(getBit((Pointer)&f,i)?'1':'0');
	}
	return 0;
}
//end
#endif
