#include<queue>
#include<iostream>
#define MAXOFTOWERS 12
#define MAXOFCASE 500
#define NEARDIST 20
const int SQNEARDIST=NEARDIST*NEARDIST;
using namespace std;
struct Point{
	float x;float y;
};
queue<int> q;
int fre[MAXOFTOWERS];
int getAnswer(Point * points,int size){
	int answer=0;
	bool solved[MAXOFTOWERS];
	int i,j;
	for(i=0;i<size;i++){
		solved[i]=false;
		fre[i]=1;
	}
	for(i=0;i<size ;i++){
		if(!solved[i]){
			q.push(i);
			while(!q.empty()){
				int now=q.front();q.pop();
				//getAdj
				for(int k=i;k<size;k++){
					if( k!=now &&  !solved[k]){
						int dx=points[k].x-points[now].x;
						int dy=points[k].y-points[now].y;
						
						if(dx*dx+dy*dy<=SQNEARDIST){
							
							//k is now's nearby tower.
							if(fre[k]==fre[now]){
								fre[k]++;
								
							}
							q.push(k);
						}
					}
				}
				solved[now]=true;
				//end getAdj
			}
		}
	}
	for(i=0;i<size;i++){
		
		if(fre[i]>answer) answer=fre[i];
	}
	return answer;
}
int main()
{
	int numTowers;
	int answer[MAXOFCASE];
	//
	Point points[MAXOFTOWERS];
	int caseCount=0;
	while(1){
		cin>>numTowers;
		if(numTowers==0) break;
		//start.
		for(int j=0;j<numTowers;j++){
			cin>>points[j].x>>points[j].y;
		}
		answer[caseCount]=getAnswer(points,numTowers);
		//end.
		caseCount++;
	}
	int i;
	for( i=0;i<caseCount-1;i++){
		cout<<"The towers in case "<<i+1<<" can be covered in "<<answer[i]<<" frequencies."<<endl;
		
	}
	cout<<"The towers in case "<<i+1<<" can be covered in "<<answer[i]<<" frequencies.";
	return 0;
}