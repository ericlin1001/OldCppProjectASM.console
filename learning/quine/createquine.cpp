#include<iostream.h>
char *substr(char *str,int begin,int end){
	char *tempstr=new char[end-begin+1];
	str+=begin;
	end-=begin;
	begin=end;
	while((end--)) *tempstr++=*str++;
	*tempstr=0;
	tempstr-=begin;
	return tempstr;
}
int main(){
	char fu[10]="\"\n\t;\\nt";
	char str[300]="#include<iostream.h>char *substr(char *str,int begin,int end){char *tempstr=new char[end-begin+1];str+=begin;end-=begin;begin=end;while((end--)) *tempstr++=*str++;*tempstr=0;tempstr-=begin;return tempstr;}int main(){char fu[10]=char str[300]=return 0;}char strcout[1000]=";
	char strcout[1000]="cout<<substr(str,0,20)<<fu[1]<<substr(str,20,62)<<fu[1]<<fu[2]<<substr(str,62,98)<<fu[1]<<fu[2]<<substr(str,98,109)<<fu[1]<<fu[2]<<substr(str,109,120)<<fu[1]<<fu[2]<<substr(str,120,130)<<fu[1]<<fu[2]<<substr(str,130,163)<<fu[1]<<fu[2]<<substr(str,163,174)<<fu[1]<<fu[2]<<substr(str,174,189)<<fu[1]<<fu[2]<<substr(str,189,204)<<fu[1]<<str[204]<<fu[1]<<substr(str,205,216)<<fu[1]<<fu[2]<<substr(str,216,228)<<fu[0]<<fu[4]<<fu[0]<<fu[4]<<fu[5]<<fu[4]<<fu[6]<<fu[3]<<fu[4]<<fu[4]<<fu[5]<<fu[6]<<fu[0]<<fu[3]<<fu[1]<<fu[2]<<substr(str,228,242)<<fu[0]<<str<<fu[0]<<fu[3]<<fu[1]<<fu[2]<<substr(str,252,271)<<fu[0]<<strcout<<fu[0]<<fu[3]<<fu[1]<<fu[2]<<strcout<<fu[1]<<fu[2]<<substr(str,242,251)<<fu[1]<<str[204]<<fu[1];";
	cout<<substr(str,0,20)<<fu[1]<<substr(str,20,62)<<fu[1]<<fu[2]<<substr(str,62,98)<<fu[1]<<fu[2]<<substr(str,98,109)<<fu[1]<<fu[2]<<substr(str,109,120)<<fu[1]<<fu[2]<<substr(str,120,130)<<fu[1]<<fu[2]<<substr(str,130,163)<<fu[1]<<fu[2]<<substr(str,163,174)<<fu[1]<<fu[2]<<substr(str,174,189)<<fu[1]<<fu[2]<<substr(str,189,204)<<fu[1]<<str[204]<<fu[1]<<substr(str,205,216)<<fu[1]<<fu[2]<<substr(str,216,228)<<fu[0]<<fu[4]<<fu[0]<<fu[4]<<fu[5]<<fu[4]<<fu[6]<<fu[3]<<fu[4]<<fu[4]<<fu[5]<<fu[6]<<fu[0]<<fu[3]<<fu[1]<<fu[2]<<substr(str,228,242)<<fu[0]<<str<<fu[0]<<fu[3]<<fu[1]<<fu[2]<<substr(str,252,271)<<fu[0]<<strcout<<fu[0]<<fu[3]<<fu[1]<<fu[2]<<strcout<<fu[1]<<fu[2]<<substr(str,242,251)<<fu[1]<<str[204]<<fu[1];
	return 0;
}
