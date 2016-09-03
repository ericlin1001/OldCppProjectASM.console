#include<iostream>
using namespace std;
#define MAX_NUM 100
int primes[MAX_NUM];

int main(){
	primes[0]=2;
	int count=1;
	int m;
	int n=3;
	cin>>m;
	if(m==0)return 0;
	else cout<<"2 ";
	while(1){
		bool isPrime=true;
		for(int i=0;i<count&&primes[i]*primes[i]<=n;i++){
			if(n%primes[i]==0){
				isPrime=false;break;
			}
		}
		if(isPrime){
			primes[count++]=n;
			cout<<n<<" ";
		}
		if(count>=m)break;
		n++;
	}
	return 0;
}