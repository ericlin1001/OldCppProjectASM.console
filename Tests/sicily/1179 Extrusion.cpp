#include<iostream>
#include<iomanip>
#define MAXCASELEN 5000
#define MAXPOINTS 2000
using namespace std;
struct Point{
	float x;
	float y;
	void print(){
		//cout<<"("<<x<<","<<y<<")"<<endl;
	}
};
float getTriArea(Point a,Point b,Point c)
{
	float area=0;
	b.x-=a.x;
	b.y-=a.y;
	c.x-=a.x;
	c.y-=a.y;
	area=b.x*c.y-b.y*c.x;
	if(area<0) area=-area;
	return area/2;
}
float getArea(Point *points,int size)
{
	float area=0;
	for(int i=1;i<size-1;i++){
		area+=getTriArea(points[0],points[i],points[i+1]);
	}
	return area;
}

int main()
{
	float n,v;
	float answer[MAXCASELEN];
	Point point[MAXPOINTS];
	int caseCount=0;
	//
	cin>>n;
	while(n>=3){
		int j=0;
		for(j=0;j<n;j++) cin>>point[j].x>>point[j].y;
		cin>>v;
		answer[caseCount]=v/getArea(point,n);
		caseCount++;
		cin>>n;
	}
	for(int i=0;i<caseCount;i++){
		cout<<"BAR LENGTH: "<<setiosflags(ios::fixed)<<setprecision(2)<<answer[i]<<"\n";
	}
	return 0;
}
