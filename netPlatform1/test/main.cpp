#include<iostream>
using namespace std;
#define Trace(m) cout<<#m"="<<(m)<<endl;
class B{
protected:
	int d;
};
class A:public B{
private:
	int a;
protected:
	int b;
public:
	int c;
	void print(){
		Trace(a);
			Trace(b);
				Trace(c);
				}
	static void test(A * t){
		//have access to all varibales except the private member drived from based class
		t->a=1;
		t->b=2;
		t->c=3;
		t->d=8;
	}
};
int main(){
	A t;
	t.test(&t);
	t.print();
	return 0;
};