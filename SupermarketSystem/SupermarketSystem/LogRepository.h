#pragma once
#include "Repository.hpp"
#include "Log.h"

class LogRepository : public Repository<Log> {
	bool loadData();
public:
	LogRepository();
};