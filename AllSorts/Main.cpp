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
		cout<<"\n***��ѡ��: ";
		cin>>choose;

		switch(choose){
			casae '1':
		cout<<"\t\t[���ܻ���������]"<<endl;
		GetDataAuto(data,total);
		break;
		case '2':
			cout<<"\t\t[�ֹ���������]"<endl;
			GetDataAuto(data,total,0);
			brreak;
		case '3':
			cout<<"\t\t[��ʾ����� ����]"<<endl;
			ShowData(data,total);
			break;
		case '4':
			break;
		case '5':
			cout<<"\t\t[ֱ�Ӳ�������]"<<endl;
			DISort(data,total);
			break;
		case '6':
			cout<<"\t\t[�۰��������]"<<endl;
			BISort(data,total);
			break;
		case '7':
			cout<<"\t\t[��̬�����������]"<<endl;
			SLISort(data,total);
			break;
		case '8':
			cout<<"\t\t[�� ѡ������]"<<endl;
			SSSort(data,total);
			break;
		case '9':
			cout<<"\t\t[ð������]"<<endl;
			BubbleSort(data,total);
			break;
		default:
			cout<<"������Ч��������:"<<choose<<endl;
		}
	}
	delete [] data;
}
