#include<iostream>
using namespace std;
#define MAXOFCASES 500
#define MAXOFINSTANCES 100000
//
//question structure:
typedef int QuestionType;

//
//answer structure:
typedef int  AnswerType;

//
//the main function:
AnswerType getAnswer(QuestionType  n){
	AnswerType answer=0;
	int primes[MAXOFINSTANCES/2];//not conisder 2
	int numPrimes=0;
	primes[numPrimes++]=3;
	int i,j;
	for( i=3;i<n;i+=2){
		bool isPrime=true;
		for( j=0;j<numPrimes  ;j++){
			if(i%primes[j]==0){
				isPrime=false;
				break;
			}
		}
		if(isPrime){
			primes[numPrimes++]=i;
		}
	}
	for( j=0;j<numPrimes-1;j++){
		if(primes[j+1]-primes[j]==2){
			answer++;
		//	j++;
		}
	}
	return answer;
}
//
//
int main()
{
	int n,answer;//5<=n<100000
	cin>>n;
	answer=getAnswer(n);
	cout<<answer<<endl;
	return 0;
}