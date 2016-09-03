#include<iostream>
using namespace std;
#define MAXOFCASES 500
#define MAXOFINSTANCES 100
//
//question structure:
class QuestionType{
public:
	QuestionType(){}
	int value;
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
	AnswerType(){
	num=0;}
	int num;
	int arr[MAXOFINSTANCES];
	int getBack(){
		return arr[num-1];
	}
	void push(int a){
		arr[num++]=a;
	}

private:
};
ostream &operator<<(ostream &out,AnswerType &t){
	out<<t.num<<endl;
	int i;
	for( i=0;i<t.num-1;i++){
		out<<t.arr[i]<<" ";
	}
	out<<t.arr[i];
	return out;
}
void swap(int a,int b){
	int t=a;
	a=b;
	b=t;
}
//
//the main function:
AnswerType getAnswer(QuestionType * lines,int size){
	AnswerType answer;
	int i,j;
	for(i=1;i<size;i++){
		QuestionType line=lines[i];
	}
	
	return answer;
}
//
//
int main()
{
	QuestionType questionCase;
	int caseCount=0;
	int numLines=0;
	//int test=0;
	while(1){
		cin>>numLines;
		if(numLines==0) break;
		//start.
		for(int j=0;j<numLines;j++){
			cin>>questionCase;
		}
		cout<<getAnswer(questionCase)<<endl;
		//end.
		caseCount++;
	}
	return 0;
}
