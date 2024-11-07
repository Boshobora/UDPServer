#include "Add.h"
#include <iostream>

string Add::realization(string message, vector<string>& base, vector<string>& base2) {
	if (find(base.begin(), base.end(), message) != base.end()) {
		response = "User with this nick already exists.\n";
	}
	else {
		base.push_back(message);
		response = "You've been added to our database.\n";
	}
	cout << message << " has been added to the server.\n";
	return response;
}