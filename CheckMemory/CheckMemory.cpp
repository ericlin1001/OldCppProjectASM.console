#include<iostream>
#include<cstring>
#include<iomanip>
using namespace std;
typedef unsigned char *pMem;
pMem hexTopMem(char *str){
	int answer=0;
	char ch;
	while((ch=*str++)!=0){
		if(ch<='9'){//is number
			ch-=0x30;
		}else{//is word
			if(ch>='a'){
				ch-=0x20;
			}
			ch-=0x40;
			ch+=9;
		}
		answer*=16;
		answer+=ch;
	}
	return (pMem)answer;
}
void printchar(char *p,int size){
	for(int i=0;i<size;i++){
		cout<<(int)p[i]<<":"<<setw(1)<<p[i]<<' ';
		if(i==7) cout<<"|";
	}
}
int main(int argc,char *argv[]){
	pMem p=(pMem)0;
	int num=16;
	if(argc==1){
		cout<<"Usage:GetMemory address [num(16)]"<<endl;
		cout<<hex<<(int)&p<<endl;
		return 0;
	}else if(argc==2){
		p=hexTopMem(argv[1]);
	}else if(argc==3){
		p=hexTopMem(argv[1]);
		num=atoi(argv[2]);
	}else{
		cout<<"too much args."<<endl;
		cout<<"Usage:GetMemory address [num(16)]"<<endl;
		return 0;
	}
	cout<<"Memory:";
	cout<<(int)p<<endl;
	char buffer[16];
	for(int i =0;i<num;i++){
		if(i%16==0){
			cout<<"   ";
			printchar(buffer,16);
			memset(buffer,0,16);
			cout<<endl;
			cout<<setw(8)<<hex<<(int)p<<"   ";
		}
		if(i%8==0 && i%16!=0) cout<<"|";
		cout<<setw(2)<<hex<<(int)*p<<" ";
		buffer[i%16]=(unsigned char)*p;
		p++;
		
	}
	cout<<endl;/**/
	return 0;
}