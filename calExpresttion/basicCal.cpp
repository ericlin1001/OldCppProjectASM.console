#include "basicCal.h"
//����ĺ�������Ҫ�Զ����,��ʵ�ַ��ŵĲ�ͬ����.
char *calTwo(char *LOPT,char *ROPT,char sign){
	//����������ļ���.�����������ĺ���.
	char *answer=new char[MAXSIZEOFNUM+1];
	strcpy(answer,LOPT);
	cout<<"calculate:"<<LOPT<<sign<<ROPT<<"="<<answer<<endl;
	return answer;
}
int signLevel(char sign){
	//����������������ȼ�,Խ��Խ��.
	int level=-1;
	switch(sign){
	case '+':
	case '-':
		level=0;
		break;
	case '*':
	case '/':
		level=1;
		break;
	case '^':
		level=2;
		break;
	case '%':
		level=3;
		break;
	default:
		break;
	}
	return level;
}
bool isOperation(char ch){
	//������Щ�ַ��ǲ�����,һ�����(0~9).
	int i=ch;
	return (48<=i && i<=57);
}
//�����������Զ���.