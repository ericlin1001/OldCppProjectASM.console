#include<cstring>
#include<iostream>
#include<stdlib.h>
using namespace std;
int main(){
/*
:itc
:cti
	*/
	char constr[100]="c4ca4238a0b923820dcc";
	char buffer[17]="0123456789abcdef";
	for(int r=0;r<15;r++){
		cout<<constr;
		for(int l=0;l<12;l++){
			cout<<buffer[rand()%16];
		}
		cout<<endl;
	}
	return 0;
}