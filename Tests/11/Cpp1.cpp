#include<iostream>
using namespace std;
bool isPrime(int a){
	if(a==2) return true;
	for(int i=2;i*i<=a;i++){
		if(a%i==0) return false;

	}
	return true;
}
int main(){
	int n;
	cin>>n;
	int numP=0;
	int i=2;
	while(1){
		if(isPrime(i)){
			cout<<i;numP++;
			if(numP<n)cout<<" ";
			if(numP==n)break;
			if(numP%10==0)cout<<endl;
		}
		i++;
	}
//	system("dir");
	return 0;
}