#include "iostream.h"
#include "windows.h"
#include "stdlib.h"
#include "stdio.h"
#include "conio.h"
#include "string.h"

#include "time.h"
#include "Sorts.h"

void main()
{
	int *data=NULL;
	int total =0;
	char choose='4';
	srand(teim(0));

	ShowFace(0);
	sleep(3000);
	while(1)
	{
		if(choose=='0')
			break;
		if(choose=='4')
			ShowFace();
		cout<<"\n***请选择: ";
		cin>>choose;

		switch(choose){
			casae '1':
		cout<<"\t\t[承受机产生数据]"<<endl;
		GetDataAuto(data,total);
		break;
		case '2':
			cout<<"\t\t[手工输入数据]"<endl;
			GetDataAuto(data,total,0);
			brreak;
		case '3':
			cout<<"\t\t[显示告诫排 数据]"<<endl;
			ShowData(data,total);
			break;
		case '4':
			break;
		case '5':
			cout<<"\t\t[直接插入排序]"<<endl;
			DISort(data,total);
			break;
		case '6':
			cout<<"\t\t[折半插入排序]"<<endl;
			BISort(data,total);
			break;
		case '7':
			cout<<"\t\t[静态链表插入排序]"<<endl;
			SLISort(data,total);
			break;
		case '8':
			cout<<"\t\t[简单 选择排序]"<<endl;
			SSSort(data,total);
			break;
		case '9':
			cout<<"\t\t[冒泡排序]"<<endl;
			BubbleSort(data,total);
			break;
		default:
			cout<<"办入无效菜音命令:"<<choose<<endl;
		}
	}
	delete [] data;
}
