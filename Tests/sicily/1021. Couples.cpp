#include<iostream>
using namespace std;
#define MAXOFCASES 500
#define MAXOFINSTANCES 100000
//
//question structure:
class QuestionType{
public:
	QuestionType(){}
	int couple[2];
private:
};
istream &operator>>(istream &in,QuestionType &t){
	in>>t.couple[0]>>t.couple[1];
	return in;
}
//
//answer structure:
class AnswerType{
public:
	AnswerType(){
	}
	bool value;
private:
};
ostream &operator<<(ostream &out,AnswerType &t){
	if(t.value){
		out<<"Yes";
	}else{
		out<<"No";
	}
	return out;
}
typedef struct Node{
	int n;
	Node(int n){
		this->n=n;
	}
	Node *next;
}CNode,* pNode;
class LinkedList{
public:
	pNode head;
	pNode tail;
	int num;
	LinkedList(){
		//head=new Node();
		head=tail=NULL;
		num=0;
	}
	LinkedList(int *arr,int size){
		num=size;
		tail=head=new Node(arr[0]);
		for(int i=1;i<size;i++){
			tail->next=new Node(arr[i]);
			tail=tail->next;
		}
		tail->next=head;
	}
	void add(int n){
		pNode t=new Node(n);
		if(head==NULL){
			head=t;
			head->next=head;
			tail=head;
		}else{
			tail->next=t;
			t->next=head;
			tail=t;
		}
		num++;
	//	cout<<"add num:"<<num<<" "<<n<<endl;
		print();
	}
	void error(){
		if(num<0){
	//		cout<<"error"<<endl;
		}
	}
	bool delCouples(){
		int i;
		int len=num/2;
		for(i=0;i<len-1;i++){
			if(!delOneCouple()) break;
			print();
		}
		if(num>2) return false;
		if(num==2){
			return true;
		}
		cout<<"error:num<2"<<endl;
		return false;
	}
	void print(){
	/*	cout<<"list("<<num<<"):";
		pNode pi;
		for(pi=head;pi!=tail;pi=pi->next){
			cout<<pi->n<<",";
		}
		cout<<pi->n<<",";
		cout<<endl;*/
	}
	bool delOneCouple(){
	//	if(num<=2) {cout<<"num<=2"<<endl;return false;}
		pNode pGuard=NULL;
		pNode pi;
		pi=head;
		for(pi=head;pi!=tail;pGuard=pi,pi=pi->next){
			if(pi->n==pi->next->n){
				break;
			}
		}
		if(pi->n==pi->next->n){
				//break;
		}else{
		pGuard=pi,pi=pi->next;
		}
		if(pi==head && pGuard!=NULL){
			return false;
		}else{
			pNode a,b;
			if(pGuard==NULL){
				 a=head; 
				 b=head->next;
				head=b->next;
				tail->next=head;
				delete a;
				delete b;
			}else{
				 a=pi; b=pi->next;
				 head=b->next;
				pGuard->next=b->next;
				tail=pGuard;
				delete a;
				delete b;
			}
			num-=2;
		//	error();
			return true;
		}
	}

};

//
//the main function:
AnswerType getAnswer(QuestionType * lines,int size){
	AnswerType answer;
	int i;
	int numtemp=size*2;
	
	int *temp=new int[numtemp];
	for(i=0;i<size;i++){
		QuestionType line=lines[i];
		temp[line.couple[0]-1]=temp[line.couple[1]-1]=i;
	}
	LinkedList list(temp,numtemp);
	/*for(i=0;i<numtemp;i++){
		list.add(temp[i]);
	}*/
	answer.value=list.delCouples();

	//
	
	//
	delete temp;
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
