#include "basicCal.h"
//下面的函数是需要自定义的,以实现符号的不同含义.
char *calTwo(char *LOPT,char *ROPT,char sign){
	//定义最基本的计算.即保操作符的含义.
	char *answer=new char[MAXSIZEOFNUM+1];
	strcpy(answer,LOPT);
	cout<<"calculate:"<<LOPT<<sign<<ROPT<<"="<<answer<<endl;
	return answer;
}
int signLevel(char sign){
	//定义各操作符的优先级,越大越高.
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
	//定义哪些字符是操作数,一般的是(0~9).
	int i=ch;
	return (48<=i && i<=57);
}
//以上三个需自定义.