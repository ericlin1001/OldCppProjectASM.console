#include<string.h>
#include<iostream>
#include<vector>
#include<cmath>
#define _TEST
struct P{
       int d;
       int cost;
};
//
#ifdef TEST
#define Trace(m) cout<<#m"="<<(m)<<endl;
#else
#define Trace(m)
#endif
using namespace std;
int getMinIndex(const vector<P>& pairs,int from=0){
    int min=from;
    int i;
        for(i=from+1;i<pairs.size();i++){
            if(pairs[i].cost<pairs[min].cost)min=i;
        }
            return min;
}

int main(){
    int t;//t<80
    cin>>t;
    while(t--){
               vector<P> pairs;

        int i;
        for(i=0;i<10;i++){
                          int temp;
                          cin>>temp;
                          if(temp!=-1){
                          P p;
                          p.d=i;
                          p.cost=temp;
                          pairs.push_back(p);
                          }
                     }       
        int m;//1-50
        cin>>m;

        //cal....
        int maxLen=0;
        int min=getMinIndex(pairs);
        int an=-1;
        int buffer[100];
        int l;
		/*10
2
5
6
7
8
9
10
14
15
53
56*/
        if(pairs[min].d==0){
             Trace("0 is the min");
            int min2=getMinIndex(pairs,1);
            if((pairs[min2].cost>m)){
				Trace("in less ");
                 
                      an=0;
                  
            }else{
                  maxLen=1+(m-pairs[min2].cost)/pairs[min].cost;
                  Trace(maxLen); 
                  //
                  int tm=m;
                  int nm=m;
                  for(l=0;l<maxLen;l++){
                     tm=nm-(maxLen-1-l)*pairs[min].cost;
                     for(i=pairs.size()-1;i>=0;i--){
						 if(tm>=pairs[i].cost){
							nm-=pairs[i].cost;
							buffer[l]=pairs[i].d;
							break;
						 }
					 }
                  }
            }
        }else{
              Trace("0 is not the min");
               maxLen=m/pairs[min].cost;
               Trace(maxLen);  
               //
               int tm=m;
                  int nm=m;
                  for(l=0;l<maxLen;l++){
                     tm=nm-(maxLen-1-l)*pairs[min].cost;
                     for(i=pairs.size()-1;i>=0;i--){
						 if(tm>=pairs[i].cost){
							nm-=pairs[i].cost;
							buffer[l]=pairs[i].d;
							//cout<<"p:"<<buffer[l]<<endl;
							break;
						 }
					 }
                  }
        }
        Trace(an);
        //
        if(an==-1){
			for(i=0;i<maxLen;i++){
				cout<<buffer[i];
			}
			cout<<endl;
        }else{
              cout<<an<<endl;
		}
       
               
    }
    
    #ifdef TEST
    system("pause");
    #endif
    return 0;
}

