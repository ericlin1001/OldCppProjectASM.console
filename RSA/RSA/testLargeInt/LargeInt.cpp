/*#ifdef __TEST__
#include <iostream>
#include "LargeInt.h"
using namespace std;
#define Trace(m) cout<<#m"="<<(m)<<endl;
#endif*/

//
//file: LargeInt.cpp
#include "LargeInt.h"
#include<iostream>
ostream& operator<<(ostream &out,const LargeInt &p){
	LargeInt k=p;
	if(k.isNegative()){
		out<<'-';
	}
	if(k.isZero())out<<'0';
	else{	
          vector<char>strnum;
          k.setPositive();
		while(k!=0){
 // cout<<"k is ";k.print();
			LargeInt::Unit remain=0;
			LargeInt::Unit power=1;
			for(int i=0;i<k.units.size();i++){
				remain+=(k.units[i]%10)*power;
				remain%=10;
				//
				power*=UNIT_BASE_MOD_TEN;
				power%=10;
				
			//	cout<<" i is "<<i<<endl;
			}
		//	cout<<"Remain"<<remain<<endl;
			
			strnum.push_back('0'+remain);

            k/=10;
		}
		for(int i=strnum.size()-1;i>=0;i--){
			out<<strnum[i];
		}
	}
	return out;
}
istream& operator>>(istream &in,LargeInt &p){
	char buffer[1000];
	in>>buffer;
	p=LargeInt(buffer);
	return in;
}
//
LargeInt::LargeInt(){
	setPositive();
	addUnit(0);
}
LargeInt::LargeInt(const int n){
	int k=n;
	if(n<0){setNegative();k=-k;}
	else  setPositive();
	if(k==0){addUnit(0);return ;}
	while(k!=0){
		addUnit(k%UNIT_BASE);
		k/=UNIT_BASE;
	}
}
LargeInt::LargeInt(const char * const str){
	int p=0;
	if(str[0]=='-'){p++;}
	else setPositive();
	int len=strlen(str);
	addUnit(0);
	for(int i=p;i<len;i++){
		(*this)*=10;
		(*this)+=str[i]-'0';
	}
	if(str[0]=='-'){setNegative();}
}
LargeInt::LargeInt(const LargeInt &p){
	sign=p.sign;
	units=p.units;
}
LargeInt::~LargeInt(){
}
//
LargeInt&	LargeInt::operator = (const LargeInt &p){
	sign=p.sign;
	units=p.units;
	return *this;
}
LargeInt&	LargeInt::operator +=(const LargeInt &p){
	if(sign==p.sign){
		unitAdd(p);
	}else{
		if(unitLess(p)){
                        
			LargeInt temp=p;
			temp.unitSubtract(*this);
			*this=temp;
		}else{
       
			//needn't to change sign
			unitSubtract(p);
		}
	}
	deleteZero();
	return *this;
}
LargeInt&	LargeInt::operator -=(const LargeInt &p){
	changeSign();
	*this+=p;
	changeSign();
	

	deleteZero();
	return *this;
}
LargeInt&	LargeInt::operator *=(const LargeInt &p){
if(p.isZero()){this->setZero();return *this;}
	//the basic one!:
	LargeInt i=p;
	LargeInt orign=*this;
	
	i.unitSubtract(1);
	while(i.unitBigger(0)){
		unitAdd(orign);
		i.unitSubtract(1);
	}
	//set sign:
	if(orign.sign==p.sign)setPositive();
	else setNegative();
	//
	deleteZero();
	return *this;
}
LargeInt&	LargeInt::operator /=(const LargeInt &p){
     if(p.isZero()){this->setZero();return *this;}//this should arouse a error!     
	LargeInt orign=*this;
	this->setZero();
	while(!orign.unitLess(p)){
		unitAdd(1);
		orign.unitSubtract(p);
	}
	//set sign:
	if(orign.sign==p.sign)setPositive();
	else setNegative();
	//
	deleteZero();
	return *this;
}
LargeInt&	LargeInt::operator %=(const LargeInt &p){
	while(!this->unitLess(p)){
		this->unitSubtract(p);
	}
	//set sign:
	deleteZero();
	return *this;
}
//
bool    	LargeInt::operator < (const LargeInt &p)const{
	if(sign==p.sign){
		return isNegative()^unitLess(p);
	}else{
		if(isNegative())return true;
		else return false;
	}
}
bool    	LargeInt::operator > (const LargeInt &p)const{
	if(sign==p.sign){
		return isNegative()^unitBigger(p);
	}else{
		if(isNegative())return false;
		else return true;
	}
}
bool    	LargeInt::operator ==(const LargeInt &p)const{
	if(sign==p.sign && unitEqual(p))return true;
	return false;
}
//
//
//
//
//
//
//
//below don't need to change!!!
//
LargeInt  LargeInt::operator --(int){
	LargeInt temp=*this;
	(*this)-=1;
	return temp;
}
LargeInt& LargeInt::operator --(){
	(*this)-=1;
	return *this;
}
LargeInt  LargeInt::operator ++(int){
	LargeInt temp=*this;
	(*this)+=1;
	return temp;
}
LargeInt& LargeInt::operator ++(){
	(*this)+=1;
	return *this;
}
//

//
LargeInt LargeInt::operator +(const LargeInt &p)const{
	LargeInt an=*this;
	an+=p;
	return an;
}
LargeInt LargeInt::operator -(const LargeInt &p)const{
	LargeInt an=*this;
	an-=p;
	return an;
}
LargeInt LargeInt::operator *(const LargeInt &p)const{
	LargeInt an=*this;
	an*=p;
	return an;
}
LargeInt LargeInt::operator /(const LargeInt &p)const{
	LargeInt an=*this;
	an/=p;
	return an;
}
LargeInt LargeInt::operator %(const LargeInt &p)const{
	LargeInt an=*this;
	an%=p;
	return an;
}
//


//

//


