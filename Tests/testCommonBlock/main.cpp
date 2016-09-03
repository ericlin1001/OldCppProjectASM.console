#include<iostream>
#include<windows.h>
#include<WinNt.h>
using namespace std;
int init_global_var=5;
 short uinit_global_var;
#define Trace(m) cout<<#m<<"="<<(m)<<endl;
void tt();
int main(){
	int *p=0;
	cout<<"the bit of the cpu is :"<<sizeof(p)*8<<endl;
	unsigned long len=3;
	char buffer[100]="abasdfadsf";
	WriteConsole(NULL,buffer,3,&len,0);
	/*tt();//0
	uinit_global_var=5;
	Trace(uinit_global_var);//5
	tt();//0 0
	//
	uinit_global_var=8;
	Trace(uinit_global_var);//8
	tt();//0 0
	//
	Trace(init_global_var);
	Trace(uinit_global_var);
	tt();*/
	return 0;
}