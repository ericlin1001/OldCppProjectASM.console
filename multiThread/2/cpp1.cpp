#include<iostream.h>
#include<windows.h>
int sum=0;
void A(LPVOID pParam){
	for(int i=1;i<100;i++){
		sum+=i;
	}
}
void B(LPVOID pParma){
	TRACE("sum=%d",sum);
}
int main(){
	AfxBeginThread(A,LPVOID(0));
	AfxBeginThread(B,LPVOID(0));
	return 0;
}