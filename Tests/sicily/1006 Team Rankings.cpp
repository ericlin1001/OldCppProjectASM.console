#include<iostream>
#include<cstring>
using namespace std;
#define MAXOFCASES 10000
#define MAXOFINSTANCES 100
void printInt(char *a){
	for(int i=0;i<5;i++){
		cout<<(char)((int)a[i]+0x30)<<",";
	}
	cout<<endl;
}
//
//question structure:
class QuestionType{
public:
	QuestionType(){
	}
	void strChangeToNum(){
		for(int i=0;i<5;i++){
			rank[i]-=0x41;
		}
		
	}
	char rank[6];
private:
};
istream &operator>>(istream &in,QuestionType &t){
	in>>t.rank;
	return in;
}
//
//answer structure:
class AnswerType{
public:
	AnswerType(){
		suit=0;
	}
	void numChangeToStr(){
		for(int i=0;i<5;i++){
			rank[i]+=0x41;
		}
		rank[5]='\0';
	}
	char rank[6];
	int suit;
	int value;
private:
};
ostream &operator<<(ostream &out,AnswerType &t){
	out<<t.rank;
	return out;
}
//
//quxiliary function:
void swap(char &a,char &b){
	char t=a;
	a=b;
	b=t;
}
int calSuit(int pairs[][5],char *rank){
	int a=0;
	for(int i=0;i<5;i++){
		for(int j=i+1;j<5;j++){
			a+=pairs[rank[i]][rank[j]];
		}
	}
	return a;
}
//
//the main function:
AnswerType getAnswer(QuestionType * lines,int size){
	//declare:
	AnswerType answer;
	int pairs[5][5];//count the num each pair(ab,ac,ad,af,bc...),the max is size
	int i,j,pLine;
	//init.
	for( i=0;i<size;i++){
		lines[i].strChangeToNum();
	}
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			pairs[i][j]=0;
		}
	}
	//start.
	for(pLine=0;pLine<size;pLine++){
		for(i=0;i<5;i++){
			for(j=i+1;j<5;j++){
				char rank[5];
				memcpy(rank,lines[pLine].rank,5);
				pairs[rank[i]][rank[j]]++;
			}
		}
	}
	/*cout<<"pairs:"<<endl;
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			cout<<pairs[i][j]<<",";
		}
		cout<<endl;
	}*/
	/*cout<<"lines:"<<endl;
	for(pLine=0;pLine<size;pLine++){
		printInt(lines[pLine].rank);
		cout<<endl;
	}*/

	//creating abcdef seq.
	char temp[5];
	for(i=0;i<5;i++){
		temp[i]=i;
	}
	for(i=0;i<5;i++){
		swap(temp[4],temp[i]);
		for(j=0;j<4;j++){
			swap(temp[3],temp[j]);
			for(int k=0;k<3;k++){
				swap(temp[2],temp[k]);
				for(int l=0;l<2;l++){
					swap(temp[1],temp[l]);
					swap(temp[1],temp[0]);
					//the permutation:
					int suit=calSuit(pairs,temp);
					if(suit>answer.suit||(suit==answer.suit && strcmp(answer.rank,temp)>0)){
					//	cout<<"temp:";
					//	printInt(temp);
						memcpy(answer.rank,temp,5);
						answer.suit=suit;
					//	cout<<"answer:";
					//	printInt(answer.rank);
					//	cout<<"suit:"<<suit<<endl<<endl;

					}
					//printInt(temp);//test:
					//end
					swap(temp[1],temp[0]);
					swap(temp[1],temp[l]);
				}
				swap(temp[2],temp[k]);
			}
			swap(temp[3],temp[j]);
		}
		swap(temp[4],temp[i]);
	}
	//end
	answer.numChangeToStr();
	answer.value=size*10-answer.suit;
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
	while(1){
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
		cout<<answer[i].rank<<" is the median ranking with value "<<answer[i].value<<".\n";
		//cout<<"answer["<<i<<"]="<<answer[i]<<"."<<endl;
		
	}
	cout<<answer[i].rank<<" is the median ranking with value "<<answer[i].value<<".\n";
	return 0;
}