

#include<iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>
using namespace std;
#define SOCKET unsigned int
//
#include "../definedMess.h"
#define Trace(m) cout<<#m"="<<m<<endl;
//

/**/
bool copyFile(const char *srcfile,const char *destfile){
	ifstream infile;
	infile.open(srcfile,ios::in|ios::binary);
	if(infile.fail())return false;
	ofstream outfile;
	outfile.open(destfile,ios::binary);
	if(outfile.fail())return false;
	while(1){char ch=infile.get();if(infile.eof())break;outfile.put(ch);}
	infile.close();
	outfile.close();
	return true;
}
int count;
#define Tag cout<<"count:"<<count++<<endl;

#define PATH_USER_DATA "..\\Server\\"FILE_USER_DATA
bool registerUser(char *name,char *user,char *pass,int age){ 
	CClientInfo ci;
	strcpy(ci.name,name);
	strcpy(ci.user,user);
	strcpy(ci.pass,pass);
	ci.age=age;
	ofstream file;
	if(!openFile(file,PATH_USER_DATA)){
		cout<<"open "PATH_USER_DATA" fail!"<<endl;
		return false;
	}
	//file.seekp(0,ios::beg);
	ci.save(file);
	file.close();
	return true;
}
bool modifyUser(int index,char *name,char *user,char *pass,int age){ 
	CClientInfo ci;
	strcpy(ci.name,name);
	strcpy(ci.user,user);
	strcpy(ci.pass,pass);
	ci.age=age;
	ofstream file;
	if(!openFile(file,PATH_USER_DATA)){
		cout<<"open "PATH_USER_DATA" fail!"<<endl;
		return false;
	}
	file.seekp(index*ci.saveSize(),ios::beg);
	ci.save(file);
	file.close();
	return true;
}
bool showAll(){
	CClientInfo ci;
	ifstream file;
	file.open(PATH_USER_DATA);
	if(file.fail()){
		cout<<"open "PATH_USER_DATA" fail!"<<endl;
		return false;
	}
	int row=0;
	while(1){
		ci.read(file);
		if(file.eof())break;
		cout<<row++<<" :";
		ci.print();
		}
	file.close();
	return true;
}
void help(){
	cout<<"order:""r,s,m"<<endl;
}
int main(){
	ofstream file;
	//file.open("abc.txt",ios::binary);
	
	char str[30]="01234567890123456789";
	//012342
	//

	//
	if(!openFile(file,"test.txt")){
		cout<<"fail"<<endl;return 0;
	}
	file.seekp(-2,ios::end);
	file.write(str,10);

	file.seekp(-2,ios::end);
		Trace(file.tellp());
	file.write(str+2,3);
		Trace(file.tellp());
		file.close();
	//
	char name[20];char user[20];char pass[20];int age;
	char order[20];
	while(1){
		cout<<"order:";cin>>order;
		if(strcmp(order,"r")==0){
			cout<<"name:";cin>>name;
			cout<<"user:";cin>>user;
			cout<<"pass:";cin>>pass;
			cout<<"age:";cin>>age;
			if(registerUser(name,user,pass,age)){
				cout<<"register success!"<<endl;
			}else{
				cout<<"fail!"<<endl;
			}
		}else if(strcmp(order,"s")==0){
			showAll();
		}else if(strcmp(order,"help")==0){
			help();
		}else if(strcmp(order,"m")==0){
			int index;
			cout<<"index:";cin>>index;
			cout<<"name:";cin>>name;
			cout<<"user:";cin>>user;
			cout<<"pass:";cin>>pass;
			cout<<"age:";cin>>age;
			if(modifyUser(index,name,user,pass,age)){
				cout<<"modity success!"<<endl;
			}else{
				cout<<"fail!"<<endl;
			}
		}else if(strcmp(order,"r")==0){
		}else {
			cout<<"no this order."<<endl;
		}
	}
	return 0;
}

