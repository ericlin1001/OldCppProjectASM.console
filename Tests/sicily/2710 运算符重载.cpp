#include<iostream>
using namespace std;
class numCal {
public:
	numCal(int [], int); //    ���캯�����βηֱ����������顢���鳤��
	numCal(const numCal&); //�������캯��
	~numCal();                      //      ����������Ҫ����ͷ��ڴ�Ĳ���
	int sum();              //      ��̬����arr��size��Ԫ��ֵ��
	numCal& operator=(const numCal&); //=���������
	numCal& operator++();                    //ǰ��++��������أ�ʹ��++A��A.arr��ÿ��Ԫ��ֵ��1 (AΪnumCal���͵Ķ�����ͬ)��
	
	numCal operator++(int);                  //����++��������أ�ʹ��A++��A.arr��ÿ��Ԫ��ֵ��1��
	//����
	/*void print(){
		cout<<"arr:";
		for(int i=0;i<size-1;i++){
			cout<<arr[i]<<",";
		}
		cout<<arr[i]<<endl;
	}*/
private:
	int size;                       //      ����arrԪ�ظ���
	int *arr;                      //      ��̬����
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
} //�������캯��
numCal::~numCal(){
	delete arr;
}                      //      ����������Ҫ����ͷ��ڴ�Ĳ���
int numCal::sum(){
	int answer=0;
	for(int i=0;i<size;i++){
		answer+=arr[i];
	}
	return answer;
}              //      ��̬����arr��size��Ԫ��ֵ��
/**/
numCal& numCal::operator=(const numCal& n){
	size=n.size;
	arr=new int[size];
	for(int i=0;i<size;i++){
		arr[i]=n.arr[i];
	}
	return *this;
} //=���������
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
