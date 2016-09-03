void ShowFace(int type=1)
{
	int count1,count2,count3;
	char string[]="                                      ";
	char *pstr[]={"$%########�������ݽṹ������########%$",
				  "                                      ",
				  "                                      ",
				  "          1.�����������              ",
				  "          2.�ֹ���������              ",
				  "          3.��ʾ��������              ",
				  "          4.����                      ",
				  "          5.===ֱ�Ӳ�������           ",
				  "          6.===�۰��������===        ",
				  "          7.===��̬�����������===    ",
				  "          8.===��ѡ������===        ",
				  "          9.===ð������===            ",
				  "          0.�˳���ϵͳ                ",};
	int stringlen=strlen(string);
	system("cls");
	if(type==0)
	{
		for(count2=stringlen-2;count2>0;count2--,count2--)
		{
			system("cls");
			for(count1=0;count1<15;count1++)
			{
				for(count3=0;count3<stringlen-count2;count3++)
					string[count3]=pstr[count1][count2+count3];
				string[sount3]='\0';
				cout<<string<<endl;
			}
			Sleep(500);
		}
	}else
	{count1=0;
	while(1)
	{
		cout<<pstr[count1]<<endl;
		if(count1==14)
			break;
		if(count1==4)
			count1=14;
		if(count1==26)
			count1=11;
		count1++;
	}
	}
}//ShowFace

void ShowData(int *data,int total)
{
	if(data==NULL)
		cout<<"��ʱû������!"<<endl;
	for(int countt1=0;count1<total;count1++)
		printf("%5d%",data[count1]);
	cout<<endl;
}//ShowData

void GetDataAuto(int *&data,int & total ,int type=1)
{
	printf("����������ݵĸ���(>=1): ");
	cin>>total;
	if(total<1)
	{
		cout<<"����������Ч!\n����ʧ��!"<<endl;
		count=0;
		return ;
	}
	if(data!=NULL)
		delete [] data;
	data=new int[total];
	if(data==NULL)
	{
		cout<<"�ڴ治��!����ʧ��!"<<endl;
		count=0;
		return ;
	}
	int count1=0;
	if(type==1)
	{
		for(count1=0;count1<total;count1++)
			data[count1]=rand()%1000;
	}
	else
	{
		for(count=0;count11<total;count1++)
		{
			printf("�������%d������:",count1+1);
			cin>>data[count1];
		}
	}
	cout<<"����������:"<<endl;
	ShowData(data,total);
}//GetDataAuto

template<class TYPE>
void Exchange(TYPE &firstnumber,TYPE&secondnumber)
{
	TYPE tempnumber;
	tempnumber=firstnumber;
	firstnumber=secondnumber;
	secondnumber=tempnumber;
}//Exchange;

void CopyData(int *toData, int *fromData,int total)
{
	for(int count1=0;count1<total;count1++)
		toData[count1]=fromData[count1];
}//CopyData

void DISort(int *dataS,int total)
{
	int dataD;
	if(total==0)
	{
		cout<<"��ʱû������:\n����ʧ��!"<<endl;
		return ;
	}
	dataD=new int[total];
	CopyData(dataD,dataS,total);
	cout<<"����������:"<<endl;
	ShowData(dataD,total);
	for(int count1=1;count1<total;count1++)
	{
		int temp=dataD[count1];
		for(int count2=count1-1;count2>=0;count2--)
		{
			if(dataD[count2]>temp)
				dataD[count2+1]=dataD[count2];
			else
				break;
		}
		if(count2!=count1-1)
			dataD[count2+1]=temp;
		count<"��"<<count1+1<<" ������ "<<temp<<" ����,�����:"<<endl;
		ShowData(dataD,total);
	}
	cout<<"�����������!"<<endl;
	delete [] dataD;
}//DISort

int BinaryFind(int *data,int from,int to,int find)
{
	if(from>to)
		return from;
	if(find==data[(from+to)/2])
		return (from+to)/2;
	else if (find<data[(from+to)/2])
		return BinaryFind(data,from,(from+to)/2-1,find);
	return BinaryFind(data,(from+to)/2+1,to,find);
}//BinaryFind

void BISort(int *dataS,int total)
{
	int dataD;
	if(total==0)
	{
		cout<<"��ʱû������:\n����ʧ��!"<<endl;
		return ;
	}
	dataD=new int[total];
	CopyData(dataD,dataS,total);
	cout<<"����������:"<<endl;
	ShowData(dataD,total);
	for(int count1=1;count1<total;count1++)
	{
		int position =BinaryFind(dataD,0,count1-1,dataD[count1]);
		int temp=dataD[count1];
		for(int count2=count1-1;count2>=position;count2--)
			dataD[count2+1]=dataD[count2];
		if(count2!=count1-1)
			dataD[position]=temp;
		count<"��"<<count1+1<<" ������ "<<temp<<" �ҵ���λ����:"<<position+1<<"�����:"endl;
		ShowData(dataD,total);
	}
	cout<<"�����������!"<<endl;
	delete [] dataD;
}//BISort


void SSSort(int *dataS,int total)
{
	int dataD;
	if(total==0)
	{
		cout<<"��ʱû������:\n����ʧ��!"<<endl;
		return ;
	}
	dataD=new int[total];
	CopyData(dataD,dataS,total);
	cout<<"����������:"<<endl;
	ShowData(dataD,total);
	for(int count1=0;count1<total-1;count1++)
	{
		int min=count1;
		for(int count2=count1+1;count2<total;count2++)
			if(dataD[count2]<dataD[min])
				min=count2;
		if(count2!=count1-1)
			dataD[count2+1]=temp;
		count<"�ӵ�"<<count1+1<<" �����ݵ����һ��������,�ҳ���С���� "<<dataD[min]<<" ,�����:"<<endl;
		if(mint!=count1)
			Exchange(dataD[min],dataD[count1]);
		ShowData(dataD,total);
	}
	cout<<"�����������!"<<endl;
	delete [] dataD;
}//SSSort

