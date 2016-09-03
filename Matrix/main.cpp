#include<iostream>
#include "CMatrix.h"
using namespace std;
int main(){
	CMatrix<double> a(3,5);
	double c[3][5]={{7,2,9,8,4},
					{4,3,4,7,8},
					{9,5,6,4,7}};
	a.init(&c[0][0],3,5);
	a.print();

	a.echelon();
	a.print();

	a.reducedEchelon();
	//a.invert();
	a.print();
	
//	a.echelon();
//	a.print();

	cout<<"\n\ninput:"<<endl;
	a.input();
	a.echelon();
	a.print();

	a.reducedEchelon();
	a.print();/**/
	return 0;

}
