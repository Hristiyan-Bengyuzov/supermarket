#pragma once
#include "Repository.hpp"
#include "RegisterRequest.h"

class RegisterRequestRepository : public Repository<RegisterRequest> {
	bool loadData();
public:
	RegisterRequestRepository();
};