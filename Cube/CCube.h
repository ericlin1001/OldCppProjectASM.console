class CCube
{
protected:
	CBlock blocks[3][3][3];
public:

	CCube()
	{
		HCBlock faceBlocks[9];
		getFaceBlocks(UP,faceBlocks);
		for(int i=0;i<9;i++){
			faceBlocks[i]->setFaceColor(UP,YELLOW);
		}
	}
	void getFaceBlocks(FACE face,HCBlock *faceBlocks)
	{
		int i,j=0;
		switch(face){
		case UP:
		//	blocks
			for( i=0;i<9;i++){
					faceBlocks[i]=&blocks[2][(i-i%3)/3][i%3];
			}
			break;
		default:
			cout<<"no this face"<<endl;
			break;
		}
	}
	void print(FACE face){
		int i;
		switch(face){
		case FRONT:
		//	cout<<"the front face is:"<<endl;
		//	cout<<endl;
			break;
		case UP:
			cout<<"the front face is:";
			HCBlock faceBlocks[9];
			getFaceBlocks(UP,faceBlocks);
			for(i=0;i<9;i++){
				if(i%3==0){cout<<"next line"<<endl;}
				cout<<faceBlocks[i]->getFaceColor(face)<<",";
			}
			cout<<endl;
			break;
		default:
			cout<<"no this face"<<endl;
			break;
		}
	}
	~CCube(){}
	void U(bool clockwise=true){
		if(clockwise){
			cout<<"after U:"<<endl;
		}else{
			cout<<"after U':"<<endl;
		}
	}
	void R();
	void L();
	void B();
	void F();
	void D();
};