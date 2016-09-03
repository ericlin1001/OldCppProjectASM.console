#include<iostream.h>
class Increase{
public:
	Increase(int num):i(num){}
	void display(){
		cout<<"the i is: "<<i<<endl;
	}
	Increase &operator++();
	friend Increase operator++(Increase&t,int);
private:
	int i;
};
Increase &Increase::operator++(){
	//Ç°×º
	i++;
	return *this;
}
Increase operator++(Increase&t,int){
	//ºó×º
	++t;
	return Increase(t.i-1);
}
int main(){
	Increase a(10);
	a.display();//10
	(a++).display();//10
	++a;
	a.display();//12
	++(++a);
	a.display();//14
	(a++)++;
	a.display();//15
	return 0;
}