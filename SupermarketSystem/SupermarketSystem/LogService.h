#pragma once
#include "LogRepository.h"

class LogService {
private:
	LogRepository& logRepo;

public:
	LogService(LogRepository& logRepo);
	bool log(size_t employeeId, const String& message);
};