#include<iostream.h>
#include"complex.h"
int main(){
	Complex a(1,2),b(1,1),c(-2,1);
	cout<<"before..."<<endl;
	cout<<"a="<<a<<endl;
	cout<<"b="<<b<<endl;
	cout<<"c="<<c<<endl;
	//
	cout<<"after c=a+b;"<<endl;
	c=a+b;
	cout<<"c="<<c<<endl; 
	//
	cout<<"after c=a-b;"<<endl;
	c=a-b;
	cout<<"c="<<c<<endl;
	//
	cout<<"after c=a*b;"<<endl;
	c=a*b;
	cout<<"c="<<c<<endl; 
	//
	cout<<"after c=a/b;"<<endl;
	c=a/b;
	cout<<"c="<<c<<endl;
	return 0;
}