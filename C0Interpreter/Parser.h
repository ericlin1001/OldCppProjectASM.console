//
//
#ifdef PARSER_H
#else
#define PARSER_H

inline bool is_end_of_input(char ch)	{	return (ch=='\0');								}
inline bool is_lc_letter(char ch)		{	return ('a'<=ch&&ch<='z');						}
inline bool is_uc_letter(char ch)		{	return ('A'<=ch&&ch<='Z');						}
inline bool is_letter(char ch)			{	return (is_lc_letter(ch)||is_uc_letter(ch));	}
inline bool is_digit(char ch)			{	return ('0'<=ch&&ch<='9');						}
inline bool is_letter_or_digit(char ch)	{	return (is_digit(ch)||is_letter(ch));			}
inline bool is_operator(char ch)		{	return (ch=='+'||ch=='-'||ch=='*');				}
inline bool is_layout(char ch)			{	return (!is_end_of_input(ch)&&ch<=' ');			}
//token.type
#define BEGIN	1		/*定义	{		的宏名*/
#define NUM		2		/*定义	num		的宏名*/
#define IDEN	3		/*定义	iden	的宏名*/
#define PLUS	4		/*定义	+		的宏名*/
#define MULT	5		/*定义	*		的宏名*/
#define ASSI	6		/*定义	=		的宏名*/
#define READ	7		/*定义	read	的宏名*/
#define WRITE	8		/*定义	write	的宏名*/
#define SEMI	9		/*定义	;		的宏名*/
#define	OPEN	10		/*定义	(		的宏名*/
#define CLOSE	11		/*定义	)		的宏名*/
#define END		12		/*定义	}		的宏名*/
#define EOF		13		/*定义	endoffile的宏名*/
#define SUB		14		/*定义	-		的宏名*/
//


//
#define MAX_SIZEOF_DIGIT 10
#define MAX_SIZEOF_SEMAN 10 //>=MAX_SIZEOF_DIGIT
//structure:
typedef struct{
	char *fileName;
	int lineNumber;
	int tokenName;
}PositionInFile;
typedef struct{
	int type;
	char seman[MAX_SIZEOF_SEMAN];
	PositionInFile pos;
}Token;
//
//globle variables:
extern char g_ch;
extern char *g_progFile;
extern int g_fp;
extern Token g_token;
//
void back();
void nextChar();
void nextAvailChar();
void recognizeNumber();
void recognizeName();
void error(char *mess="no");
void nextToken();
//
void checkToken(int type);
void prog();
void expr();
void reset();
#endif