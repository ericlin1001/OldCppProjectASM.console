#include<iostream>
using namespace std;
void printInt(int i){
	if(i<1000)cout<<" ";
	if(i<100 )cout<<" ";
	if(i<10  )cout<<" ";
	cout<<i;	
}
void printBlanK(int n){
	for(int i=0;i<n;i++)cout<<" ";
}
int main(){
	int n;
	cin>>n;
	if(n==1){ cout<<1;return 0;}
	while(n!=1){
		for(int i=2;i<=n;i++){
			if(n%i==0) {cout<<i;n/=i;break;}
		}
		cout<<' ';
	}
/*	int i,j;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			if(j<=i)cout<<j;
			else cout<<" ";
			cout<<" ";
		}
		for(j=1;j<=n;j++){
			if(j<=n+1-i)cout<<j;
			else cout<<" ";
			cout<<" ";
		}
		for(j=1;j<=n;j++){
			if(j>=n+1-i)cout<<i+j-n;
			else cout<<" ";
			cout<<" ";
		}
		for(j=1;j<=n;j++){
			if(j>=i)cout<<j-i+1;
			else cout<<" ";
			cout<<" ";
		}
		cout<<endl;
	}*/
	return 0;
}