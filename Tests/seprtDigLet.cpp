#include<iostream>
using namespace std;
char *seprtDigLet(char *str){
#define is_letter(ch) (('a'<=(ch) && (ch)<='z')||('A'<=(ch) && (ch)<='Z'))
	char *p=str+1;
	while(*p){
		if('0'<=*p && *p<='9'){
			char *p2=p;
			while(str<p2 && is_letter(*(p2-1))){
				*(p2-1)^=*p2^=*(p2-1)^=*p2;
				p2--;
			}
		}
		p++;
	}
	return str;
}
void out(char *str){
	while(*str)cout.put(*str++);
	cout.flush();
}
int main(){
	char buffer[100];
	while(1){
		cin>>buffer;
		if(buffer[0]=='#')break;
		out(seprtDigLet(buffer));
		//cout<<seprtDigLet(buffer)<<endl;
	}
	return 0;
}
