#include<iostream>
#define MAXOFPOINTS 50
#define MAXOFROUTES 100
#define MAXOFCASE 5000
using namespace std;
struct myType{
	int pa;int pb;
	int cost;
};
bool isInSameSet(int a,int b);
void Union(int a,int b,int);
int sets[MAXOFPOINTS+1];
int getAnswer(myType * routes,int size,int numPoints){
	int answer=0;
	//bubbling sort:
	int i,j;
	for( i=1;i<size;i++){
		for(j=0;j<i;j++){
			if(routes[j].cost>routes[j+1].cost){
				myType t;
				t=routes[j];
				routes[j]=routes[j+1];
				routes[j+1]=t;
			}
		}
	}
	//
	for(i=1;i<=size;i++){sets[i]=i;}
	for(i=0;i<size;i++){
		if(!isInSameSet(routes[i].pa,routes[i].pb)){
			answer+=routes[i].cost;
			Union(routes[i].pa,routes[i].pb,size);
		}
	}
	return answer;
}
bool isInSameSet(int a,int b){
	return sets[a]==sets[b];
}
void Union(int a,int b,int size){
	int set=sets[b];
	for(int i=1;i<=size;i++){
		if(sets[i]==set){
			sets[i]=sets[a];
		}
	}
}
int main()
{
	int numPoints,numRoutes;
	int answer[MAXOFCASE];
	//
	myType routes[MAXOFROUTES];
	int caseCount=0;
	while(1){
		cin>>numPoints;
		if(numPoints==0) break;
		cin>>numRoutes;
		//start.
		for(int j=0;j<numRoutes;j++){
			cin>>routes[j].pa>>routes[j].pb>>routes[j].cost;
		}
		answer[caseCount]=getAnswer(routes,numRoutes,numPoints);
		//end.
		caseCount++;
	}
	int i;
	for( i=0;i<caseCount-1;i++){
		cout<<answer[i]<<endl;
	}
	cout<<answer[i];
	return 0;
}