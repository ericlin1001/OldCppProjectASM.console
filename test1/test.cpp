#include<iostream>
using namespace std;

#include"StrFunc.h"
int main(){
	string str;
	getLine(cin,str,'a');
	cout<<"str="<<str<<endl;
	//
	string str2;
	getline(cin,str2,'a');
	cout<<"str2="<<str2<<endl;
	//

	system("pause");
	return 0;
}