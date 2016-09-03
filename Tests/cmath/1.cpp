#include<iostream>
#include<cstring>
//#include<cmath>
using namespace std;
int di;
#define MAX_BUFFER 500
int powBuffer[MAX_BUFFER];
int pow(int a,int b){
	if(b>MAX_BUFFER) return a*pow(a,b-1);
	if(powBuffer[b]==0){
		powBuffer[b]=a*pow(a,b-1);
	}
	return powBuffer[b];
}
int getAnswer(int n){
	if(n==0) return 0;
	if(n==1) return 1;
	int line=1;
	int nowNum=1;
	while(1){
		if(nowNum>=n){
			break;
		}
		line++;
		nowNum*=2;
		nowNum+=1;
	}
	//cout<<"each line:"<<line-1<<" ";
	return pow(di,line-1)+getAnswer(n-(nowNum-1)/2-1);
}
int main(){
	int b;
	while(1){
		cin>>di>>b;
		memset(powBuffer,0,MAX_BUFFER);
		cout<<getAnswer(b)<<endl;
	}
	return 0;
}