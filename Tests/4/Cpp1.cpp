//1002 problem.
#include<iostream>
#include<cstring>
using namespace std;
#define MAX 10000
int fibona[MAX];
int fibo(int n)
{
	int i=1,j;
	if(fibona[n]==0){
		while(fibona[++i]!=0);
		for(j=i;j<=n;j++) fibona[j]=fibona[j-1]+fibona[j-2];
	}
	return fibona[n];
}
int getAnswer(char *str)
{
	int count=1;
	int templen=0;
	while(*str!=0){
		bool b=false;
		templen=0;
		while(*str!=0 && (*str=='1' || *str=='2')){
			str++;templen++;
			b=true;
		}
		if(*str!=0 && b && (*(str-1)=='1' || *str<=6+0x30)){
			templen++;str++;
		}
		count*=fibo(templen);
		if(*str==0) break;
		if(!b) str++;
	}
	return count;
}
int main()
{
fibona[0]=1;
fibona[1]=1;
char buffer[MAX];
int answer[MAX];
answer[0]=0;
cin>>buffer;
int i=0;
while(strcmp(buffer,"0")!=0){
answer[i++]=getAnswer(buffer);
cin>>buffer;
}
answer[i]=0;
i=0;
while(answer[i]!=0){
cout<<answer[i++]<<endl;
}
return 0;
}
//1002 problem.