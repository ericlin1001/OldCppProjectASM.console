#include<iostream.h>
class Complex{
public:
	Complex(double i,double j){
		a=i;
		b=j;
	}
	Complex(Complex &z){
		a=z.a;
		b=z.b;
	}
	Complex operator +(Complex&);
	Complex operator -(Complex&);
	Complex operator *(Complex&);
	Complex operator /(Complex&);
	Complex opp();
	void display(ostream& out);
	friend ostream& operator <<(ostream&,Complex&);
private:
	double a,b;
};
ostream& operator <<(ostream&,Complex&);