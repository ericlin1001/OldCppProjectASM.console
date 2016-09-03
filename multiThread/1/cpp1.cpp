/*#include<windows.h>
#include<process.h>
#include<stddef.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<iostream.h>

  #define GetRandom(min,max) ((rand()%(int)(((max)+1)-(min)))+(min))
  BOOL repeat=TRUE;
  HANDLE hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  void CheckKey(void *dummy);
  void Bounce(void *ch);
  void main(){
  CHAR ch='A';
  hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
  GetConsoleScreenBufferInfo(hStdOut,&csbi);
  _beginthread(CheckKey,0,NULL);//startadress,stack_size,arglist
  while(repeat){
		_beginthread(Bounce,0,(void*)(ch++));
		Sleep(1000L);
		}
		}
		void CheckKey(void *dummy)
		{
		_getch();
		cout<<"exiting"<<endl;
		repeat=0;
		}
		void Bounce(void *ch){
		char blankcell=0x20;
		char blockcell=(char)ch;
		BOOL first =TRUE;
		COORD oldcoord,newcoord;
		DWORD result;
		srand((unsigned )time(NULL));
		newcoord.X=GetRandom(0,csbi.dwSize.X-1);
		newcoord.Y=GetRandom(0,csbi.dwSize.Y-1);
		while(repeat){
		Sleep(100L);
		if(first) first =FALSE;
		else
		WriteConsoleOutputCharacter(hStdOut,&blockcell,1,oldcoord,&result);
		oldcoord.X=newcoord.X;
		oldcoord.Y=newcoord.Y;
		newcoord.X+=GetRandom(-1,1);
		newcoord.Y+=GetRandom(-1,1);
		if(newcoord.X<0) newcoord.X=1;
		else if (newcoord.X==csbi.dwSize.X) newcoord.X=csbi.dwSize.X-2;
		else if (newcoord.Y<0) newcoord.Y=1;
		else if (newcoord.Y==csbi.dwSize.Y) newcoord.Y=csbi.dwSize.Y-2;
		else continue;
		Beep(((char)ch-'A')*100,175);
		}
		_endthread();
		}
*/
/*#include<iostream>  
#include<iomanip>   
#include<windows.h>   
using namespace std;   
void Draw(HANDLE hand,int colour,char *s,int len,COORD point,LPDWORD lPdword);   
int main()   
{   
int x=4;   
int y=4;   
HANDLE hand;   
hand=GetStdHandle(STD_OUTPUT_HANDLE);   
int colour=200;   
int len=2;   
COORD point = {x,y};   
SMALL_RECT rt = {0,0,35,32}; // 窗口尺寸   
SetConsoleWindowInfo(hand,true,&rt); // 由于DOS默认只有25行，为了便于观察，把dos窗口行数调为35，这个也可以用system函数实现   
char *string="■";   
Draw(hand,colour,string,len,point,NULL);   
INPUT_RECORD keyRec;   
DWORD res;   
HANDLE hnd;   
hnd=GetStdHandle(STD_INPUT_HANDLE);   
for(;;)   
{   
cout<<setfill('0')<<"("<<setw(2)<<point.X<<","<<setw(2)<<point.Y<<")";   
ReadConsoleInput(hnd,&keyRec,1,&res);   
if(keyRec.EventType==KEY_EVENT)   
{   
if(keyRec.Event.KeyEvent.wVirtualKeyCode==65)   
{   
if(point.X>1) // 这里不用那么麻烦，因为按a时只会使X减小，下同   
{   
Draw(hand,1," ",len,point,NULL);   
point.X-=1;   
Draw(hand,colour,string,len,point,NULL);   
}   
}   if(keyRec.Event.KeyEvent.wVirtualKeyCode==68)   
{   
if(point.X<30)   
{   
Draw(hand,1," ",len,point,NULL);   
point.X+=1;   
Draw(hand,colour,string,len,point,NULL);   
}   
}   
if(keyRec.Event.KeyEvent.wVirtualKeyCode==87)   
{   
if(point.Y>1)   
{   
Draw(hand,1," ",len,point,NULL);   
point.Y-=1;   
Draw(hand,colour,string,len,point,NULL);   
}   
}   
if(keyRec.Event.KeyEvent.wVirtualKeyCode==83)   
{   if(point.Y<30)   
{   
Draw(hand,1," ",len,point,NULL);
   
point.Y+=1;   
Draw(hand,colour,string,len,point,NULL);   
 }   
 }   
 }   
 cout<<"\b\b\b\b\b\b\b";   
 }   
 }   
 void Draw(HANDLE hand,int colour,char *s,int len,COORD point,LPDWORD lPdword)
 {   
 FillConsoleOutputAttribute(hand,colour,len,point,lPdword);   
 WriteConsoleOutputCharacter(hand,s,len,point,lPdword);   
 }
 */

#include<process.h>
#include<stddef.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
HANDLE hOut;
bool repeat;
CONSOLE_SCREEN_BUFFER_INFO csinfo;
void checkExit(void *t){
	if(_getch()=='q'){
		repeat=false;
		_endthread();
	}
}
void moveChar(void *ch){
Sleep(100L);
system("dir");
}
int main(){
	repeat=true;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOut,&csinfo);
	COORD oldCurPos={0,0};
//	DWORD result;
//	WriteConsoleOutputCharacter(hOut,"Aasdfadfasdf",5,pos,&result);
	_beginthread(checkExit,0,NULL);
	char ch='A';
	system("dir");
	while(repeat){
		Sleep(1000L);
		int x=csinfo.dwCursorPosition.X;
		int y=csinfo.dwCursorPosition.Y;
		if(x==oldCurPos.X && y==oldCurPos.Y){
		}else{
			oldCurPos.X=x;
			oldCurPos.Y=y;
			_beginthread(moveChar,0,(void *)(ch++));
		}
	}
	return 0;
}