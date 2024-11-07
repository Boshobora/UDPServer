#pragma once
#include "Request.h"

class Send : public Request {
	string realization(string message, vector<string>& base, vector<string>& base2) override;
};