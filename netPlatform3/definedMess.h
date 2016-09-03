#include<iostream>
using namespace std;
//user define:
#define ID unsigned int
#define INVALID_ID -1
#define SERVER_ID 0
//
#define DEFAULT_PORT 6789
#define FILE_USERPASS "userpass.txt"
//
#define MAX_LEN_SHOWNAME		20
#define MAX_LEN_USERNAME		20
#define MAX_LEN_PASS			20
#define MAX_LEN_CHATTEXT		200
#define MAX_LEN_PREFIX			40
#define MAX_NUM_USERLIST		10

//

//
#define MYSUCCESS 0
#define MYERROR -1


//
//Message type defined
struct MessageHeader{
	int type;
	ID from;//id,SOCKET
	ID to;//id,SOCKET
	unsigned int dataLen;//remmember the len() must be invoked int the end.
	int certification;//not use.
	void print(){
		cout<<"Messageheader:"<<endl
			<<"type="<<type<<endl
			<<"from id:"<<from<<endl
			<<"to id:"<<to<<endl
			<<"dataLen:"<<dataLen<<endl
			<<"certification:"<<certification<<endl;
	}
};
union MessageData{
	struct LoginData{
		char user[MAX_LEN_USERNAME];
		char pass[MAX_LEN_PASS];
		ID id;
		int certification;
		bool isSuccess;
		int len(){return sizeof(LoginData);}
	} login;
	struct LogoffData{
		bool isSuccess;
		int len(){return sizeof(LogoffData);}
	} logoff;
	struct ChatData{
		char prefix[MAX_LEN_PREFIX];
		char text[MAX_LEN_CHATTEXT];
		int len(){return MAX_LEN_PREFIX+strlen(text)+1;}
	} chat;
	struct ExampleData{
		int a;
		char str[10];
		int len(){return sizeof(ExampleData);}
	} example;
	struct UserDetailData{
		ID id;
		char user[MAX_LEN_USERNAME];
		int len(){return sizeof(UserDetailData);}
	}userDetail;
	struct UserListData{
		int from;
		int num;
		char users[MAX_NUM_USERLIST][MAX_LEN_USERNAME];
		int len(){return sizeof(from)+sizeof(num)+MAX_LEN_USERNAME*num;}
	}userList;
};
struct Message{
	MessageHeader h;
	MessageData d;
};
//MESSAGE.TYPE
#define MT_ERROR					-1
#define MT_LOGIN					0
#define MT_LOGOFF					1
#define MT_CHAT						2
#define MT_PASSDIRECT				3
#define MT_EXAMPLE					4
#define MT_GETUSERDETAIL			5
#define MT_GETUSERLIST				6
//
#define Test(m) cout<<#m"="<<(m)<<endl;