#include "UDPserver.h"
void UDPserver::winsock() {
	WORD version = MAKEWORD(2, 2);
	int ws = WSAStartup(version, &wsa);
	if (ws != 0) {
		cout << "Unable to start winsock " << ws;
		return;
	}
}

void UDPserver::socketCreating(long port) {
	{
		in = socket(AF_INET, SOCK_DGRAM, 0);
		server.sin_addr.S_un.S_addr = ADDR_ANY;
		server.sin_family = AF_INET;
		server.sin_port = htons(port);

		if (bind(in, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
			cout << "Can't bind socket " << WSAGetLastError() << endl;
			return;
		}
	}
}

void UDPserver::setRequest(string option) {
	delete request;
	if (option == "Add") {
		request = new Add;
		char response[1024] = "Enter your nick: ";
		if (sendto(in, response, strlen(response), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR) {
			cout << "sendto() failed with error code: " << WSAGetLastError() << "\n";
			exit(EXIT_FAILURE);
		}
	}
	if (option == "Delete") {
		request = new Delete;
		char response[1024] = "We've received your delete request\n";
		if (sendto(in, response, strlen(response), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR) {
			cout << "sendto() failed with error code: " << WSAGetLastError() << "\n";
			exit(EXIT_FAILURE);
		}
	}
	if (option == "Send") {
		request = new Send;
		char response[1024] = "You can type your messages\n";
		if (sendto(in, response, strlen(response), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR) {
			cout << "sendto() failed with error code: " << WSAGetLastError() << "\n";
			exit(EXIT_FAILURE);
		}
	}
}

void UDPserver::start() {
	int clientLength = sizeof(client);
	ZeroMemory(&client, clientLength);

	char buf[1024];
	for (int i = 0; i < limit; ++i) {
		ZeroMemory(buf, 1024);
		// Czekamy na wiadomoœæ
		int bytesIn = recvfrom(in, buf, 1024, 0, (sockaddr*)&client, &clientLength);
		if (bytesIn == SOCKET_ERROR) {
			cout << "Error receiving from client " << WSAGetLastError() << endl;
			continue;
		}
		char clientIp[256];
		ZeroMemory(clientIp, 256);
		inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);
		setRequest(buf); // Ustawianie strategii
		// Czekamy na wiadomoœæ
		bytesIn = recvfrom(in, buf, 1024, 0, (sockaddr*)&client, &clientLength);
		if (bytesIn == SOCKET_ERROR) {
			cout << "Error receiving from client " << WSAGetLastError() << endl;
			continue;
		}
		string r;
		r = request->realization(buf, users, messages);
		const char* response = r.data();
		if (sendto(in, response, strlen(response), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR) {
			cout << "sendto() failed with error code: " << WSAGetLastError() << "\n";
			exit(EXIT_FAILURE);
		}
	}
}

UDPserver::UDPserver(long port) {
	winsock();
	socketCreating(port);
	cout << "How many requests do you want to receive? ";
	cin >> limit;
}

UDPserver::~UDPserver() {
	delete request;
	// Zamykamy gniazdo
	closesocket(in);
	// Wy³¹czamy winsock
	WSACleanup();
}