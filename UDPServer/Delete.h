#pragma once
#include "Request.h"

class Delete : public Request {
public:
	string realization(string message, vector<string>& base, vector<string>& base2) override;
};