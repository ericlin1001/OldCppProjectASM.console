# include <iostream>


using namespace std;

int main ()
{
	int n;
	cin>>n;
	int sec=n%60;
	n/=60;
	int min=n%60;
	n/=60;
	int hour=n%24;
	n/=24;
	int day=n;
	cout<<day<<" "
		<<hour<<" "
		<<min<<" "
		<<sec<<" "<<endl;

	
}