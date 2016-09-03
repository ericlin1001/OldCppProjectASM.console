#include<iostream>
#include<cstring>
using namespace std;
#define MAXOFCASES 500
#define MAXOFINSTANCES 80
//
//question structure:
class QuestionType{
public:
	QuestionType(){}
	int deleteNum;
	char value[MAXOFINSTANCES];
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
	AnswerType(){}
	char value[MAXOFINSTANCES];
private:
};
ostream &operator<<(ostream &out,AnswerType &t){
	out<<t.value;
	return out;
}
//
//the main function:
AnswerType getAnswer(QuestionType line){
	AnswerType answer;
	int j=0;
	for(int i=0;i<strlen(line.value);i++){
		if(i!=line.deleteNum-1){
			answer.value[j]=line.value[i];
			j++;
		}
	}
	answer.value[j]='\0';
	return answer;
}
//
//
int main()
{
	AnswerType answer[MAXOFCASES];
	//
	QuestionType lines;

	int numLines=0;
	//while(1){
		cin>>numLines;
	//	if(numLines==0) break;
		//start.
		for(int j=0;j<numLines;j++){
			cin>>lines.deleteNum>>lines.value;
			answer[j]=getAnswer(lines);
		}
		
	
//	}
	int i;
	for( i=0;i<numLines;i++){
		cout<<i+1<<" "<<answer[i]<<endl;
		
	}
	return 0;
}
