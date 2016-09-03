#include "List.h"
#include<string.h>
#include<iostream.h>
void List::push(char * str){
	Node * node=new Node();
	node->value=new char[strlen(str)+1];
	strcpy(node->value,str);
	node->next=NULL;
	if(head==NULL){
		head=tail=node;
	}else{
		tail->next=node;
		tail=node;
	}
	len++;
}
void List::push(char ch){
	char *temp=new char[2];
	*temp=ch;
	*(temp+1)='\0';
	push(temp);
}
char * List::del(int i){
	if(isEmpty()){
		cerr<<"Error:has not element"<<endl;
		return "0";
	}
	char *temp;
	if(i==0)
	{
		temp=head->value;
		head=head->next;
		len--;
		return temp;
	}
	setpSearch(i-1);
	temp=new char[strlen(pSearch->next->value)+1];
	strcpy(temp,pSearch->next->value);
	pSearch->next=pSearch->next->next;
	len--;
	return temp;

}
char * List::get(int i){
	setpSearch(i);
	if(pSearch==NULL){
		cerr<<"you are getting element out of range."<<endl;
		return (char*)0;
	}
	return pSearch->value;
}
void List::set(int i,char *str){
	int myLen=strlen(str);
	char *temp=new char[myLen+1];
	strcpy(temp,str);
	//
	setpSearch(i);
	delete pSearch->value;//easy mistake, when delete the element is what is setting
	//
//	cout<<"mylen="<<myLen<<endl;
//	cout<<"you are setting element("<<i<<")="<<str<<endl;
	//
	pSearch->value=new char[myLen+1];
	strcpy(pSearch->value,temp);
//	*(pSearch->value+myLen)='\0';
	
	return ;
}
void List::print(){
	cout<<"now the list is:"<<endl;
	for(pSearch=head;pSearch!=tail->next;pSearch=pSearch->next){
		cout<<pSearch->value<<" , ";
	}
	cout<<endl;
}
void List::setpSearch(int i){
	pSearch=head;
	while(i>0){
		i--;
		pSearch=pSearch->next;
	}
}
void List::next(){
	pSearch=pSearch->next;
}
void List::fromBegin(){
	pSearch=head;
}
char * List::get(){
	return pSearch->value;
}
	