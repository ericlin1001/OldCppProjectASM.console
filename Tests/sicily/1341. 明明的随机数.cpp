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
		j=i-1;
		while(j>=0 && line.value<lines[j].value){
			lines[j+1].value=lines[j].value;
			j--;
		}
		lines[j+1].value=line.value;
	}
	//j=0;
	answer.push(lines[0].value);
	for(i=1;i<size;i++){
		if(lines[i].value!=answer.getBack()){
			answer.push(lines[i].value);
		}
	}
	return answer;
}
//
//
int main()
{
	AnswerType answer[MAXOFCASES];
	//
	QuestionType lines[MAXOFINSTANCES];
	int caseCount=0;
	int numLines=0;
	//int test=0;
	while(1){
		//if(++test==3)break;
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
	for( i=0;i<caseCount;i++){
		cout<<answer[i]<<endl;
		
	}
	return 0;
}
