#include"complex.h"
#define Case break;case
Complex Complex::operator +(Complex&z){
	Complex res(a+z.a,b+z.b);
	return res;
}
Complex Complex::operator -(Complex&z){
	Complex res(a-z.a,b-z.b);
	return res;
}
Complex Complex::operator *(Complex&z){
	Complex res(a*z.a-b*z.b,a*z.b+b*z.a);
	return res;
}
Complex Complex::opp(){
	Complex res(a,-b);
	return res;
}
Complex Complex::operator /(Complex&z){
	if(z.a==0 && z.b==0){
		throw z;
	}
	double under=z.a*z.a+z.b*z.b;
	
	Complex res=*this*z.opp();
	
	return Complex(res.a/under,res.b/under);
}
void Complex::display(ostream& out){
	if(a==0 ){
		if(b==0){
			out<<0;
		}else if(b==1){
			out<<'i';
		}else if(b==-1){
			out<<"-i";
		}else{
			out<<b<<'i';
		}
	}else{
		out<<a;
		if(b==0){
		}else if(b==1){
			out<<"+i";
		}else if(b==-1){
			out<<"-i";
		}else{
			if(b>0){
				out<<'+'<<b<<'i';
			}else{
				out<<b<<'i';
			}
		}
	}

}
ostream& operator <<(ostream& out,Complex& z){
	z.display(out);
	out<<"\tin operator<<() a="<<z.a<<endl;
	
	return out;
}