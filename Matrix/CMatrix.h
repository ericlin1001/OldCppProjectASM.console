#include<iostream>
#include<iomanip>
using namespace std;
enum ERRORTYPE{OUTOFRANGE,DIVIDEDBYZERO};
template <class T>class CMatrix
{
public:
	CMatrix(){
		numRows=0;
		numCols=0;
		data=NULL;
	}
	void init(T *arr,int row,int col){
		numRows=row;
		numCols=col;
		data=NULL;
		createArea();
		for(int i=0;i<numRows;i++){
			for(int j=0;j<numCols;j++){
				set(i,j,arr[i*col+j]);
			}
		}
	}
	CMatrix(int row,int col){
		numRows=row;
		numCols=col;
		data=NULL;
		createArea();
	}
	void echelon(){
		cout<<"after echelon"<<endl;
		echeReduce(0,0);
	}
	int isNonZeroCol(int col){
		for(int i=crow;i<numRows;i++){
			if(data[i][col]!=0){
				return i;
			}
		}
		return -1;
	}
	void echeReduce(const int row,const int col){
		if(row>numRows-1 || col> numCols-1)
			return ;
		//
		int i;
		crow=row;
		int temp;
		for( ccol=col;ccol<numCols;ccol++){
			if((temp=isNonZeroCol(ccol))!=-1) break;
		}
		crow=temp;
		//
		T divtemp=data[crow][ccol];
		cout<<"divtemp:"<<divtemp<<endl;
		divRow(crow,divtemp);
		rowchg(crow,row);
		crow=row;
		/**/
		for( i=row+1;i<numRows;i++){
			T t;
			if((t=data[i][ccol])!=0){
					cout<<"div:"<<t<<endl;
				divRow(i,t);
				subRow(i,data[row]);
			}
		}/**/
		//
		echeReduce(row+1,ccol+1);
		cout<<"in"<<endl;
	}

	void divRow(int row,T a){
		if(a==0) {
			error(DIVIDEDBYZERO,"Divided by 0.");
			return ;
		}
		for(int i=ccol;i<numCols;i++){
			data[row][i]/=a;
		}
	}
	void divRow(int row,T *a){
		if(a==0) {
			error(DIVIDEDBYZERO,"Divided by 0.");
			return ;
		}
		for(int i=0;i<numCols;i++){
			data[row][i]/=a[i];
		}
	}
	void subRow(int row,T a){
		for(int i=0;i<numCols;i++){
			data[row][i]-=a;
		}
	}
	void subRow(int row,T *a){
		for(int i=0;i<numCols;i++){
			data[row][i]-=a[i];
		}
	}
	void addRow(int row,T a){
		for(int i=0;i<numCols;i++){
			data[row][i]+=a;
		}
	}
	void mulRow(int row,T a){
		for(int i=0;i<numCols;i++){
			data[row][i]*=a;
		}
	}
	int isNonZeroRow(int row){
		for(int i=ccol;i<numCols;i++){
			if(data[row][i]!=0){
				return i;
			}
		}
		return -1;
	}
	
	void rowchg(int row1,int row2){
		T *t=*(data+row1);
		*(data+row1)=*(data+row2);
		*(data+row2)=t;
	}
	void swap(T &a,T &b){
		T c=a;
		a=b;
		b=c;
	}
	void invert(){
		cout<<"after invert:"<<endl;
		int i,j;
		for(i=0;i<numRows;i++){
			for(j=0;j<numCols/2;j++){
				swap(data[i][j],data[i][numCols-1-j]);
			}
		}
		for(i=0;i<numRows/2;i++){
			rowchg(i,numRows-1-i);
		}
	}
	void reducedEchelon(){
		cout<<"after reducedEchelon:"<<endl;
		invert();
		echeReduce(numRows-1-crow,numCols-1-ccol);
		invert();	
	}
	void input(){
		cout<<"input like that:"<<endl
			<<"m n"<<endl
			<<"a11 a12 ... a1n"<<endl
			<<"a21 a22 ... a2n"<<endl
			<<"."<<endl
			<<"."<<endl
			<<"."<<endl
			<<"am1 am2 ... amn"<<endl;
		cin>>numRows>>numCols;
		createArea();
		for(int i=0;i<numRows;i++){
			for(int j=0;j<numCols;j++){
				cin>>data[i][j];
			}
		}
	}
	~CMatrix(){
		if(data!=NULL) delete []data;
	}
	CMatrix(CMatrix &A){
		numRows=A.numRows;
		numCols=A.numCols;
		createArea();
		for(int i=0;i<numRows;i++){
			for(int j=0;j<numCols;j++){
				data[i][j]=A.data[i][j];
			}
		}
	}
	CMatrix &operator=(CMatrix &A){
		numRows=A.numRows;
		numCols=A.numCols;
		createArea();
		for(int i=0;i<numRows;i++){
			for(int j=0;j<numCols;j++){
				set(i,j,A.get(i,j));
			}
		}
	}
	//operation function:
	const T get(int row,int col){
		if(!testRowCol(row,col)) return 0;
		return data[row][col];
	}
	void set(int row,int col,T value){
		if(testRowCol(row,col)){
			data[row][col]=value;
		}
	}
	void print(){
		cout<<"print:"<<endl;
		for(int i=0;i<numRows;i++){
			for(int j=0;j<numCols;j++){
				cout<<setiosflags(ios::fixed)<<setprecision(2)<<data[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}
	T & operator[](int row){
		if(testRowCol(row,0)){
			return data[row][0];
		}else{
			return data[0][0];
		}
	}
private:
	bool isInRange(int x,int min,int max){
		return (min<=x && x<=max);
	}
	bool testRowCol(int row,int col){
		if( isInRange(row,0,numRows) && isInRange(col,0,numCols)){
			return true;
		}else{
			error(OUTOFRANGE,"The operation row or col out of Range.");
			return false;
		}
	}
protected:
	void error(int type,char *mess){
		cout<<"Error("<<type<<"):"<<mess<<endl;
	}
	int ccol;
	int crow;
	T **data;
	int numRows;
	int numCols;
	void createArea(){
		if(data!=NULL) delete []data;
		data=new T *[numRows];
	for(int i=0;i<numRows;i++){
		*(data+i)=new T[numCols];
		}
	}
};