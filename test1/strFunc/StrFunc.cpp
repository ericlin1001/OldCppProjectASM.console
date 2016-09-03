#include"StrFunc.h"
istream& getLine(istream&in,string &str,char delim){
	char ch;ostringstream out;
	while((ch=in.get())!=delim)out<<ch;
	str=out.str();
	return in;
}
