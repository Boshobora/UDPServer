#include "Delete.h"

string Delete::realization(string message, vector<string>& base, vector<string>& base2) {
	auto it = find(base.begin(), base.end(), message);
	base.erase(it);
	response = "You've been deleted from our base\n";
	cout << message << " has been removed from the server.\n";
	return response;
}