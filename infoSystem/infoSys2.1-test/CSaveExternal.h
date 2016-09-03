//if you want to save as external ,please #define __saveExternal__
#ifndef CSAVEEXTERNAL_H
#define CSAVEEXTERNAL_H
#ifdef __saveExternal__//determin whether include serialIn,serialOut
#include<fstream>
using namespace std;
typedef unsigned short StrLen;
#define serial(m) (char *)&m,sizeof(m)
#endif

class CSaveExternal{
public:
	~CSaveExternal(){
	}
	CSaveExternal(){
	}
protected:
	/**/
	#ifdef __saveExternal__
	//
	bool  serizlIn(ifstream &infile){return false;}
	bool  serizlOut(ofstream &outfile){return false;}
	void writeStr(char *str,ofstream &outfile){
		StrLen len=strlen(str);
		len++;
		outfile.write(serial(len));
		outfile.write(str,len);
	}
	//
	#endif
};
#endif