#include<iostream>
using namespace std;
#define MAXOFCASES 5000
#define MAXOFINSTANCES 1000
//
//question structure:
typedef unsigned long uint;
class QuestionType{
public:
	QuestionType(){}
	uint value;
private:
};
istream &operator>>(istream &in,QuestionType &t){
	in>>t.value;
	return in;
}
//
//answer structure:
class AnswerType{
public:
	uint num;
	uint *arr;
	AnswerType(){
		num=0;
		arr=new uint[MAXOFINSTANCES];
	}
	AnswerType(AnswerType &p){
		num=p.num;
		arr=new uint[p.num];
		for(int i=0;i<p.num;i++){
			arr[i]=p.arr[i];
		};
	}
	AnswerType& operator=(AnswerType& p){
		if(arr!=NULL) delete arr;
		num=p.num;
		arr=new uint[p.num];
		for(int i=0;i<p.num;i++){
			arr[i]=p.arr[i];
		};
		return *this;
	}
	~AnswerType(){
		delete arr;
	}
	uint getBack(){
		return arr[num-1];
	}
	void push(uint a){
		arr[num++]=a;
	}
	void sort(){
		int i,j;
		for(i=1;i<num;i++){
			uint now=arr[i];
			j=i-1;
			while(j>=0 && now<arr[j]){
				arr[j+1]=arr[j];
				j--;
			}
			arr[j+1]=now;
		}
	}

private:
};
ostream &operator<<(ostream &out,AnswerType &t){
	//out<<t.num<<endl;
	int i;
	for( i=0;i<t.num-1;i++){
		out<<t.arr[i]<<"\n";
	}
	out<<t.arr[i];
	return out;
}
//
//the main function:
AnswerType getAnswer(QuestionType * lines,int size){
	AnswerType answer;
	/**/for(int i=0;i<size;i++){
	answer.arr[i]=lines[i].value;
	}
	answer.num=size;
	answer.sort();
	return answer;
}
//
//
int main()
{
	uint *test=new uint[10];
	delete test;
	AnswerType answer[MAXOFCASES];
	//
	QuestionType lines[MAXOFINSTANCES];
	int caseCount=0;
	int numLines=0;
	int maxOfCases;
	cin>>maxOfCases;
	while(caseCount<maxOfCases){
	cin>>numLines;
	if(numLines==0) break;
	//start.
	for(int j=0;j<numLines;j++){
	cin>>lines[j];
	}
	answer[caseCount]=getAnswer(lines,numLines);
	//end.
	caseCount++;
	}
	int i;
	for( i=0;i<caseCount-1;i++){
	cout<<answer[i]<<endl;
	
	 }
cout<<answer[i]<<endl;
	return 0;
}