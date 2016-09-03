#include<iostream>
#include<cstring>
#include<vector>
#include<winsock2.h>
#include<cstdlib>
#include<fstream>
using namespace std;
#include "../definedMess.h"
//
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
int count;
int a;
int & f(){
	if(count++==0){
		return a;
	}else{
		return count;
	}
}
class T{
public:
	T(){
		a=count++;
	}
	int a;
	void print(){
		cout<<"a="<<a<<endl;
	}
};
class E{
public:
	char a[20];
	E(){}
	/*E(E &p){
		strcpy(a,p.a);
	}*/
	void set(char *p){
		strcpy(a,p);
	}
	void print(){
		Trace(a);
	}
};

vector< E> v;
void * add(char *p){
	E e;
	e.set(p);
	v.push_back(e);
	char *pstr=e.a;
	cout<<"e"<<pstr<<endl;
	return  0;
}
//

//vector will copy the another mem of the element.
HANDLE hEvent=NULL;
DWORD WINAPI thread1(LPVOID p){
	cout<<"create"<<endl;
	WaitForSingleObject(hEvent,INFINITE);
	cout<<"run"<<endl;
	return 0;
}
//
#define test
int main(){
	fstream *f;
	ifstream *ifile;
	ofstream *outfile;
	//f=ifile;
	ifile=f;
#ifdef test	
	MyVector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.del(1);
	for(int i=0;!v.empty();i++){
		Trace(v.size());
		cout<<v[0]<<endl;
		if(!v.empty())v.del((unsigned int)0);
	}
	
#else	
	hEvent=CreateEvent(NULL,FALSE,FALSE,NULL);
	while(1){
	cout<<"begin"<<endl;
	CreateThread(NULL,0,&thread1,NULL,0,NULL);
	cout<<"after create"<<endl;
	cin.get();
	SetEvent(hEvent);
	}
	/*
	BEGIN
	CREAT
	after

  run*/


	char *pstr=(char*)*((char **)add("1"));
	cout<<pstr<<endl;
	add("2");
	cout<<pstr<<endl;
	if(1){
		E e;
	e.set("e");
	v.push_back(e);
	}
	E d;
	d.set("d");
	v.push_back(d);
	v.back().print();
	d.print();
	Trace((int)&d==(int)&v.back());
	//
	d.set("er");
	v[0].print();
	v[1].print();
	d.print();
	return 0;

	for(int j=0;j<3;j++){
		v.push_back(T());

	}
	v[0].print();
	v.back().print();
	v.at(1).print();
	Trace(v.size());
	
	return 0;
	for(int i=0;i<2;i++){
		int &p=f();
		p=i+4;
		Trace(a);
		Trace(count);
		//correct:
		/*
		a=4
		count=1
		
		  a=4
		  count=5
		  */
		//no
		/*
		a=4
		c=1

		a=5
		c=2
		*/
	}
	return 0;
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
#endif
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