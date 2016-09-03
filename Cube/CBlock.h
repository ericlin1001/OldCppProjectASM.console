enum COLOR	{BLANK,	BLUE,	GREEN,	ORANGE,	RED,	YELLOW,	WHITE};
enum FACE	{		FRONT,	BACK,	LEFT,	RIGHT,	UP,		DOWN};
char faceToColor[6]={""};
class CBlock
{//front back/left right/up down
	COLOR faceColor[6];
public:
	CBlock()
	{
		for(int i=0;i<6;i++){
			faceColor[i]=BLANK;
		}
	}
	void rotaX(bool clockwise=true);
	void setFaceColor(FACE face,COLOR color){
		faceColor[face]=color;
	}
	const COLOR getFaceColor(FACE face){
		return faceColor[face];
	}
};
typedef CBlock * HCBlock;