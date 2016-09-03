#include<iostream>
int main()
{
	int a[75][75];
	int n;
	cin>>n;
	int row=1,col=1,cur=1;
	int up=0;
	int right=1;
	int turn=0;
	int z=n,zz;
	while(cur<=n*n)
	{
		a[row][col]=cur;
	row+=up;
	col+=right;
	if(turn%4==3){
		
	}

	turn++;
	cur++;

	}
	/*#include<iostream>
int main()
{
	int a[75][75];
	int n;
	cin>>n;
	int row=1,col=1,cur=1;
	int up=0;
	int right=1;
	int turn=0;
	int z=n,zz=1;
	while(cur<=n*n)
	{
		a[row][col]=cur;
	row+=up;
	col+=right;
	if(zz>z){
		zz=1;
		z--;
	}

	turn++;
	cur++;
	zz++;
	}*/