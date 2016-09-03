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
	union{
		int a;
		char str1[10];
		char str2[20];
		int b;
	} t;
	t.a=10;
	Trace(t.b);
	strcpy(t.str2,"abc");
	Trace(t.str1);
	char *p=(char *)&t;

	Trace(p);
	/*
	A t;
	t.test(&t);
	t.print();
	return 0;*/
	return 0;
};

	/*
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);v.push_back(4);
	Trace(v.size());
	v.pop_back();
	Trace(v.back());
	Trace(v.front());
	Trace(v.at(2));
	vector<int>::iterator iv;
	for(iv=v.begin();iv!=v.end();iv++){
		Trace(*iv);
	}
	//4 3 1 3 1 2 3
*/