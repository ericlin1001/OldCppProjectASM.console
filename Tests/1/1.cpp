#include<iostream.h>
#include<time.h>
#include<stdlib.h>
int RandInt(int min,int max){
	return rand()%(max-min+1)+min;
}
int main(){
	srand((unsigned int)time(NULL));
	int n;
	int i=20;
	while(i-->0){
	n=RandInt(5,10);
	cout<<n<<endl;
	}
	cin>>n;
	return 0;
}