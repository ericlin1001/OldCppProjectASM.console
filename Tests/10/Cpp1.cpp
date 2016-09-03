#include<iostream>
using namespace std;
/*void m2n(int m, char* mNum, int n, char* nNum) 
{
	int i = 0;
	char c, *p = nNum;
	//这是一个考察地方，是否能用最少乘法次数。
	while (*mNum != '\0')
		i = i*m + *mNum++ - '0';
	//辗转取余
	while (i) {
		*p++ = i % n + '0';
		i /= n;
	}
	*p-- = '\0';

	//逆置余数序列
	while (p > nNum) {
		c = *p;
		*p-- = *nNum;
		*nNum++ = c;
	}
}
*/
int main()
{
	while(0){/*
		int t;
		char buffer[1000];
		char answer[1000];
		cin>>t>>buffer;

		m2n(10,buffer,2,answer);
		//cout<<"ans:";
		//cout<<answer<<endl;
		char *p=answer;
		int k;
		while(*p!=0){
		}
		cout<<k<<endl;*/
		/*
		m2n(2,answer,t,buffer);
		cout<<"buff:";
		cout<<buffer<<endl;

		m2n(t,buffer,10,answer);
		cout<<"ans:";
		cout<<answer<<endl;*/

		}
	unsigned long k,n;
	unsigned long kk;
	unsigned long answer;
	while(1){
		kk=1;
		answer=0;
		cin>>k>>n;
		for(int i=n;i>0;i=i>>1)
		{
			answer+=kk*(i&0x1);
			kk*=k;
		}
		cout<<answer<<endl;
	}
	return 0;
}
