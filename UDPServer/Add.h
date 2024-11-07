#pragma once
#pragma once
#include "Request.h"

class Add : public Request {
public:
	string realization(string message, vector<string>& base, vector<string>& base2) override;
};