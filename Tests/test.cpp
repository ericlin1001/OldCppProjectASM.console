#include<iostream>
using namespace std;
typedef char * Pointer;
typedef bool Bit;
//
Bit getBit(Pointer p,int index){
	//bit is unit of size
	return (*(p+index/8) & (1<<(index%8)))!=0;
}
int main(){
	float f=15.25f;
	for(int i=32-1;i>=0;i--){
		//print from high address to low address
		cout<<(getBit((Pointer)&f,i)?'1':'0');
	}
	cout<<endl;
	return 0;
}
//output:01000001011101000000000000000000

/*#include<iostream>
#include<cmath>
using namespace std;
#define Trace(m,sep) cout<<#m<<sep<<(m)<<endl;
int main(){
	double d=0;
	int numLoop=0;
	while(!(fabs(d-1.0)<1e-8)){//this will cause infinite loop
		cout<<"Loop "<<numLoop++<<":"<<endl;
		d+=0.1;
		Trace(d,"=");
		Trace(d==1.0," is ");
	}
	return 0;

}*/
//d=0.99999999999999989
/*
#include<iostream>
using namespace std;
#define Trace(m) cout<<#m<<'='<<(m)<<endl;
int main(){
	double d=0;
	double sum=0;
	
//	Trace(d);
//	Trace(d!=10.0);
	//this will cause infinite loop
	while(d!=1.0){
		d+=0.1;
		Trace(d);
		Trace(d!=1.0);
		sum+=d;
	}
	cout<<sum<<endl;

	return 0;

}*/
/*#include<iostream>
using namespace std;
#define Trace(m) cout<<#m<<'='<<(m)<<endl;
int main(){
	double d=0;
	double sum=0;
	double q=5;
	float p=5;
	Trace(q==5.0);
//	return 0;
	//
//	d=9.9;
//	d+=0.1;
	Trace(d);
	Trace(d!=10.0);
	while(d!=1.0){
		d+=0.1;
			Trace(d);
		Trace(d!=1.0);
		sum+=d;
	}
	cout<<sum<<endl;
	return 0;//0+0.1+...10
	int a ,b;
	double c;
	a =1/2;Trace(a);
	a =(double)1/2;Trace(a);
	a =1/(double)2;Trace(a);
	a =(double)1/(double)2;Trace(a);
	a =(double)(1/2);Trace(a);
	
	c =1/2;Trace(c);
	c =(double)1/2;Trace(c);
	c =1/(double)2;Trace(c);
	c =(double)1/(double)2;Trace(c);
	c =(double)(1/2);Trace(c);
	return 0;

}*/