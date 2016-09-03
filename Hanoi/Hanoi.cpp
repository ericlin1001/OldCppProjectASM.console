#include<fstream.h>
void move(int num,char *stick1,char *stick2)
{
	cout<<"move "<<num<<" from "<<stick1<<" to "<<stick2<<endl;
}
void hanoi(int num,char *stick1,char *stick2,char *stick3)
{
	if(num==1){
		move(1,stick1,stick3);
	}else{
		hanoi(num-1,stick1,stick3,stick2);
		move(num,stick1,stick3);
		hanoi(num-1,stick2,stick1,stick3);
	}
}

int main()
{
	hanoi(3,"A","B","C");
	return 0;
}