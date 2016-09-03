#include<iostream>
using namespace std;
#define MAXOFCASES 500
#define MAXOFINSTANCES 100000
//
//question structure:
class QuestionType{
public:
	QuestionType(){}
	int a;
	int b;
	void tt(){
		if(a>b){
			int c=a-1;
			a=b-1;
			b=c;
		}else{
		a--;
		b--;
		}
	}
};

//
//answer structure:
//
//the main function:
int temp[MAXOFINSTANCES*2];
bool getAnswer(QuestionType * lines,int size){
	bool answer;
	int i,j;
	int numtemp=size*2;
	int p=1;
	answer=true;
	for(i=0;i<size;i++){
		QuestionType &line=lines[i];
		j=line.a+1;
		while(j<line.b){
			 if(temp[j]==0){
				j++;
			}else if(temp[j]==-1){
				answer=false;
				i=size;
				j=line.b+1;
				break ;
			} else{
				j=temp[j]+1;
			}
		}
		if(j>line.b){
			answer=false;
			break;
		}
		temp[line.a]=line.b;
		temp[line.b]=-1;
	}
	return answer;
}
//
//
int main()
{
	bool answer[MAXOFCASES];
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
			cin>>lines[j].a>>lines[j].b;
			lines[j].tt();
		}
		answer[caseCount]=getAnswer(lines,numLines);
		//end.
		caseCount++;
	}
	int i;
	for( i=0;i<caseCount;i++){
		if(answer[i])cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
	return 0;
}
