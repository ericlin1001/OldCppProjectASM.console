#include<iostream.h>
//#include<cmath>
#include<math.h>
//using namespace std;
void f(int n){
	int *an=new int[n+1];
	int i=0;
	for(i=2;i<=n;i++){
		an[i]=i;
	}
	int *primes=new int[abs(n/2)];
	int	*p=primes;
	cout<<"primes < "<<n<<" is:\n";
	for(i=2;i<=n;i++){
		if(an[i]!=0){
			cout<<i<<",";
			*p++=i;
			for(int j=2;j<=n/i;j++){
				an[i*j]=0;
			}
		}
	}
	cout<<endl;
}
int main(){
	int n;
	while(1){
		cin>>n;
		if(n==0)break;
		f(n);
	}
	return 0;
}
