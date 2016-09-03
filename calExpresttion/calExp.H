#include "List.h"
#include "basicCal.h"//请自行定义,以实现不同功能.
char *mainCal(char *exp);
char *calExp(char *exp);
char *cal(char *exp);
int getMaxIndex(List &list);
int findIndex(char *str,char ch);
int findLastIndex(char *str,char ch);
char *subStr(char *str,int start,int end);
void strSplice(char * &str,int start,int end,char *substr);
bool isSign(char ch);
