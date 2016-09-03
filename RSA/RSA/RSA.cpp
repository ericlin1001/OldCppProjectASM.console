// RSA.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "LargeInt.h"
//A little regret for LargeInt,it is so slow,because there is not so much time left to write this class...
#include "BasicRSA.h"
//RSA also not so satisfying,there are still something to polish...
#include<cstdlib>

#include<iostream>
using namespace std;
//#define Trace(m) cout<<#m"="<<(m)<<endl;
int _tmain(int argc, _TCHAR* argv[])
{
	while(1){
	RSA<LargeInt> a;
	LargeInt key;LargeInt publicKey;
	cout<<"Key(Number):";cin>>key;
	cout<<"Be patient,it's just runing..."<<endl;
	if(!a.setEncyptParam(key,"10","100")){
		//In practices,a.setEncyptParam(key,"10","100") the min and max of P and Q should be bigger,
		//for example:a.setEncyptParam(key,"100000","1000000")
		cout<<"Error setEncyptParam()"<<endl;continue;
	}
	publicKey=a.getPublicKey();
	cout<<"P:"<<a.getP()<<" Q:"<<a.getQ()<<endl;
	cout<<"Public key(P*Q):"<<publicKey<<endl;
	char bufferM[100];
	LargeInt encrypted[100];
	cout<<"plain text(Anything without space):";cin>>bufferM;
	int len=strlen(bufferM);
	int i;
	//you may merge some char as a block,and encrypt the block
	//but ensure that,the size of block shouldn't bigger than the min of Q or Q.
	//For convience,here,we just encrypte each char!
	for(i=0;i<=len;i++){
		encrypted[i]=a.encrypt(bufferM[i]);//process the encryption
		//encrypted is the encrypted text,you can store in file....
	}

	cout<<"After encrypted:";
	for(i=0;i<=len;i++){
		cout<<encrypted[i]<<",";
	}
	cout<<endl;

	RSA<LargeInt> b;
	b.setDecpytParam(key,publicKey);
	char bufferCM[100];
	for(i=0;i<=len;i++){
		bufferCM[i]=b.decrypt(encrypted[i]).getFirstUnit();//process the decryption
	}
	cout<<"After decrypted:"<<bufferCM<<endl;
	system("pause");
	}
	return 0;
}