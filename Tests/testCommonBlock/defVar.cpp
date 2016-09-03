#include<iostream>
using namespace std;
#define Trace(m) cout<<#m<<"="<<(m)<<endl;
double uinit_global_var;
void tt(){
	//uinit_global_var=5;
	Trace(uinit_global_var);
	uinit_global_var/=2;
	Trace(uinit_global_var);

	cout<<"tt()"<<endl;
}