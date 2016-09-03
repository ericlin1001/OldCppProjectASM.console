#include<iostream>
using namespace std;
//user define:
#define DEFAULT_PORT 6789
#define FILE_USERPASS "userpass.txt"
//
#define MAX_LEN_SHOWNAME		20
#define MAX_LEN_USERNAME		20
#define MAX_LEN_PASS			20
#define MAX_LEN_CHATTEXT		200
#define MAX_LEN_PREFIX			40
//
#define INVALID_ID -1
#define SERVER_ID 0
//
//MESSAGE.TYPE
#define MT_ERROR					-1
#define MT_LOGIN					0
#define MT_LOGOFF					1
#define MT_CHAT						2
#define MT_PASSDIRECT				3
//
#define MYSUCCESS 0
#define MYERROR -1


//
//Message type defined
typedef struct {
	int type;
	int from;
	int to;
	unsigned int dataLen;
	int certification;
	void print(){
		cout<<"Messageheader:"<<endl
			<<"type="<<type<<endl
			<<"from id:"<<from<<endl
			<<"to id:"<<to<<endl
			<<"dataLen:"<<dataLen<<endl
			<<"certification:"<<certification<<endl;
	}
}MessageHeader;
struct LoginData{
	char user[MAX_LEN_USERNAME];
	char pass[MAX_LEN_PASS];
	int id;
	int certification;
	bool isSuccess;
};
struct LogoffData{
	bool isSuccess;
};
struct ChatData{
	char prefix[MAX_LEN_PREFIX];
	char text[MAX_LEN_CHATTEXT];
};
union MessageData{
	LoginData login;
	LogoffData logoff;
	ChatData chat;
};
struct Message{
	MessageHeader h;
	MessageData d;
};

//
#define Test(m) cout<<#m"="<<(m)<<endl;