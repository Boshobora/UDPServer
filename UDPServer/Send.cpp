#include "Send.h"
string Send::realization(string message, vector<string>& base, vector<string>& base2) {
	base2.push_back(message);
	cout << message << '\n';
	response = "You're message has been received\n";
	return response;
}