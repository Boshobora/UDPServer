#define _CRT_SECURE_NO_WARNINGS
#include "Client.h"
using namespace std;

void Client::winsock() {
	// Uruchamiamy winsock
	version = MAKEWORD(2, 2);
	int ws = WSAStartup(version, &data);
	if (ws != 0) {
		cout << "Unable to start winsock " << ws;
		return;
	}
}

void Client::createSocket(long port) {
	// Tworzymy strukturê wskazówek dla serwera
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

	// Tworzymy gniazdo
	out = socket(AF_INET, SOCK_DGRAM, 0);
}

Client::Client(long port) {
	winsock();
	createSocket(port);
	// Ustawianie strategii
	message = "Add";
	int sendOk = sendto(out, message.c_str(), message.size() + 1, 0, (sockaddr*)&server, sizeof(server));
	if (sendOk == SOCKET_ERROR)
		cout << "That didn't work" << WSAGetLastError() << endl;
	// Odpowied¿
	char answer[1024] = {};
	int slen = sizeof(sockaddr_in);
	int answer_length;
	if ((answer_length = recvfrom(out, answer, 1024, 0, (sockaddr*)&server, &slen)) == SOCKET_ERROR) {
		cout << "recvfrom() failed with error code: " << WSAGetLastError() << "\n";
		exit(EXIT_FAILURE);
	}
	cout << answer;
	// Ustawienie nicku
	cin >> message;
	nick = message;
	sendOk = sendto(out, message.c_str(), message.size() + 1, 0, (sockaddr*)&server, sizeof(server));
	if (sendOk == SOCKET_ERROR)
		cout << "That didn't work" << WSAGetLastError() << endl;
	// Odbieramy odpowiedŸ
	slen = sizeof(sockaddr_in);
	if ((answer_length = recvfrom(out, answer, 1024, 0, (sockaddr*)&server, &slen)) == SOCKET_ERROR) {
		cout << "recvfrom() failed with error code: " << WSAGetLastError() << "\n";
		exit(EXIT_FAILURE);
	}
	cout << answer;
}

void Client::start() {
	// Ustawianie strategii
	message = "Send";
	int sendOk = sendto(out, message.c_str(), message.size() + 1, 0, (sockaddr*)&server, sizeof(server));
	if (sendOk == SOCKET_ERROR)
		cout << "That didn't work" << WSAGetLastError() << endl;
	// Odpowied¿
	char answer[1024] = {};
	int slen = sizeof(sockaddr_in);
	int answer_length;
	if ((answer_length = recvfrom(out, answer, 1024, 0, (sockaddr*)&server, &slen)) == SOCKET_ERROR) {
		cout << "recvfrom() failed with error code: " << WSAGetLastError() << "\n";
		exit(EXIT_FAILURE);
	}
	cout << answer;
	// Wpisanie wiadomoœci
	cout << "Send your message.\n";
	cin.ignore((long long)numeric_limits<streamsize>::max, '\n');
	getline(cin, message);
	sendOk = sendto(out, message.c_str(), message.size() + 1, 0, (sockaddr*)&server, sizeof(server));
	if (sendOk == SOCKET_ERROR)
		cout << "That didn't work" << WSAGetLastError() << endl;
	// Odbieramy odpowiedŸ
	slen = sizeof(sockaddr_in);
	if ((answer_length = recvfrom(out, answer, 1024, 0, (sockaddr*)&server, &slen)) == SOCKET_ERROR) {
		cout << "recvfrom() failed with error code: " << WSAGetLastError() << "\n";
		exit(EXIT_FAILURE);
	}
	cout << answer;

	cout << "Do you want to finish now? If yes, you will send a delete request to the server. Y/N ";
	char choice;
	cin >> choice;
	if (choice == 'y' || choice == 'Y')
		return;
	start();
}

Client::~Client() {
	message = "Delete";
	int sendOk = sendto(out, message.c_str(), message.size() + 1, 0, (sockaddr*)&server, sizeof(server));
	if (sendOk == SOCKET_ERROR)
		cout << "That didn't work" << WSAGetLastError() << endl;
	// Odpowied¿
	char answer[1024] = {};
	int slen = sizeof(sockaddr_in);
	int answer_length;
	if ((answer_length = recvfrom(out, answer, 1024, 0, (sockaddr*)&server, &slen)) == SOCKET_ERROR) {
		cout << "recvfrom() failed with error code: " << WSAGetLastError() << "\n";
		exit(EXIT_FAILURE);
	}
	cout << answer;
	// Wysy³anie nicku do usuniêcia
	message = nick;
	sendOk = sendto(out, message.c_str(), message.size() + 1, 0, (sockaddr*)&server, sizeof(server));
	if (sendOk == SOCKET_ERROR)
		cout << "That didn't work" << WSAGetLastError() << endl;
	// Odbieramy odpowiedŸ
	slen = sizeof(sockaddr_in);
	if ((answer_length = recvfrom(out, answer, 1024, 0, (sockaddr*)&server, &slen)) == SOCKET_ERROR) {
		cout << "recvfrom() failed with error code: " << WSAGetLastError() << "\n";
		exit(EXIT_FAILURE);
	}
	cout << answer;
	// Zamykamy gniazdo
	closesocket(out);
	// Wy³¹czamy winsock
	WSACleanup();
}