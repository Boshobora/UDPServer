#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Request.h"
#include "Add.h"
#include "Delete.h"
#include "Send.h"
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

class UDPserver {
private:
	WSADATA wsa{};
	SOCKET in;
	sockaddr_in server{}, client{};
	Request* request = NULL;
	vector<string> users;
	vector<string> messages;
	string chose;
	int limit;
	void winsock();
	void socketCreating(long port);
public:
	void start();
	void setRequest(string operation);
	UDPserver(long port = 54000);
	~UDPserver();
};