#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;
#define MAXLEN 1000
void arraySplit(int *a,char *b)
{
	if(*a==-1){
		*b='\0';
		return ;
	}
	char buffer[10];
	while(*(a+1)!=-1){
		itoa(*a,buffer,10);
		strcat(b,buffer);
		strcat(b,",");
		a++;
	}
	itoa(*a,buffer,10);
	strcat(b,buffer);
	strcat(b,"\0");
}
char *getAnswer(int n,int m,int d){
	char *answerStr=new char [MAXLEN*2];
	int answer[MAXLEN];//-1 means end.
	for(int i=0;i<10;i++){
		answer[i]=i+1;
	}
	answer[i]=-1;
	arraySplit(answer,answerStr);
	return answerStr;
}
#define MAXOFLINES 1000
int main()
{
	char buffer[10];
	char *answer[MAXOFLINES];
	int n,m,d;
	int i=0;
	do{
	cin>>buffer;
	n=atoi(buffer);
	cin>>buffer;
	m=atoi(buffer);
	cin>>buffer;
	d=atoi(buffer);
	answer[i++]=getAnswer(n,m,d);
	}while(!(n==0 && m==0 && d==0));
	int j=0;
	for(j=0;j<i;j++){
		cout<<answer[j]<<endl;
		delete answer[j];
	}/**/
	return 0;
}