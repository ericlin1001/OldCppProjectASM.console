#include<iostream.h>
#include<winsock2.h>
#include<stdlib.h>
int main(){
	char buffer[100];
	servent *ps;
	while(1){
	cin>>buffer;
	 ps=getservbyname("W32Time","tcp");
	if(ps==NULL){
		cout<<"no found!"<<endl;
		continue;
	}
	cout<<ntohs(ps->s_port)<<"  "<<ps->s_name<<endl;
	cout<<"\""<<buffer<<"\"="<<atoi(buffer)<<endl;
	}
	return 0;
}