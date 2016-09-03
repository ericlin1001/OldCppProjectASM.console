#include<iostream>
using namespace std;
class numCal {
public:
	numCal(int [], int); //    构造函数，形参分别是整形数组、数组长度
	numCal(const numCal&); //拷贝构造函数
	~numCal();                      //      析构函数，要完成释放内存的操作
	int sum();              //      求动态数组arr中size个元素值和
	numCal& operator=(const numCal&); //=运算符重载
	numCal& operator++();                    //前序++运算符重载，使得++A后，A.arr的每个元素值加1 (A为numCal类型的对象，下同)；
	
	numCal operator++(int);                  //后序++运算符重载，使得A++后，A.arr的每个元素值加1。
	//……
	/*void print(){
		cout<<"arr:";
		for(int i=0;i<size-1;i++){
			cout<<arr[i]<<",";
		}
		cout<<arr[i]<<endl;
	}*/
private:
	int size;                       //      数组arr元素个数
	int *arr;                      //      动态数组
};
numCal::numCal(int a[] , int s){
	arr=new int[s];
	size=s;
	for(int i=0;i<size;i++){
		arr[i]=a[i];
	}
}
numCal::numCal(const numCal& n){
	size=n.size;
	arr=new int[size];
	for(int i=0;i<size;i++){
		arr[i]=n.arr[i];
	}
} //拷贝构造函数
numCal::~numCal(){
	delete arr;
}                      //      析构函数，要完成释放内存的操作
int numCal::sum(){
	int answer=0;
	for(int i=0;i<size;i++){
		answer+=arr[i];
	}
	return answer;
}              //      求动态数组arr中size个元素值和
/**/
numCal& numCal::operator=(const numCal& n){
	size=n.size;
	arr=new int[size];
	for(int i=0;i<size;i++){
		arr[i]=n.arr[i];
	}
	return *this;
} //=运算符重载
numCal& numCal::operator++(){
	
	for(int i=0;i<size;i++){
		arr[i]++;
	}
	return *this;
}
numCal numCal::operator++(int){
	numCal old=*this;
	for(int i=0;i<size;i++){
		arr[i]++;
	}
	return old;
}
int main(){
	int a[10]={1,2,3,4,5,6};
	numCal t(a,6);
	t.print();
	t++;
	t.print();
	++t;
	t.print();
	numCal b=t;
	b.print();
	b++;
	numCal c(b);
	c.print();
	return 0;
}
