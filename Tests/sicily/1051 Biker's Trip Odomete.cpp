#include<iostream>
#include<iomanip>
#define PI 3.1415927
#define FEETINMILE 5280
#define INCHESINFOOT 12
#define METERSINFURLONG 201.168
using namespace std;
struct myType{
	float dist;
	float MPH;
};
#define MAXCASE 100
int main()
{
	float diameter;
	int revolu;
	float time;
	myType answer[MAXCASE];
	//
	int caseCount=0;
	while(1){
		cin>>diameter;
		cin>>revolu;
		cin>>time;
		if(revolu==0) break;
		//
		diameter/=INCHESINFOOT;
		diameter/=FEETINMILE;
		answer[caseCount].dist=PI*diameter*revolu;
		//cout<<"dist="<<answer[caseCount].dist<<endl;
		time/=3600;
		answer[caseCount].MPH=answer[caseCount].dist/time;
		//
		caseCount++;
	}
	cout<<setiosflags(ios::fixed);
	cout<<setprecision(2);
	for(int i=0;i<caseCount;i++){
		cout<<"Trip #"<<(i+1)<<": "<<answer[i].dist<<" "<<answer[i].MPH<<endl;
	}
	return 0;
}