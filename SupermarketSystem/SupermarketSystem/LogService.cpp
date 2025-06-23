#include "LogService.h"

LogService::LogService(LogRepository& logRepo) : logRepo(logRepo)
{
}

bool LogService::log(size_t employeeId, const String& message)
{
	logRepo.add(Log(employeeId, message));
	return logRepo.saveChanges();
}
