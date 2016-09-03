//file: LargeInt.h
#ifndef __LARGEINT_H__
#define __LARGEINT_H__
#include<ios>
#include<vector>
using namespace std;
class LargeInt;
ostream& operator<<(ostream &out,const LargeInt &p);
istream& operator<<(istream &in, LargeInt &p);
//

class LargeInt{
	//can and only can contact with char*,int!
public:
	LargeInt();
	LargeInt(const int);
	LargeInt(const char *);
	LargeInt(const LargeInt &p);
	~LargeInt();
	//
	LargeInt& operator =(const LargeInt &p);

	LargeInt& operator +=(const LargeInt &p);
	LargeInt& operator -=(const LargeInt &p);
	LargeInt& operator *=(const LargeInt &p);
	LargeInt& operator /=(const LargeInt &p);
	LargeInt& operator %=(const LargeInt &p);
	//
	LargeInt operator --(int);
	LargeInt& operator --();
	LargeInt operator ++(int);
	LargeInt& operator ++();
	//
	LargeInt operator +(const LargeInt &p)const;
	LargeInt operator -(const LargeInt &p)const;
	LargeInt operator *(const LargeInt &p)const;
	LargeInt operator /(const LargeInt &p)const;
	LargeInt operator %(const LargeInt &p)const;
	//

	bool operator < (const LargeInt &p)const;
	bool operator > (const LargeInt &p)const;
	bool operator ==(const LargeInt &p)const;
	//
	inline bool    	 operator !=(const LargeInt &p)const{return !(*this==p);}
    inline bool   	 operator <=(const LargeInt &p)const{return !(*this>p);}
    inline bool   	 operator >=(const LargeInt &p)const{return !(*this<p);}
	//
	friend ostream& operator<<(ostream &out,const LargeInt &p);
	friend istream& operator>>(istream &in, LargeInt &p);
	#ifdef __TEST__ 
	void print(){
         cout<<"sign:"<<sign;
         cout<<" LargeInt(";
         for(int i=0;i<units.size();i++){
                 if(i!=0)cout<<",";
                 cout<<units[i];
                 
                 }
                 cout<<")"<<endl;
                 }
#endif
private:
	char sign;//+ or -
	typedef unsigned short Unit;
	vector<Unit>units;
#define UNIT_MAX_VALUE 65535
#define UNIT_BASE 	65536
#define UNIT_BASE_MOD_TEN 6
#define POSITIVE_SIGN '+'
#define NEGATIVE_SIGN '-'
	inline bool isZero()const{return unitEqual(0);}
	inline bool isPositive()const{return sign==POSITIVE_SIGN;}
	inline bool isNegative()const{return sign==NEGATIVE_SIGN;}
	inline void setPositive(){sign=POSITIVE_SIGN;}
	inline void setNegative(){sign=NEGATIVE_SIGN;}
    inline void setZero(){while(!units.empty())units.pop_back();addUnit(0);setPositive();}
	inline void changeSign(){if(isPositive())setNegative();else setPositive();}
	void deleteZero(){while(units.back()==0)units.pop_back();if(units.size()==0)addUnit(0);}
	void addUnit(Unit unit=0){units.push_back(unit);}
	void unitAdd(const LargeInt &p){//negelect the sign
		Unit carry=0;
		int i;
		for(i=0;i < p.units.size();i++){
			if(i>=this->units.size()){
				this->addUnit(0);
			}
			this->units[i]+=p.units[i]+carry;
			if(this->units[i]<p.units[i])carry=1;
			else carry=0;
		}
		if(carry==1){
			if(i>=this->units.size()){
				this->addUnit(0);
			}
			while(units[i]>=UNIT_MAX_VALUE){
				units[i]=0;
				i++;
				if(i>=this->units.size()){
					this->addUnit(0);break;
				}
			}
			this->units[i]++;
		}
	}
	
	void unitSubtract(const LargeInt &p){//this should ensure the answer is positive,that is this larger or equal than p
		Unit carry=0;
		int i;
		for(i=0;i < this->units.size();i++){
			Unit oldUnit=this->units[i];
			this->units[i]-=p.getUnit(i)+carry;
			if(this->units[i]>oldUnit)carry=1;
			else carry=0;
		}
	}
	bool unitBigger(const LargeInt &p)const{
		int i=max(units.size(),p.units.size())-1;
		while(i>=0 && this->getUnit(i)==p.getUnit(i))i--;
		if(getUnit(i)>p.getUnit(i))return true;
		return false;
		
	}
	bool unitLess(const LargeInt &p)const{
		int i=max(units.size(),p.units.size())-1;
		while(i>=0 && this->getUnit(i)==p.getUnit(i))i--;
		if(getUnit(i)<p.getUnit(i))return true;
		return false;
	}
	bool unitEqual(const LargeInt &p)const{
		int i=max(units.size(),p.units.size())-1;
		while(i>=0 && this->getUnit(i)==p.getUnit(i))i--;
		if(getUnit(i)!=p.getUnit(i))return false;
		return true;
	}
	Unit getUnit(int i)const{
		if(i<units.size())return units[i];
		else return 0;
	}
};
inline LargeInt operator +(const int i,const LargeInt &p){return LargeInt(i)+p;}
inline LargeInt operator -(const int i,const LargeInt &p){return LargeInt(i)-p;}
inline LargeInt operator *(const int i,const LargeInt &p){return LargeInt(i)*p;}
inline LargeInt operator /(const int i,const LargeInt &p){return LargeInt(i)/p;}
inline LargeInt operator %(const int i,const LargeInt &p){return LargeInt(i)%p;}
//
inline LargeInt operator +(const char*str,const LargeInt &p){return LargeInt(str)+p;}
inline LargeInt operator -(const char*str,const LargeInt &p){return LargeInt(str)-p;}
inline LargeInt operator *(const char*str,const LargeInt &p){return LargeInt(str)*p;}
inline LargeInt operator /(const char*str,const LargeInt &p){return LargeInt(str)/p;}
inline LargeInt operator %(const char*str,const LargeInt &p){return LargeInt(str)%p;}
//
#endif
