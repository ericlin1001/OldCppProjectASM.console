
#include<iostream>
#include<stack>
using namespace std;
int main()
{
int n,i;
while(cin>>n,n)
{
int 
a[200100],l,r;
for(i=0;i!=n;i++)
{
cin>>l>>r;
a[l]=r;
a[r]=l;
}
stack<int> b;
for(i=1;i<=2*n;i++)
{

if(b.empty())
b.push(i);
else if(a[b.top()]==i)
b.pop();
else
b.push(i);
}
if (b.empty())
cout << "Yes" << endl;
else 
cout << "No" << endl;
}
}