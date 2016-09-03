#include <cstdlib>
#include <iostream>

using namespace std;

#include "LargeInt.h"

#define Trace(m) cout<<#m"="<<(m)<<endl;
int main(int argc, char *argv[])
{
 LargeInt a(2),b=10;
	//cout<<a<<endl;
	a/=b;
	cout<<a<<endl;
	//a.print();b.print();
	a/=b;
//	a.print();b.print();
	
  /*  Trace(true^false);
    Trace(true^true);
    Trace(false^false);
    bool a,b;
    a=true;
    b=true;
    Trace(a^b);*/
    /*LargeInt a("4294967296"),b("65536");
    a.print();b.print();
    //a+=b;
    //a.print();b.print();
  
  
    //cout<<a<<endl;
    //a/=b;
    a.print();b.print();
    a/=655;
    a.print();
   cout<<a<<endl;*/
//    Trace(a);
    /*
    Trace(sizeof(unsigned short))
    Trace(int('+'));
    Trace(int('-'));
    //
    LargeInt a,b=2,c(b),d(3),f="123123";
    unsigned short sa,sb;
//    sa=0x
sa=65535;
sb=2;
Trace(sa);
Trace(sb);
sa+=sb;
Trace(sa);
Trace(sb);
sa=-1;
Trace(sa);
Trace(sb);
    //
   
    Trace(a=b);
    Trace(a+=b);
    Trace(a=a+b);
    Trace(a++);
    Trace((--a)++);
    Trace(++a);
    Trace(a--);
    Trace(a=2+b);
    Trace(a*=2);
    Trace(a=4*5);
    Trace(a=(int)54.0*d);
    Trace(a);
    Trace(b);
    Trace(b="123132");
    Trace(a=c+"0123");
    Trace(a="123"+b);
    Trace(a+="123132");
    Trace(a+="-123123");
    cout<<"input a:";cin>>a;
    Trace(a);*/
/**/
    system("PAUSE");
    return EXIT_SUCCESS;
}
