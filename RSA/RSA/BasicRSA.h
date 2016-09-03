#ifndef	__BASICRSA_H__
#define __BASICRSA_H__
#include<time.h>
template<class T>
class RSA{
private:
	typedef T LargeNumber;
	LargeNumber e,n,p,q,d;
	const LargeNumber expMod(const LargeNumber& base,const LargeNumber& expo,const LargeNumber& m){
	if(m==0){cout<<"expMod Error!"<<endl;return 0;}
	LargeNumber x=1;
	LargeNumber power=base%m;
	LargeNumber exp=expo;
	while(exp!=0){
		if(exp%2==1)x=(x*power)%m;
		exp/=2;
		power=(power*power)%m;
	}
	return x;
}
	bool isMillerTest(const LargeNumber& num,const LargeNumber& b){
	//true means probaly a prime
	//false mean sure to be composite!
	//ensure 1<b<num!
	LargeNumber s=0,t=num-1;
	while(t%2==0){s++;t/=2;}
	LargeNumber x=expMod(b,t,num);
	if(x==1||x==num-1){
		return true;//pass,unknown,probably a prime
	}
	for(LargeNumber j=1;j<=s-1;j++){
		x*=x;
		x%=num;
		if(x==num-1)return true;//pass,unknown,probably a prime}
	}
	return false;//not pass,not a prime!
}
	bool isComposite(const LargeNumber& num){
	//according to the Miller's test
	if(num<=1)return true;
	if(num==2)return false;
	const int numTestCase=30;
	for(int i=0;i<numTestCase;i++){
		LargeNumber b=range(2,num-1);
		if(!isMillerTest(num,b)){return true;}
	}
	return false;
}
	LargeNumber getInverseMod(LargeNumber a,LargeNumber b){
	//ensuer gcd(a,b)==1
	//find y such that a*y==1 (mod b); 
	LargeNumber originB=b;
	LargeNumber q1=1,q2=0,q3;
	LargeNumber r;
	if(gcd(a,b)!=1){cout<<"getInverseMod Error"<<endl;return 1;}
	while(1){
		r=a%b;
		q3=q1-(a/b)*q2;
		if(r==1)break;
		a=b;b=r;
		q1=q2;q2=q3;
	}
	//
	while(q3<0)q3+=originB;
	return q3;
}
	LargeNumber gcd(LargeNumber a,LargeNumber b){
	LargeNumber r;
	if(b==0){cout<<"gcd Error"<<endl;return a;}
	do{
		r=a%b;
		a=b;
		b=r;
	}while(r!=0);
	return a;
}
	LargeNumber range(const LargeNumber& min,const LargeNumber& max){
		LargeNumber temp=(max-min+1);
		LargeNumber r=1;
		while(r<temp){
			r*=rand();
		}
	return r%temp+min;
}
	
public:
	RSA(){srand((unsigned int)time(NULL));}
	bool setEncyptParam(const LargeNumber& privateKey,const LargeNumber& min,const LargeNumber& max){//create n
	d=2*privateKey+1;
	LargeNumber retryTimes=(max-min);
	while((retryTimes--)>0){
		p=range(min,max);
		if(gcd(d,p-1)==1 && !isComposite(p))break;
	}
	if(retryTimes==0)return false;
	
	retryTimes=(max-min);
	while((retryTimes--)>0){
		q=range(min,max);
		if(gcd(d,q-1)==1 && !isComposite(q))break;
	}
	if(retryTimes==0)return false;

	//
	//cout<<"p:"<<p<<" q:"<<q<<endl;
	e=this->getInverseMod(d,(p-1)*(q-1));
	n=p*q;
	return true;
}
	inline bool setDecpytParam(const LargeNumber& key,const LargeNumber& publicKey){n=publicKey;d=2*key+1;return true;}
	inline const LargeNumber encrypt(const LargeNumber& M){return expMod(M,e,n);}
	inline const LargeNumber decrypt(const LargeNumber& C){return expMod(C,d,n);}
	inline const LargeNumber& getPublicKey()const{return n;}
	inline const LargeNumber& getP()const{return p;}
	inline const LargeNumber& getQ()const{return q;}

};
#endif