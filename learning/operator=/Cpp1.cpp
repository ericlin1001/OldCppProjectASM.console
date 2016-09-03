#include<iostream.h>
#include<string.h>
class Name{
	
public:
	Name(char *str){
		pName=new char[strlen(str)+1];
		strcpy(pName,str);
	}
	~Name(){
		delete pName;
		cout<<"pName="<<(int)pName<<endl;

	}
	void display(){
		cout<<pName<<endl;
	}
	Name& operator=(Name &n){
		if(pName){
			delete pName;
		}
		pName=new char[strlen(n.pName)+1];
		strcpy(pName,n.pName);
		return *this;
	}/**/
protected:
	void deleteName(){
	}
	char *pName;


};
int main(){
	Name s("claudette");
	Name t("temporary");
	t.display();
	t=s;
	t.display();
	return 0;
}
