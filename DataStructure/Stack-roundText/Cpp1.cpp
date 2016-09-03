#include<iostream>
#include<stack>
#include<string>
using namespace std;
bool isRoundText(char *pstr)
{
	string str;
	stack<char> text;
	int i=0;
	while(*(pstr+i)) text.push(*(pstr+i++));
	while(*pstr && text.top()==*pstr++) {text.pop();	i--;}
	return i==0;
}
int main()
{
	char buffer[100];
	while(1){
	cin>>buffer;
	if(isRoundText(buffer)){
		cout<<buffer<<" is round text."<<endl;
	}else{
		cout<<buffer<<" isn't round text."<<endl;
	}
	cout<<endl;
	}
	return 0;
}