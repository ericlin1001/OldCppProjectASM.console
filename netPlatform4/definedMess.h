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

#define UINT unsigned int
//
//Message type defined
struct MessageHeader{
	int type;
	ID from;//id,SOCKET
	ID to;//id,SOCKET
	UINT dataLen;//remmember the len() must be invoked int the end.
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
		UINT len(){return sizeof(LoginData);}
	} login;
	struct LogoffData{
		bool isSuccess;
		UINT len(){return sizeof(LogoffData);}
	} logoff;
	struct ChatData{
		char prefix[MAX_LEN_PREFIX];
		char text[MAX_LEN_CHATTEXT];
		UINT len(){return MAX_LEN_PREFIX+strlen(text)+1;}
	} chat;
	struct ExampleData{
		int a;
		char str[10];
		UINT len(){return sizeof(ExampleData);}
	} example;
	struct UserDetailData{
		ID id;
		char user[MAX_LEN_USERNAME];
		UINT len(){return sizeof(UserDetailData);}
	}userDetail;
	struct UserListData{
		int from;
		int num;
		char users[MAX_NUM_USERLIST][MAX_LEN_USERNAME];
		UINT len(){return sizeof(from)+sizeof(num)+MAX_LEN_USERNAME*num;}
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



//
template<class T>
class MyVector{
public:
	typedef T* iterator;
	typedef const T CT;
private:
	typedef unsigned int sizt_t;
	#define UNIT sizeof(T)
	size_t s;
	iterator head;
	size_t max;
public:

	
	iterator begin(){
		return head;
	}
	MyVector(){
		max=1;
		s=0;
		head=NULL;
		expand();
	}
	void del(const iterator i){
		memcpy(i,i+1,((end()-i)-1)*UNIT);
		s--;
	}
	void del(const sizt_t i){
		del(begin()+i);
	}
	void erase(const iterator i){
		del(i);
	}
	void erase(const sizt_t i){
		del(i);
	}

	~MyVector(){
		if(head!=NULL){
			delete []head;
		}
	}
	iterator end(){
		return head+s;
	}
	size_t size(){
		return s;
	}
	void push_back(CT & t){
		memcpy(end(),&t,sizeof(T));
		s++;
		if(s>=max){
			expand();
		}
	}
	T &back(){
		return *(head+s-1);
	}
	T &at(size_t i ){
		return *(head+i);
	}
	T &operator[](size_t i){
		return at(i);
	}
	bool empty(){
		return s==0;
	}
private:
	void expand(){
		iterator temp=new T[max*2];
		if(head!=NULL){
			memcpy(temp,head,max*sizeof(T));
			delete []head;
		}
		head=temp;
		max*=2;
	}
};