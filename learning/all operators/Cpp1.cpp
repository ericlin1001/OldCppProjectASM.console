#include<iostream.h>
class Value{
public:
	Value(int i){
		cout<<"\nin Value(int i)"<<endl;
		this->i=i;
		
	}
	Value(Value& va){
		cout<<"\nin Value(Value&)"<<endl;
		i=va.i;
		
	}
	void display(){
		cout<<"\nin display()"<<endl;
		cout<<"i="<<i<<endl;
		
	}
	//
	operator int(){
		cout<<"\nin operator int()"<<endl;
		return i;
	}
	//
	Value operator +(Value &v){
		cout<<"\nin operator +(Value &v)"<<endl;
		return Value(i+v.i);
	}
	Value operator -(Value &v){
		cout<<"\nin operator -(Value &v)"<<endl;
		return Value(i-v.i);
	}
	Value operator *(Value &v){
		cout<<"\nin operator *(Value &v)"<<endl;
		return Value(i*v.i);
	}
	Value operator /(Value &v){
		cout<<"\nin operator /(Value &v)"<<endl;
		return Value(i/v.i);
	}
	//
	Value &operator =(Value &v){
		cout<<"\nin operator =(Value &v)"<<endl;
		i=v.i;
		return *this;
	}
/**/	Value &operator +=(Value &v){
		cout<<"\nin operator +=(Value &v)"<<endl;
		i+=v.i;
		return *this;
	}
	Value &operator -=(Value &v){
		cout<<"\nin operator -=(Value &v)"<<endl;
		i-=v.i;
		return *this;
	}
	Value &operator *=(Value &v){
		cout<<"\nin operator *=(Value &v)"<<endl;
		i*=v.i;
		return *this;
	}
	Value &operator /=(Value &v){
		cout<<"\nin operator /=(Value &v)"<<endl;
		i/=v.i;
		return *this;
	}
	Value &operator ++(){
		i++;
		return *this;
	}
	Value operator ++(int){
		Value temp(*this);
		i++;
		return temp;
	}
	Value &operator --(){
		i--;
		return *this;
	}
	Value operator --(int){
		Value temp(*this);
		i--;
		return temp;
	}
	//
	ostream& operator<<(ostream &out){
		out<<i;
		return out;
	}
	istream& operator>>(istream &in){
		in>>i;
		return8 in;
	}
protected:
	int i;

};
int main(){
	
	Value a(1),b(2),c(0);
	c=a+b;//3
	c+=a;//4
	c.display();
	cout<<"\na,b,c:"<<endl;
	//cin>>a>>b>>c;
	cout<<a<<","<<b<<","<<c<<endl;
	cout<<a++<<endl;
	cout<<++a<<endl;
	a=(--b)+(c--);
	a.display();
	
	return 0;
}
