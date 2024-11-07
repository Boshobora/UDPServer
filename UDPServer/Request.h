#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Request {
protected:
	string response;
public:
	virtual string realization(string message, vector<string>& base, vector<string>& base2) = 0;
};