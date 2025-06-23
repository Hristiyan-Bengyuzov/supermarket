#include "LogRepository.h"
#include "Loader.hpp"

bool LogRepository::loadData()
{
    return load<Log>(file, items);
}

LogRepository::LogRepository() : Repository("logs.bin")
{
    loadData();
}
