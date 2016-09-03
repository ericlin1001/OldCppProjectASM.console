#include<iostream.h>
#include "calExp.h"
int main(int argc,char **argv)
{
	/*for(int i=0;i<argc;i++){
		cout<<i<<":";
		cout<<*(argv+i)<<endl;
	}*/
	if(argc==2){
		cout<<mainCal(*(argv+1))<<endl;
	}else{
		cout<<"argument error!"<<endl;
		cout<<"Usage:"<<endl;
		cout<<"calExp \"expression\""<<endl;
		cout<<"for example:"<<endl;
		cout<<"calExp 2+(3+8*7)*2^2*3+5"<<endl;
		cout<<endl;
	}
	/*char buffer[100]="1+5*(5+8*9-9)*7-9";
	char *p=buffer;
	cout<<mainCal("1+5*(5+8*9-9)*7-9")<<endl;
	*/
	return 0;
}
