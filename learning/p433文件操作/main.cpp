#include<fstream.h>
#include"student.h" 
#include"master.h"
int main(){
	ofstream out("e:\\bctemp\\abc.txt");
	Student s1("Dill Arnson",12567,3.5);
	MasterStudent s2("Welch shammas",12579,4.1f,'A');
	MasterStudent s3("pORTEL bRAUMBEL",12579,3.8f,'B');

	out<<s1;
	out<<s2;
	out<<s3;
	return 0;
}