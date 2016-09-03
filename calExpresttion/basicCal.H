#include<iostream.h>
#include<string.h>
//请包直接包含 #include"calExp.h"即可.

//入口函数是: char *calExp(char *exp);
const int MAXSIZEOFNUM=10;//最大操作数位数.(按字符算)
//下面的函数是需要自定义的,以实现符号的不同含义.
int signLevel(char sign);//定义各操作符的优先级,越大越高.
bool isOperation(char ch);//定义哪些字符是操作数,一般的是(0~9).
char *calTwo(char *LOPT,char *ROPT,char sign);//定义最基本的计算.即保操作符的含义.
//以上三个需自定义.
