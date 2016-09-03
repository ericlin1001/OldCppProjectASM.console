
#include<stdio.h>

int m;
void printInt(int *a,int size){
	int i;
	for( i=1;i<size;i++){
		printf("%d ",a[i]);
	}
	printf("%d\n",a[i]);
}
inline void swap(int &a,int &b){
	int t=a;
	a=b;
	b=t;
}
void insertA(int *a,int n,int k){//from 3 to 1
	int t=a[k];
	for(int i=k;i>n;i--){
		a[i]=a[i-1];
	}
	a[n]=t;
}
void insertB(int *a,int n,int k){//from 1 to 3
	int t=a[n];
	for(int i=n;i<k;i++){
		a[i]=a[i+1];
	}
	a[k]=t;
}
void perm(int *a,int n){
	if(n>=m){
		printInt(a,m);
		return ;
	}
	int i;
	for( i=n;i<=m;i++){
		//swap(a[i],a[n]);
	/*	int x=a[i];
		int k=0;
		for(k=i;k>n;k--){
			a[i]=a[i-1];
		}
		a[n]=x;*/
		insertA(a,n,i);//i to n
		perm(a,n+1);
		insertB(a,n,i);//n to i
		/*
		int y=a[n];
		for(k=n;k<i;k++){
			a[i]=a[i+1];
		}
		a[i]=y;*/
	}
}
int main(){
	int a[9];
	int i=0;
	for(i=1;i<9;i++)a[i]=i;
	int n;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d",&m);
		perm(a,1);
	}
return 0;
}
/*#include<stdio.h>
int m;
char buffer[645130];
char *p=buffer;
void printInt(int *a,int size){
	for(int i=0;i<size-1;i++){
		p+=sprintf(p,"%d ",a[i]);
	}
	p+=sprintf(p,"%d\n",a[i]);
}
void swap(int &a,int &b){
	int t=a;
	a=b;
	b=t;
}
void perm(int *a,int n){
	if(n<=1){
		printInt(a,m);
		return ;
	}
	for(int i=0;i<n;i++){
		swap(a[i],a[n-1]);
		perm(a,n-1);
		swap(a[i],a[n-1]);
	}
}
int main(){
	int a[8];
	int i=0;
	for(i=0;i<8;i++)a[i]=i+1;
	int n;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d",&m);
		p=buffer;
		perm(a,m);
		printf("%sz",buffer);
	}
return 0;
}*/

/*


*/