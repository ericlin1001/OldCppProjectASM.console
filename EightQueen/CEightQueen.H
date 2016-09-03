class CEightQueen{
private :
	int arr[8][8];
	//0:
public:
	CEightQueen();
	CEightQueen(CEightQueen & t);
	bool setQueen(int row,int col);
	void print();
protected:
	bool canSet(int row,int col);

};
/*
*/