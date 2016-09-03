#include<cstring>
#include<iostream>
using namespace std;
int main(){
/*
:itc
:cti
	*/
	bool itc=false;
	bool cti=true;
	char ch;
	//
	char buffer[100];
	cout<<"order :itc :cti"<<endl
		<<"set :cti=true"<<endl;
	while(1){
		cin>>buffer;
		ch=buffer[0];
		if(ch==':'){
			if(strcmp(buffer,":itc")==0){
				itc=true;cti=false;cout<<"set :itc=true"<<endl;continue;
			}else if(strcmp(buffer,":cti")==0){
				itc=false;cti=true;cout<<"set :cti=true"<<endl;continue;
			}else{
				cout<<":order no this order!"<<endl;
			}
		}
		if(itc){
			for(int i=0;i<strlen(buffer);i+=2){
				char dig[5];dig[0]=buffer[i];
				dig[1]=buffer[i+1];dig[2]=0;
				cout<<(char)(atoi(dig));
			}
		}
		if(cti){
			for(int j=0;j<strlen(buffer);j++){
				cout<<(int)buffer[j];
			}
		}
	}
	return 0;
}