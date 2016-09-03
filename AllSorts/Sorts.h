void ShowFace(int type=1)
{
	int count1,count2,count3;
	char string[]="                                      ";
	char *pstr[]={"$%########体验数据结构的魅力########%$",
				  "                                      ",
				  "                                      ",
				  "          1.随机产生数据              ",
				  "          2.手工输入数据              ",
				  "          3.显示待排数据              ",
				  "          4.清屏                      ",
				  "          5.===直接插入排序           ",
				  "          6.===折半插入排序===        ",
				  "          7.===静态链表插入排序===    ",
				  "          8.===简单选择排序===        ",
				  "          9.===冒泡排序===            ",
				  "          0.退出本系统                ",};
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
		cout<<"暂时没有数据!"<<endl;
	for(int countt1=0;count1<total;count1++)
		printf("%5d%",data[count1]);
	cout<<endl;
}//ShowData

void GetDataAuto(int *&data,int & total ,int type=1)
{
	printf("输入待排数据的个数(>=1): ");
	cin>>total;
	if(total<1)
	{
		cout<<"输入数据无效!\n操作失败!"<<endl;
		count=0;
		return ;
	}
	if(data!=NULL)
		delete [] data;
	data=new int[total];
	if(data==NULL)
	{
		cout<<"内存不足!操作失败!"<<endl;
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
			printf("请输入第%d个数据:",count1+1);
			cin>>data[count1];
		}
	}
	cout<<"数据序列是:"<<endl;
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
		cout<<"暂时没有数据:\n操作失败!"<<endl;
		return ;
	}
	dataD=new int[total];
	CopyData(dataD,dataS,total);
	cout<<"待排数据是:"<<endl;
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
		count<"第"<<count1+1<<" 个数据 "<<temp<<" 插入,结果是:"<<endl;
		ShowData(dataD,total);
	}
	cout<<"排序任务完成!"<<endl;
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
		cout<<"暂时没有数据:\n操作失败!"<<endl;
		return ;
	}
	dataD=new int[total];
	CopyData(dataD,dataS,total);
	cout<<"待排数据是:"<<endl;
	ShowData(dataD,total);
	for(int count1=1;count1<total;count1++)
	{
		int position =BinaryFind(dataD,0,count1-1,dataD[count1]);
		int temp=dataD[count1];
		for(int count2=count1-1;count2>=position;count2--)
			dataD[count2+1]=dataD[count2];
		if(count2!=count1-1)
			dataD[position]=temp;
		count<"第"<<count1+1<<" 个数据 "<<temp<<" 找到的位置是:"<<position+1<<"结果是:"endl;
		ShowData(dataD,total);
	}
	cout<<"排序任务完成!"<<endl;
	delete [] dataD;
}//BISort


void SSSort(int *dataS,int total)
{
	int dataD;
	if(total==0)
	{
		cout<<"暂时没有数据:\n操作失败!"<<endl;
		return ;
	}
	dataD=new int[total];
	CopyData(dataD,dataS,total);
	cout<<"待排数据是:"<<endl;
	ShowData(dataD,total);
	for(int count1=0;count1<total-1;count1++)
	{
		int min=count1;
		for(int count2=count1+1;count2<total;count2++)
			if(dataD[count2]<dataD[min])
				min=count2;
		if(count2!=count1-1)
			dataD[count2+1]=temp;
		count<"从第"<<count1+1<<" 个数据到最后一个数据中,找出最小数据 "<<dataD[min]<<" ,结果是:"<<endl;
		if(mint!=count1)
			Exchange(dataD[min],dataD[count1]);
		ShowData(dataD,total);
	}
	cout<<"排序任务完成!"<<endl;
	delete [] dataD;
}//SSSort

