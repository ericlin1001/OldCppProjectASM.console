
#ifndef CLINKEDLIST_H
#define CLINKEDLIST_H
#include "CSaveExternal.h"
//for test
#ifdef __test__
#include<iostream>
using namespace std;
#define TestTrace(mess)  cout<<mess;
#else
#define TestTrace(mess)  
#endif
//end test
#ifndef NULL
#define NULL 0
#endif


template<class MyType> class CLinkedList{
protected:
	struct Node{
		MyType value;
		Node *next;
	};
private:
	Node *head;//the head but store nothing,just a pointer.
	Node *pcur;
	Node *tail;
	Node *iter;
	int curindex;
	int num;
	bool setPcur(int index){
		if(index==num-1){
			pcur=tail;
			curindex=index;
			return true;
		}
		pcur=head;
		if(-1<=index && index<num){//-1 represent the head.
			for(int i=-1;i<index;i++)pcur=pcur->next;
			curindex=index;
			return true;
		}
		return false;
}
	bool isInRange(int index){
		return -1<=index && index<num;
}
public:
	//for iteration:
	void begin(MyType &p){
		iter=head->next;
		if(iter!=NULL){
			p=iter->value;
		}
	};
	void next(MyType &p){
		iter=iter->next;
		if(iter!=NULL){
			p=iter->value;
		}
	}
	bool end(){
		return iter==NULL;
	}
	//
	
	CLinkedList(){
		
		num=0;
		head=new Node();
		head->next=NULL;
		pcur=head;
		tail=head;
		curindex=0;
}
	~CLinkedList(){
		while(num!=0)del(num-1);
		delete head;
}
	bool interchange(int indexa,int indexb){
		if(isInRange(indexa) && isInRange(indexb)){
			MyType value=get(indexa);
			return set(indexa,get(indexb)) && set(indexb,value);
		}
		return false;
	}
	int getNum(){return num;}
	bool set(int index,MyType value){
		if(setPcur(index)){
			pcur->value=value;
			return true;
		}
		return false;
	}
	MyType get(int index){
		if(curindex==index)return pcur->value;
		if(setPcur(index))return pcur->value;
		return (MyType)NULL;
	}
	bool insert(MyType value,int index){//index represent the inserted type.
		if(index<0 || index>num)return false;
		setPcur(index-1);
		Node *newNode=new Node();
		newNode->value=value;
		newNode->next=pcur->next;
		pcur->next=newNode;
		//
		if(tail->next==newNode)tail=newNode;
		num++;
		return true;
	}
	bool add(MyType value);
	void print(){
		for(int i=0;i<num;i++){
			TestTrace(get(i)<<',');
		}
		TestTrace(endl);
	}
	bool del(int index){
		if(num<=0)return false;
		if(index<0 || index>=num) return false;
		setPcur(index-1);
		Node *delNode=pcur->next;
		pcur->next=delNode->next;
		if(delNode==tail)tail=pcur;
		delete delNode;
		num--;
		return true;
}
};

/*
template<class MyType> class CLinkedList{
protected:
	struct Node{
		MyType value;
		Node *next;
	};
private:
	Node *head;//the head but store nothing,just a pointer.
	Node *pcur;
	Node *tail;
	Node *iter;
	int num;
	bool setPcur(int index);
	bool isInRange(int index);
public:
	//for iteration:
	void begin(MyType &p){
		iter=head->next;
		if(iter!=NULL){
			p=iter->value;
		}
	};
	void next(MyType &p){
		iter=iter->next;
		if(iter!=NULL){
			p=iter->value;
		}
	}
	bool end(){
		return iter==NULL;
	}
	//
	~CLinkedList();
	CLinkedList();
	bool interchange(int indexa,int indexb);
	int getNum();
	bool set(int index,MyType value);
	MyType get(int index);
	bool insert(MyType value,int index);
	bool add(MyType value);
	void print();
	bool del(int index);
};
template<class MyType>
bool CLinkedList<MyType>::setPcur(int index){
		if(index==num-1){
			pcur=tail;
			return true;
		}
		pcur=head;
		if(-1<=index && index<num){//-1 represent the head.
			for(int i=-1;i<index;i++)pcur=pcur->next;
			return true;
		}
		return false;
}
template<class MyType>
bool CLinkedList<MyType>::isInRange(int index){
		return -1<=index && index<num;
}

template<class MyType>
CLinkedList<MyType>::CLinkedList(){
		num=0;
		head=new Node();
		head->next=NULL;
		pcur=head;
		tail=head;
}

template<class MyType> 
bool CLinkedList<MyType>::interchange(int indexa,int indexb){
		if(isInRange(indexa) && isInRange(indexb)){
			MyType value=get(indexa);
			return set(indexa,get(indexb)) && set(indexb,value);
		}
		return false;
	}
template<class MyType> 
int CLinkedList<MyType>::getNum(){
		return num;
	}
template<class MyType> 
bool CLinkedList<MyType>:: set(int index,MyType value){
		if(setPcur(index)){
			pcur->value=value;
			return true;
		}
		return false;
	}
template<class MyType> 
MyType CLinkedList<MyType>::get(int index){
		if(setPcur(index))return pcur->value;
		return (MyType)NULL;
}
	
template<class MyType> 
bool CLinkedList<MyType>::insert(MyType value,int index){//index represent the inserted type.
		if(index<0 || index>num)return false;
		setPcur(index-1);
		Node *newNode=new Node();
		newNode->value=value;
		newNode->next=pcur->next;
		pcur->next=newNode;
		//
		if(tail->next==newNode)tail=newNode;
		num++;
		return true;
	}
template<class MyType> 
bool CLinkedList<MyType>::add(MyType value){//index represent the inserted type.
		return insert(value,num);
	}
template<class MyType> 
void CLinkedList<MyType>::print(){
		for(int i=0;i<num;i++){
			TestTrace(get(i)<<',');
		}
		TestTrace(endl);
	}
template<class MyType> 
bool CLinkedList<MyType>::del(int index){
		if(num<=0)return false;
		if(index<0 || index>=num) return false;
		setPcur(index-1);
		Node *delNode=pcur->next;
		pcur->next=delNode->next;
		if(delNode==tail)tail=pcur;
		delete delNode;
		num--;
		return true;
}
template<class MyType>  CLinkedList<MyType>::~CLinkedList(){
		while(num!=0)del(num-1);
		delete head;
}*/
#endif
//for test LinkedList

/*
#ifndef TestFun
#define TestFun(FUN) cout<<"After "<<#FUN<<":"<<FUN<<endl;
#endif
  CLinkedList<int> list;
	list.add(1);list.add(5);list.add(90);list.add(1);list.add(5);list.add(90);
	list.print();
	TestFun(list.del(1))
	list.print();
	TestFun(list.insert(20,2))
	list.print();
	*/