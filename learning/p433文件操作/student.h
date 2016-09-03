#include<iostream.h>
#include<string.h>
#ifndef STUDENT
#define STUDENT
class Student{
public:
	Student(char *pS,unsigned num,float g){
		strcpy(pName,pS);
		uID=num;
		grade=g;
	}
	virtual void display(ostream& out);
protected:
	char pName[20];
	unsigned int uID;
	float grade;
};
ostream & operator<<(ostream& out,Student&st);
#endif
