#include<iostream>
#include<cstring>
using namespace std;
int findIndex(char *str,char *findStr){
	int lstr=strlen(str);
	int lfindStr=strlen(findStr);
	int i,j;
	for(i=0;i<lstr-lfindStr+1;i++){
		j=0;
		while(*(str+i+j)==*(findStr+j))j++;
		if(j>=lfindStr)return i;
	}
	return -1;
}
void blank(int n){while(n-->0)cout<<' ';
}
int main(){
	char buffer[100];
	char *p1,*p2;
	p1=p2=buffer;
	p2+=50;
	while(1){
		cout<<"please input two string."<<endl
			<<"first one:";
		cin>>p1;
		cout<<"second one:";
		cin>>p2;
		cout<<"result:"<<endl;
		if(strlen(p1)<strlen(p2)){
			char *temp=p2;
			p2=p1;
			p1=temp;
		}
		int index=findIndex(p1,p2);
		if(index>=0){
			cout<<p2<<" is the subString of "<<p1<<','<<endl;
			cout<<"match like that:"<<endl;
			cout<<p1<<endl;
				blank(index);
				cout<<p2<<endl;
		}else{
			cout<<p2<<" isn't the subString of "<<p1<<','<<endl;
		}
		cout<<endl;

	}

	return 0;
}