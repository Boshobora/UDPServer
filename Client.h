#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <ios>
#include <WS2tcpip.h>
using std::string;

class Client {
private:
	string nick;
	string message;
	WSADATA data;
	WORD version;
	SOCKET out;
	sockaddr_in server;
	void winsock();
	void createSocket(long port);
public:
	Client(long port = 54000);
	void start();
	~Client();
};