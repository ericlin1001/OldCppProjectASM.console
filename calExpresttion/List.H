#include<iostream.h>
struct Node
{
	char *value;
	Node *next;
};
class List{
public :
	List(){
		head=tail=NULL;
		len=0;
	}
	void next();
	void fromBegin();
	void push(char * str);
	void push(char ch);
	int getLength(){return len;}
protected:
	void setpSearch(int i);
protected:
	Node * head;
	int len;
	Node * pSearch;
	Node * tail;
public:
	char * del(int i);
	char *get(int i);
	char *get();
	void set(int i,char *str);
	bool isEmpty(){return (len==0);}
	void print();
};
