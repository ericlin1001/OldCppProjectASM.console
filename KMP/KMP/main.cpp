
#define Trace(m) //cout<<(#m)<<"="<<(m)<<endl;
#include<iomanip>
#include<iostream>
using namespace std;
#include<windows.h>
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 计算模式串每个前缀的边界 
int printInt(int *arr,int size){
	for(int i=0;i<size;i++){
		cout<<arr[i];
	}
	return 0;
}
void compute_next(char *pattern, int m, int *next){
    int i,j;
    next[0] = -2;
    next[1] = -1;
    for (i = 2; i < m; i++)
    {
        j = next[i-1] + 1;
        while ( (pattern[i-1] != pattern[j] || pattern[i] == pattern[j+1]) && j >= 0 )
        {
            j = next[j] + 1; 
        }
        next[i] = j;
    }
    return;
}




int kmp_string_match(char *text, int tLen, char *pattern, int pLen )
{
    int i = 0;
    int j = 0;
    int start = -1;

    //为next数组申请空间
    int *next = (int*)malloc(sizeof(int) * pLen);
    if (next == NULL)
    {
        return -2;
    }
    memset(next, 0, sizeof(int) * pLen);

    //计算模式串的边界
    compute_next(pattern, pLen, next);

    //匹配
    while (start == -1 && i < tLen)
    {
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j] + 1;

            if (j < 0)
            {
                j = 0;
                i++  ;
            }
        }
        if(j == pLen)
        {
            start = i - pLen;
        }
    }
Trace(printInt(next,pLen));
    free(next);

    return start;
}
//


int getRand(int min,int max){
	if(min>max)swap(min,max);
	return rand()%(max-min+1)+min;
}
char *gernStr(char *str,int size){
	for(int i=0;i<size;i++){
		char ch;
		switch(getRand(0,0)){
			case 0:
				ch=getRand('0','4');
				break;
			case 1:
				ch=getRand('A','Z');
				break;
			case 2:
				ch=getRand('a','z');
				break;		
		}
		str[i]=ch;
	}
		str[size]=0;
	return str;
}/*int i,j;
    next[0] = -2;
    next[1] = -1;
    for (i = 2; i < m; i++)
    {
        j = next[i-1] + 1;
        while ( (pattern[i-1] != pattern[j] || pattern[i] == pattern[j+1]) && j >= 0 )
        {
            j = next[j] + 1; 
        }
        next[i] = j;
    }*/
void mynext(char *pattern,int *next,int len){
#define until(exp) while(!(exp))
	//we must ensure next[k]=p k>p;
	next[0]=-1;
	next[1]=0;
	int mlen=0;
	for(int i=2;i<len;i++){
		mlen=next[i-1]+1;
		until(pattern[i-1]==pattern[mlen-1]&&pattern[i]!=pattern[mlen]||mlen<=0){
			mlen=next[mlen];
		}
		next[i]=mlen;
	}
}

int myKmp(char *text,int tlen,char *pattern,int plen){
	//plen>=2
	int * next=new int[plen];
	mynext(pattern,next,plen);
	int index=-1;
	int mlen=0;
	int ptext=0;
	while(ptext<tlen){
		if(text[ptext]==pattern[mlen]){
			mlen++;ptext++;
			if(mlen==plen){
				index=ptext-plen;break; 
			}
		}else{
			if(mlen==0)ptext++;
			else mlen=next[mlen];
		}
	}
	Trace(printInt(next,plen));
	delete []next;
	return index;
}
int main(){
	for(int i=0;i<10;i++){
		Trace(getRand(0,3));
		
	}
	for(int i=0;i<10;i++){
		Trace(getRand(3,0));
	}
	Trace(-3%5);
	Trace(-3%-5);
	Trace(3%-5);
	char stra[110];
	char strb[100];
	int co=0;
	while(co++<500){
	//cin>>stra>>strb;
	gernStr(stra,100);
	gernStr(strb,getRand(2,5));;
	//
	int index=kmp_string_match(stra,strlen(stra),strb,strlen(strb));
	int myindex=myKmp(stra,strlen(stra),strb,strlen(strb));
	if(index!=myindex){
		//
	Trace(index);
	cout<<"start"<<endl
		<<stra<<endl;
	if(index==-1)cout<<"no match"<<endl;
	else
		cout<<setw(index)<<" ";
		cout<<strb<<endl;
		cout<<"end\n"<<endl;
		//
		cout<<"Error!Error!Error!Error!Error!Error!Error!Error!Error!Error!Error!Error!Error!Error!Error!Error!Error!Error!Error!"<<endl;
	}else{
		cout<<"OK!"<<endl;
	}
	
	//cin.get();
	}
}