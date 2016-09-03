#include<iostream>
using namespace std;
int f1(int a[][2],int size){
	return 1;
}
int f2(int b[5][2]){
	return 1;
}
int print(int a[4],int size){
	for(int i=0;i<size;i++)cout<<a[i]<<',';
	cout<<endl;
	return 0;
}
int main(){
	int k[4][2];
	f2(k);
	f1(k,5);
	int u[10]={1,2,3,4,5,6,7,8,9,0};
	print(u,10);
	int a=3,b=5,c;
	c=a*(b=4)+b;
	cout<<c<<endl;
	for(int i=0;i<50;i++){
		for(int j=0;j<50;j++){
			if(i*j==60){
				continue;
				cout<<i<<'*'<<j<<'='<<i*j<<endl;
				goto end;
				break;
			}
		}
	}
end:
    cin>>k[0][0];
	return 0;
}
