#include"CEightQueen.h"
#include<iostream.h>
CEightQueen::CEightQueen(){
	int *p=&arr[0][0];
	for(int i=0;i<8*8;i++){
		*p++=0;
	}
//	cout<<"initializing..."<<endl;
//	print();
}
CEightQueen::CEightQueen(CEightQueen & t){
//	cout<<"copying.."<<endl;
	int *p=&arr[0][0];
	int *pt=&t.arr[0][0];
	for(int i=0;i<8*8;i++){
		*p++=*pt++;
	}
}
bool CEightQueen::setQueen(int row,int col){
	if(canSet(row,col)){
		int i,j;
		//setflag line
		for(i=0;i<8;i++){
			arr[row][i]=1;
		}
		//setflag col
		for(i=0;i<8;i++){
			arr[i][col]=1;
		}
		//setflag /
		j=row+col;
		if(j<8){
			for(i=j;i>=0;i--){
				arr[j-i][i]=1;
			}
		}else{
			j-=7;
			for(i=j;i<8;i++){
				arr[7+j-i][i]=1;
			}
		}
		//setflag "\"
		int dr=row-col;
		if(dr>0){
			for(i=dr;i<8;i++){
				arr[i][i-dr]=1;
			}
		}else{
			dr=-dr;
			for(i=dr;i<8;i++){
				arr[i-dr][i]=1;
			}
		}
		arr[row][col]=2;
		return true;
	}
	return false;
}
void CEightQueen::print(){
	cout<<"arr:"<<endl;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			cout<<arr[i][j]<<",";
		}
		cout<<endl;
	}
}
bool CEightQueen::canSet(int row,int col){
	return (arr[row][col]==0);
}
/*
*/