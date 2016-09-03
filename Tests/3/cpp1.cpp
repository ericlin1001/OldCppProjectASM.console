#include<iostream>
#include<stdarg.h>
//#include<string>
using namespace std;

class A
{
public:
	A()
	{
		n=new int;
		init();
	}
	void init()
	{
		throw 1.0f;
	}
private:
	int *n;
};
void g(int first,...)
{
	va_list paralist;
	int j;
	va_start(paralist,first);
	j=va_arg(paralist,int);
	va_end(paralist);
	printf("%d,%d",first,j);
	cout<<endl;
}

void f(...){
	
}
int main(){
	g(1,2,3);
/*	f(1,2);
	try{
		int a=2;
		throw a;
	}
	catch(double){
		cout<<"double error"<<endl;
	}
//	catch(int b){
//		cout<<"error:"<<b<<endl;
//	}
	catch(...){
		cout<<"catch default"<<endl;
	};
	cout<<"after throw"<<endl;
	//
	try{
		A aaa;
	}
	catch(double){
		cout<<"double "<<endl;
	}
	catch(int ){
	}
	catch (float tt){
		cout<<"float "<<tt<<endl;
	}
	exit(1);
//	terminate();
//	abort();*/
	return 0;
}