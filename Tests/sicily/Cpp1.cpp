/*#include<iostream>
using namespace std;
int abs(int a)
{
	if(a<0)return (-a);
	else return a;
}
void sort(int a[],int len)
{
	int i,j,tmp;
	j=1;
	while(j)
	{
		j=0;
		for(i=0;i<len-1;i++)
		{
			if(abs(a[i])>abs(a[i+1]))
			{
				tmp=a[i];
				a[i]=a[i+1];
				a[i+1]=tmp;
				j=1;
			}
		}
	}
}
int main(){
	int t,n,a[1000],b[1000],j,k;
	int res;
	cin>>t;
	for(int i=0;i<t;i++){
		cin>>n;
		for(j=0;j<n;j++){
			cin>>a[j];
		}
		for(j=0;j<n;j++){
			cin>>b[j];
		}
		sort(a,n);
		sort(b,n);
		res=0;
		for(j=0;j<n;j++){
			if(a[j]<0)
			{
				for(k=0;k<n;k++)
				{
					if(b[k]>0 && abs(b[k])<abs(a[k])){
						res++;
						b[k]=0;
						break;
					}
				}
			}
			else
			{
				for(k=0;k<n;k++)
				{
					if(b[k]<0 && abs(b[k])>abs(a[k])){
						res++;
						b[k]=0;
						break;
					}
				}
			}
		}
		cout<<res<<endl;
	}
	return 0;
}*/
#include<iostream>
#include<algorithm>
using namespace std;

int main(){
    int t;
	cin>>t;
	int b[1001];
    int g[1001];
	while(t--){
	int n;
	cin>>n;
	int i;
	for( i=0;i<n;i++)
		cin>>b[i];
	sort(b,b+n);
	for( i=0;i<n;i++)
		cin>>g[i];
	sort(g,g+n);

	 i=0;
    int j=n-1;
	int count=0;
	while(i<n && j>=0){
			if(g[j]<=0){
				while(b[i]<=0 && i<n)i++;
			}

		while(j>=0&&i<n){
		
	    	if(b[i]+g[j]<0){
				count++;
				j--;
				break;
			}
			j--;
			if(g[j]<=0){
				while(b[i]<=0 && i<n)i++;
			}
		}
		i++;
	}
	cout<<count<<endl;
	}
	return 0;
}








