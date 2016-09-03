#include "CServer.h"
#include "CClient.h"

int main(){
	CServer::init(5150);
	CServer server;
	server.waitThread(0);

	return 0;
}