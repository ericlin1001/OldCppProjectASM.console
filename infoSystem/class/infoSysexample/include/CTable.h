#ifndef CTABLE_H
#define CTABLE_H
//for test
#ifdef __test__
#include<iostream>
using namespace std;
#define TestTrace(mess)  cout<<mess;
#else
#define TestTrace(mess)  
#endif
//end test
#define DEFAULT_NUM_ROW 20
#define DEFAULT_NUM_COL 20
#ifndef NULL
#define NULL 0
#endif
template<class MyType>
class CTable{
	typedef MyType *PMyType;
private:
	PMyType *table;
	int numRows;
	int numCols;
	int maxNumRows;
	int maxNumCols;
public:
	CTable(){
		maxNumRows=DEFAULT_NUM_ROW;
		maxNumCols=DEFAULT_NUM_COL;
		numRows=0;
		numCols=0;
		initATable(table,maxNumRows,maxNumCols);
	}
	~CTable(){
		releaseTable();
	}
	void init(int tnumRows,int tnumCols){
		while(maxNumRows<=tnumRows)expandMaxRow();
		while(maxNumCols<=tnumCols)expandMaxCol();
		numRows=tnumRows;
		numCols=tnumCols;
	}
	int getNumRows(){return numRows;}
	int getNumCols(){return numCols;}
	
	
	bool interchangeCol(int cola,int colb){
		if(isValCol(cola) && isValCol(colb)){
			int tempCol=numCols;
			insertCol(numCols);
			copyCol(tempCol,cola);
			copyCol(cola,colb);
			copyCol(colb,tempCol);
			delCol(tempCol);
			return true;
		}
		return false;
	}
	bool interchangeRow(int rowa,int rowb){
		if(isValRow(rowa) && isValRow(rowb)){
			int tempRow=numRows;
			insertRow(numRows);
			copyRow(tempRow,rowa);
			copyRow(rowa,rowb);
			copyRow(rowb,tempRow);
			delRow(tempRow);
			return true;
		}
		return false;
	}
	bool delCol(int delCol){
		if(delCol>=numCols || delCol<0){
			return false;
		}
		for(int col=delCol;col<numCols-1;col++){
			copyCol(col,col+1);
		}
		numCols--;
		return true;
	}
	bool delRow(int delRow){
		if(delRow>=numRows || delRow<0){
			return false;
		}
		for(int row=delRow;row<numRows-1;row++){
			copyRow(row,row+1);
		}
		numRows--;
		return true;
	}
	bool insertCol(int startCol){
		if(startCol>numCols || startCol<0){
			return false;
		}
		numCols++;//allocate the memory.
		for(int col=numCols-1;col>startCol;col--){
			if(!copyCol(col,col-1))return false;
		}
		if(numCols>=maxNumCols){
			expandMaxCol();
		}
		return true;
	}
	bool insertRow(int startRow){//the too big num mean insert in the last.
		if(startRow>numRows || startRow<0){
			return false;
		}
		numRows++;
		for(int row=numRows-1;row>startRow;row--){
			if(!copyRow(row,row-1)){
				return false;
			}
		}
		if(numRows>=maxNumRows){
			expandMaxRow();
		}
		return true;
	}
	MyType get(int row,int col){
		if(isInRange(row,col)){
			return table[row][col];
		}
		return (MyType )NULL;
	}
	bool assign(int row,int col,MyType value){
		return set(row,col,value);
	}
	bool set(int row,int col,MyType value){
		if(isInRange(row,col)){
			table[row][col]=value;
			return true;
		}
		return false;
	}
	void print(){
		int row,col;
		for(row=0;row<numRows;row++){
			for(col=0;col<numCols;col++){
				TestTrace(get(row,col)<<',');
			}
			TestTrace(endl);
		}
	}
private://be private
	bool isInRange(int row,int col){return isValRow(row)&& isValCol(col);}
	bool isValRow(int row){	return 0<=row && row <numRows;}
	bool isValCol(int col){return 0<=col && col<numCols;}
	bool initATable(PMyType * &temp,int row,int col){
		if((temp=new PMyType[row])==NULL){
			return false;
		}
		for(int i=0;i<row;i++){
			if((temp[i]=new MyType[col])==NULL){
				return false;
			}
		}
		return true;
	}
	void releaseTable(){
		for(int i=0;i<maxNumRows;i++){
			delete [] table[i];
		}
		delete []table;
	}
	bool copyCol(int destCol,int srcCol){
		if(isValCol(destCol)&&isValCol(srcCol)){
			int row;
			for(row=0;row<numRows;row++){
				table[row][destCol]=table[row][srcCol];
			}
			return true;
		}
		return false;
	}
	bool copyRow(int destRow,int srcRow){
		if(isValRow(destRow)&&isValRow(srcRow)){
			int col;
			for(col=0;col<numCols;col++){
				table[destRow][col]=table[srcRow][col];
			}
			return true;
		}
		return false;
	}
	bool expandMaxRow(){
		TestTrace("expandMaxRow...");
		PMyType *temp;
		if(!initATable(temp,maxNumRows*2,maxNumCols))return false;
		int row,col;
		for( row=0;row<maxNumRows;row++){
			for(col=0;col<maxNumCols;col++){
				temp[row][col]=table[row][col];
			}
		}
		releaseTable();
		table=temp;
		maxNumRows*=2;
		return true;
	}
	bool expandMaxCol(){
		TestTrace("expandMaxCol...");
		PMyType *temp;
		if(!initATable(temp,maxNumRows,maxNumCols*2))return false;
		int row,col;
		for( row=0;row<maxNumRows;row++){
			for(col=0;col<maxNumCols;col++){
				temp[row][col]=table[row][col];
			}
		}
		releaseTable();
		table=temp;
		maxNumCols*=2;
		return true;
	}
};


//below is the depart format,but just has the same function with above
/*
template<class MyType>
class CTable{
typedef MyType *PMyType;
private:
PMyType *table;
int numRows;
int numCols;
int maxNumRows;
int maxNumCols;
public:
CTable();
~CTable();
void t(){}
int getNumRows(){return numRows;}
int getNumCols(){return numCols;}
void init(int tnumRows,int tnumCols);
bool delCol(int delCol);
bool interchangeCol(int cola,int colb);
bool interchangeRow(int rowa,int rowb);
bool delRow(int delRow);
bool insertCol(int startCol);
bool insertRow(int startRow);
MyType get(int row,int col);
bool assign(int row,int col,MyType value);
bool set(int row,int col,MyType value);
void print();
private://be private
bool isInRange(int row,int col){return isValRow(row)&& isValCol(col);}
bool isValRow(int row){	return 0<=row && row <numRows;}
bool isValCol(int col){return 0<=col && col<numCols;}
bool initATable(PMyType * &temp,int row,int col);
void releaseTable();
bool copyCol(int destCol,int srcCol);
bool copyRow(int destRow,int srcRow);
bool expandMaxRow();
bool expandMaxCol();
};

  template<class MyType>
  CTable<MyType>::CTable(){
  maxNumRows=DEFAULT_NUM_ROW;
  maxNumCols=DEFAULT_NUM_COL;
  numRows=0;
  numCols=0;
  initATable(table,maxNumRows,maxNumCols);
  }
  template<class MyType>
  CTable<MyType>::~CTable(){
  releaseTable();
  }
  template<class MyType>
  void CTable<MyType>:: init(int tnumRows,int tnumCols){
  while(maxNumRows<=tnumRows)expandMaxRow();
  while(maxNumCols<=tnumCols)expandMaxCol();
  numRows=tnumRows;
  numCols=tnumCols;
  }
  template<class MyType>
  bool CTable<MyType>:: delCol(int delCol){
  if(delCol>=numCols || delCol<0){
		return false;
		}
		for(int col=delCol;col<numCols-1;col++){
		copyCol(col,col+1);
		}
		numCols--;
		return true;
		}
		template<class MyType>
		bool CTable<MyType>::interchangeCol(int cola,int colb){
		if(isValCol(cola) && isValCol(colb)){
		int tempCol=numCols;
		insertCol(numCols);
		copyCol(tempCol,cola);
		copyCol(cola,colb);
		copyCol(colb,tempCol);
		delCol(tempCol);
		return true;
		}
		return false;
		}
		template<class MyType>
		bool CTable<MyType>:: interchangeRow(int rowa,int rowb){
		if(isValRow(rowa) && isValRow(rowb)){
		int tempRow=numRows;
		insertRow(numRows);
		copyRow(tempRow,rowa);
		copyRow(rowa,rowb);
		copyRow(rowb,tempRow);
		delRow(tempRow);
		return true;
		}
		return false;
		}
		template<class MyType>
		bool CTable<MyType>:: delRow(int delRow){
		if(delRow>=numRows || delRow<0){
		return false;
		}
		for(int row=delRow;row<numRows-1;row++){
		copyRow(row,row+1);
		}
		numRows--;
		return true;
		}
		template<class MyType>
		bool CTable<MyType>:: insertCol(int startCol){
		if(startCol>numCols){
		startCol=numCols;
		}else if(startCol<0){
		return false;
		}
		numCols++;//allocate the memory.
		for(int col=numCols-1;col>startCol;col--){
		if(!copyCol(col,col-1))return false;
		}
		if(numCols>=maxNumCols){
		expandMaxCol();
		}
		return true;
		}
		template<class MyType>
		bool CTable<MyType>::insertRow(int startRow){//the too big num mean insert in the last.
		if(startRow>numRows){
		startRow=numRows;
		}else if(startRow<0){
		return false;
		}
		numRows++;
		for(int row=numRows-1;row>startRow;row--){
		if(!copyRow(row,row-1)){
		return false;
		}
		}
		if(numRows>=maxNumRows){
		expandMaxRow();
		}
		return true;
		}
		template<class MyType>
		MyType CTable<MyType>::get(int row,int col){
		if(isInRange(row,col)){
		return table[row][col];
		}
		return (MyType )NULL;
		}
		template<class MyType>
		bool CTable<MyType>:: assign(int row,int col,MyType value){
		return set(row,col,value);
		}
		template<class MyType>
		bool CTable<MyType>:: set(int row,int col,MyType value){
		if(isInRange(row,col)){
		table[row][col]=value;
		return true;
		}
		return false;
		}
		template<class MyType>
		void CTable<MyType>:: print(){
		int row,col;
		for(row=0;row<numRows;row++){
		for(col=0;col<numCols;col++){
		TestTrace(get(row,col)<<',');
		}
		TestTrace(endl);
		}
		}
		template<class MyType>
		bool CTable<MyType>::initATable(PMyType * &temp,int row,int col){
		if((temp=new PMyType[row])==NULL){
		return false;
		}
		for(int i=0;i<row;i++){
		if((temp[i]=new MyType[col])==NULL){
		return false;
		}
		}
		return true;
		}
		template<class MyType>
		void CTable<MyType>:: releaseTable(){
		for(int i=0;i<maxNumRows;i++){
		delete [] table[i];
		}
		delete []table;
		}
		template<class MyType>
		bool CTable<MyType>:: copyCol(int destCol,int srcCol){
		if(isValCol(destCol)&&isValCol(srcCol)){
		int row;
		for(row=0;row<numRows;row++){
		table[row][destCol]=table[row][srcCol];
		}
		return true;
		}
		return false;
		}
		template<class MyType>
		bool CTable<MyType>:: copyRow(int destRow,int srcRow){
		if(isValRow(destRow)&&isValRow(srcRow)){
		int col;
		for(col=0;col<numCols;col++){
		table[destRow][col]=table[srcRow][col];
		}
		return true;
		}
		return false;
		}
		template<class MyType>
		bool CTable<MyType>:: expandMaxRow(){
		TestTrace("expandMaxRow...");
		PMyType *temp;
		if(!initATable(temp,maxNumRows*2,maxNumCols))return false;
		int row,col;
		for( row=0;row<maxNumRows;row++){
		for(col=0;col<maxNumCols;col++){
		temp[row][col]=table[row][col];
		}
		}
		releaseTable();
		table=temp;
		maxNumRows*=2;
		return true;
		}
		template<class MyType>
		bool CTable<MyType>:: expandMaxCol(){
		TestTrace("expandMaxCol...");
		PMyType *temp;
		if(!initATable(temp,maxNumRows,maxNumCols*2))return false;
		int row,col;
		for( row=0;row<maxNumRows;row++){
		for(col=0;col<maxNumCols;col++){
		temp[row][col]=table[row][col];
		}
		}
		releaseTable();
		table=temp;
		maxNumCols*=2;
		return true;
}*/
#endif
//for test:CTable:
/*
#ifndef TestFun
#define TestFun(FUN) cout<<"After "<<#FUN<<":"<<FUN<<endl;
#endif
CTable<int> t;
t.init(5,7);
int row,col;
for(row=0;row<5;row++){
for(col=0;col<9;col++){
t.assign(row,col,row*10+col);
}
}
t.print();
TestFun(t.insertRow(2))
t.print();
TestFun(t.insertCol(5))
t.print();
TestFun(t.insertCol(4))
TestFun(t.insertRow(3))
t.print();
TestFun(t.delCol(2))
t.print();
TestFun(t.delRow(3))
t.print();
TestFun(t.delRow(5))
t.print();
*/