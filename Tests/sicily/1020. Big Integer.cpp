#include<iostream>
#include<cstring>
using namespace std;
#define MAXOFCASES 500
#define MAXOFINSTANCES 100
#define MAXLENOFINT 400
//
//question structure:
class CaseType{
public:
	CaseType(){}
	int num;
	int arr[MAXOFINSTANCES];
	char bigInt[MAXLENOFINT];
private:
};
void swap(char &a,char &b){
	char t=a;
	a=b;
	b=t;
}
istream &operator>>(istream &in,CaseType &t){
	in>>t.num;
	for(int i=0;i<t.num;i++){
		in>>t.arr[i];
	}
	in>>t.bigInt;
	return in;
}
//
//answers structure:
class AnswerType{
public:
	AnswerType(){}
	int num;
	int arr[MAXOFINSTANCES];
private:
};
ostream &operator<<(ostream &out,AnswerType &t){
	out<<"(";
	for(int i=0;i<t.num-1;i++){
		cout<<t.arr[i]<<",";
	}
	cout<<t.arr[i]<<")";
	return out;
}
void bigAdd(char *a,char *b){
}
void bigSub(char *a,char *b){
}
void bigMul(char *a,int b){
	for(int i=0;i<
}
int getMode(char *big,int num){
	
	return a;
}
//
//the main function:
AnswerType getAnswer(CaseType &cases){
	AnswerType answer;
	answer.num=cases.num;
	//
	int i,j;
	int len=strlen(cases.bigInt);
	for(i=0;i<len/2;i++){
		swap(cases.bigInt[i],cases.bigInt[len-1-i]);
	}
	for(i=0;i<cases.num;i++){
		answer.arr[i]=getMode(cases.bigInt,cases.num);
	}
	//
	return answer;
}
//
//
int main()
{
	
	AnswerType answers[MAXOFCASES];
	//
	CaseType cases;
	int caseCount=0;
	int maxCases;
	cin>>maxCases;
	while(caseCount<=maxCases){
		cin>>cases;
		answers[caseCount]=getAnswer(cases);
		caseCount++;
	}
	int i;
	for( i=0;i<caseCount;i++){
		cout<<"answers["<<i<<"]="<<answers[i]<<"."<<endl;
		
	}
	return 0;
}