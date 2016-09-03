#include<iostream.h>
#include"CEightQueen.h"
bool isAnswer(int *p){
	CEightQueen t;
	for(int i=0;i<8;i++){
		if(!t.setQueen(i,*p++)){
			return false;
		}
	}
	return true;	
}
void printInt(int *p,int size){
	while(size-->0) cout<<*p++<<",";
	cout<<endl;
}
void create(int *p,int num){
	static int MAX=8;
	static int count=0;
	if(num==MAX){
		//printInt(p,MAX);
		if(isAnswer(p)){
			printInt(p,MAX);
			count++;
		}
		return ;
	}
	for(int i=0;i<8;i++){
		*(p+num)=i;
		create(p,num+1);
	}
	if(num==0){
		cout<<"count="<<count<<endl;
	}
	return ;
}
void selectPos(CEightQueen t,int row,int num){
	static const int MAX=8;
	static int count=0;
	//
	if(num>=(MAX+1)){
		t.print();
		//cout<<"has "<<num<<" queen"<<endl;
		count++;
		return ;
	}
		for(int j=0;j<8;j++){
			//
			if(t.setQueen(row,j)){
				//setted
				selectPos(t,row+1,num+1);
			}
		}

	if(row==8){
		return ;
	}
//	cout<<"num="<<num<<endl;
	if(num==1){
		cout<<"count="<<count<<endl;
	}
	return ;
}
int main(){
	CEightQueen t;
//	t.setQueen(0,1);
//	t.print();
/*
	int a[8];
	int b[8]={1,0,2,2,3,1,0,5};
//	cout<<isAnswer(b)<<endl;
	create(a,0);*/
	selectPos(t,0,1);
	system("pause");
	return 0;
}